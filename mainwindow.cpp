#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QDateTime>
#include <QFileDialog>
#include <QTextStream>
#include <QScrollBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_serial(new QSerialPort(this))
    , m_sendTimer(new QTimer(this))
    , m_uiTimer(new QTimer(this))
{
    ui->setupUi(this);
    setWindowTitle("串口助手 v1.0");

    setupStatusBar();
    populatePorts();
    populateBaudRates();

    // 数据位
    ui->comboData->addItems({"5", "6", "7", "8"});
    ui->comboData->setCurrentText("8");

    // 校验位
    ui->comboParity->addItems({"None", "Even", "Odd", "Mark", "Space"});

    // 停止位
    ui->comboStop->addItems({"1", "1.5", "2"});

    // 默认定时发送间隔
    ui->spinInterval->setValue(1000);
    ui->spinInterval->setRange(10, 60000);

    // 接收区只读
    ui->textRecv->setReadOnly(true);

    // UI 刷新定时器：50ms 批量刷新一次接收区，防止高频数据卡死界面
    m_uiTimer->setInterval(50);
    connect(m_uiTimer, &QTimer::timeout, this, [this]() {
        if (m_rxBuffer.isEmpty()) return;
        QString display;
        if (ui->chkHexRecv->isChecked()) {
            display = m_rxBuffer.toHex(' ').toUpper();
        } else {
            display = QString::fromUtf8(m_rxBuffer);
        }
        m_rxBuffer.clear();
        appendReceiveText(display);
    });

    // 信号槽连接
    connect(ui->btnOpenClose,  &QPushButton::clicked,        this, &MainWindow::onOpenClosePort);
    connect(ui->btnRefresh,    &QPushButton::clicked,        this, &MainWindow::onRefreshPorts);
    connect(ui->btnSend,       &QPushButton::clicked,        this, &MainWindow::onSendData);
    connect(ui->btnClear,      &QPushButton::clicked,        this, &MainWindow::onClearReceive);
    connect(ui->btnSave,       &QPushButton::clicked,        this, &MainWindow::onSaveReceive);
    connect(ui->chkTimedSend,  &QCheckBox::toggled,          this, &MainWindow::onTimedSendToggle);
    connect(ui->chkHexSend,    &QCheckBox::toggled,          this, &MainWindow::onHexSendToggle);
    connect(ui->chkHexRecv,    &QCheckBox::toggled,          this, &MainWindow::onHexRecvToggle);
    connect(m_serial,          &QSerialPort::readyRead,      this, &MainWindow::onReadData);
    connect(m_serial,          &QSerialPort::errorOccurred,  this, &MainWindow::onSerialError);
    connect(m_sendTimer,       &QTimer::timeout,             this, &MainWindow::onTimedSend);
    connect(ui->spinInterval, &QSpinBox::valueChanged, this, [this](int value) {
        if (m_sendTimer->isActive())
            m_sendTimer->setInterval(value);
    });

    // 回车发送
    connect(ui->editSend, &QLineEdit::returnPressed, this, &MainWindow::onSendData);
}

MainWindow::~MainWindow()
{
    if (m_serial->isOpen())
        m_serial->close();
    delete ui;
}

// ─────────────────────────────────────────────
//  状态栏初始化
// ─────────────────────────────────────────────
void MainWindow::setupStatusBar()
{
    m_statusLabel   = new QLabel("未连接", this);
    m_rxCountLabel  = new QLabel("RX: 0 B", this);
    m_txCountLabel  = new QLabel("TX: 0 B", this);

    statusBar()->addWidget(m_statusLabel, 1);
    statusBar()->addPermanentWidget(m_rxCountLabel);
    statusBar()->addPermanentWidget(m_txCountLabel);
}

// ─────────────────────────────────────────────
//  填充串口列表
// ─────────────────────────────────────────────
void MainWindow::populatePorts()
{
    ui->comboPort->clear();
    const auto ports = QSerialPortInfo::availablePorts();
    for (const auto &info : ports) {
        QString label = info.portName();
        if (!info.description().isEmpty())
            label += " (" + info.description() + ")";
        ui->comboPort->addItem(label, info.portName());
    }
    if (ports.isEmpty())
        ui->comboPort->addItem("无可用串口");
}

// ─────────────────────────────────────────────
//  填充波特率（含 Custom 自定义输入）
// ─────────────────────────────────────────────
void MainWindow::populateBaudRates()
{
    ui->comboBaud->addItems({
        "1200", "2400", "4800", "9600",
        "19200", "38400", "57600", "115200",
        "230400", "460800", "921600", "Custom"
    });
    ui->comboBaud->setCurrentText("115200");

    connect(ui->comboBaud, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, [this](int index) {
                if (ui->comboBaud->itemText(index) == "Custom") {
                    ui->comboBaud->setEditable(true);
                    ui->comboBaud->lineEdit()->clear();
                    ui->comboBaud->lineEdit()->setPlaceholderText("输入波特率...");
                } else {
                    ui->comboBaud->setEditable(false);
                }
            });
}

// ─────────────────────────────────────────────
//  打开 / 关闭串口
// ─────────────────────────────────────────────
void MainWindow::onOpenClosePort()
{
    if (m_serial->isOpen()) {
        m_sendTimer->stop();
        m_uiTimer->stop();
        m_rxBuffer.clear();
        ui->chkTimedSend->setChecked(false);
        m_serial->close();
        ui->btnOpenClose->setText("打开串口");
        m_statusLabel->setText("未连接");
        setPortControlsEnabled(true);
        return;
    }

    QString portName = ui->comboPort->currentData().toString();
    if (portName.isEmpty()) {
        QMessageBox::warning(this, "警告", "请先选择串口！");
        return;
    }

    // 波特率校验
    bool ok = false;
    int baud = ui->comboBaud->currentText().toInt(&ok);
    if (!ok || baud <= 0) {
        QMessageBox::warning(this, "警告", "请输入有效的波特率！");
        return;
    }

    m_serial->setPortName(portName);
    m_serial->setBaudRate(baud);

    // 数据位
    int dataBitsVal = ui->comboData->currentText().toInt();
    m_serial->setDataBits(static_cast<QSerialPort::DataBits>(dataBitsVal));

    // 校验位
    static const QMap<QString, QSerialPort::Parity> parityMap = {
        {"None",  QSerialPort::NoParity},
        {"Even",  QSerialPort::EvenParity},
        {"Odd",   QSerialPort::OddParity},
        {"Mark",  QSerialPort::MarkParity},
        {"Space", QSerialPort::SpaceParity}
    };
    m_serial->setParity(parityMap.value(ui->comboParity->currentText(), QSerialPort::NoParity));

    // 停止位
    static const QMap<QString, QSerialPort::StopBits> stopMap = {
        {"1",   QSerialPort::OneStop},
        {"1.5", QSerialPort::OneAndHalfStop},
        {"2",   QSerialPort::TwoStop}
    };
    m_serial->setStopBits(stopMap.value(ui->comboStop->currentText(), QSerialPort::OneStop));

    m_serial->setFlowControl(QSerialPort::NoFlowControl);

    if (m_serial->open(QIODevice::ReadWrite)) {
        // 拉高 DTR 和 RTS，通知设备可以发数据
        m_serial->setDataTerminalReady(true);
        m_serial->setRequestToSend(true);
         m_serial->setReadBufferSize(0);  // 不限制接收缓冲区大小
        m_uiTimer->start();
        ui->btnOpenClose->setText("关闭串口");
        m_statusLabel->setText(QString("已连接: %1 | %2-8-%3-%4")
                                   .arg(portName)
                                   .arg(baud)
                                   .arg(ui->comboParity->currentText())
                                   .arg(ui->comboStop->currentText()));
        setPortControlsEnabled(false);
    } else {
        QMessageBox::critical(this, "错误",
                              "无法打开串口: " + m_serial->errorString());
    }
}

// ─────────────────────────────────────────────
//  刷新串口列表
// ─────────────────────────────────────────────
void MainWindow::onRefreshPorts()
{
    populatePorts();
}

void MainWindow::appendColoredText(const QString &text, const QColor &color)
{
    QTextCursor cursor = ui->textRecv->textCursor();
    cursor.movePosition(QTextCursor::End);

    QTextCharFormat fmt;
    fmt.setForeground(color);
    cursor.setCharFormat(fmt);
    cursor.insertText(text + "\n");

    // 恢复默认颜色，避免影响后续插入
    QTextCharFormat defaultFmt;
    defaultFmt.setForeground(ui->textRecv->palette().color(QPalette::Text));
    cursor.setCharFormat(defaultFmt);

    ui->textRecv->setTextCursor(cursor);

    if (ui->chkAutoScroll->isChecked()) {
        QScrollBar *sb = ui->textRecv->verticalScrollBar();
        sb->setValue(sb->maximum());
    }
}

// ─────────────────────────────────────────────
//  发送数据
// ─────────────────────────────────────────────
void MainWindow::onSendData()
{
    if (!m_serial->isOpen()) {
        QMessageBox::warning(this, "警告", "请先打开串口！");
        return;
    }

    QString text = ui->editSend->text();
    if (text.isEmpty()) return;

    QByteArray data;
    if (ui->chkHexSend->isChecked()) {
        QString hex = text.remove(' ');
        if (hex.length() % 2 != 0) {
            QMessageBox::warning(this, "格式错误", "HEX 字符串长度必须为偶数！");
            return;
        }
        data = QByteArray::fromHex(hex.toLatin1());
    } else {
        data = text.toUtf8();
        if (ui->chkNewline->isChecked())
            data.append("\r\n");
    }

    qint64 written = m_serial->write(data);
    if (written > 0) {
        m_txCount += written;
        updateCountLabel();

        // 新增：在接收框显示发送内容
        QString prefix = "[TX]";
        if (ui->chkTimestamp->isChecked())
            prefix += " " + QDateTime::currentDateTime().toString("[hh:mm:ss.zzz]");
        prefix += " ";

        QString display = ui->chkHexSend->isChecked()
                              ? data.toHex(' ').toUpper()
                              : QString::fromUtf8(data).trimmed();

        appendColoredText(prefix + display, QColor("#E8A838")); // 橙黄色
    }
}

// ─────────────────────────────────────────────
//  接收数据：只写缓冲区，不操作 UI
// ─────────────────────────────────────────────
void MainWindow::onReadData()
{
    QByteArray data = m_serial->readAll();
    m_rxCount += data.size();
    updateCountLabel();
    m_rxBuffer.append(data);
}

// ─────────────────────────────────────────────
//  追加接收文本到界面
// ─────────────────────────────────────────────
void MainWindow::appendReceiveText(const QString &text)
{
    QString prefix = "[RX]";
    if (ui->chkTimestamp->isChecked())
        prefix += " " + QDateTime::currentDateTime().toString("[hh:mm:ss.zzz]");
    prefix += " ";

    appendColoredText(prefix + text, QColor("#1db7dd")); // 蓝色
}

// ─────────────────────────────────────────────
//  定时发送
// ─────────────────────────────────────────────
void MainWindow::onTimedSendToggle(bool checked)
{
    if (checked) {
        if (!m_serial->isOpen()) {
            QMessageBox::warning(this, "警告", "请先打开串口！");
            ui->chkTimedSend->setChecked(false);
            return;
        }
        m_sendTimer->start(ui->spinInterval->value());
    } else {
        m_sendTimer->stop();
    }
}

void MainWindow::onTimedSend()
{
    onSendData();
}

// ─────────────────────────────────────────────
//  清空接收区
// ─────────────────────────────────────────────
void MainWindow::onClearReceive()
{
    ui->textRecv->clear();
    m_rxBuffer.clear();
    m_rxCount = 0;
    m_txCount = 0;
    updateCountLabel();
}

// ─────────────────────────────────────────────
//  保存接收内容到文件
// ─────────────────────────────────────────────
void MainWindow::onSaveReceive()
{
    QString fileName = QFileDialog::getSaveFileName(
        this, "保存接收数据", "",
        "文本文件 (*.txt);;所有文件 (*)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream out(&file);
        out.setEncoding(QStringConverter::Utf8);  // Qt6 设置 UTF-8 编码，防止中文乱码
        out << ui->textRecv->toPlainText();        // toPlainText() 已包含所有显示内容
        file.close();
        statusBar()->showMessage("已保存到: " + fileName, 3000);
    } else {
        QMessageBox::critical(this, "错误", "无法写入文件！");
    }
}

// ─────────────────────────────────────────────
//  HEX 发送格式提示
// ─────────────────────────────────────────────
void MainWindow::onHexSendToggle(bool checked)
{
    ui->editSend->setPlaceholderText(
        checked ? "输入 HEX 数据，如：AA BB CC DD" : "输入发送内容...");
}

void MainWindow::onHexRecvToggle(bool /*checked*/)
{
    // 切换后只影响后续数据，已有内容不变
}

// ─────────────────────────────────────────────
//  串口错误处理
// ─────────────────────────────────────────────
void MainWindow::onSerialError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::NoError) return;

    if (m_serial->isOpen()) {
        m_uiTimer->stop();
        m_rxBuffer.clear();
        m_serial->close();
        ui->btnOpenClose->setText("打开串口");
        m_statusLabel->setText("未连接");
        setPortControlsEnabled(true);
        QMessageBox::critical(this, "串口错误",
                              "串口发生错误，已断开连接。\n错误信息: " + m_serial->errorString());
    }
}

// ─────────────────────────────────────────────
//  控件使能控制
// ─────────────────────────────────────────────
void MainWindow::setPortControlsEnabled(bool enabled)
{
    ui->comboPort->setEnabled(enabled);
    ui->comboBaud->setEnabled(enabled);
    ui->comboData->setEnabled(enabled);
    ui->comboParity->setEnabled(enabled);
    ui->comboStop->setEnabled(enabled);
    ui->btnRefresh->setEnabled(enabled);
}

// ─────────────────────────────────────────────
//  更新收发计数标签
// ─────────────────────────────────────────────
void MainWindow::updateCountLabel()
{
    m_rxCountLabel->setText(QString("RX: %1 B").arg(m_rxCount));
    m_txCountLabel->setText(QString("TX: %1 B").arg(m_txCount));
}
