#pragma once

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // 串口操作
    void onOpenClosePort();
    void onRefreshPorts();

    // 数据收发
    void onSendData();
    void onReadData();

    // 定时发送
    void onTimedSend();
    void onTimedSendToggle(bool checked);

    // 界面操作
    void onClearReceive();
    void onSaveReceive();
    void onHexSendToggle(bool checked);
    void onHexRecvToggle(bool checked);

    // 串口状态
    void onSerialError(QSerialPort::SerialPortError error);
    void appendColoredText(const QString &text, const QColor &color);

private:
    QByteArray  m_rxBuffer;   // 接收缓冲区
    QTimer     *m_uiTimer;    // UI 刷新定时器

private:
    Ui::MainWindow *ui;
    QSerialPort    *m_serial;
    QTimer         *m_sendTimer;

    // 状态栏标签
    QLabel *m_statusLabel;
    QLabel *m_rxCountLabel;
    QLabel *m_txCountLabel;

    quint64 m_rxCount = 0;
    quint64 m_txCount = 0;

    void setupStatusBar();
    void populatePorts();
    void populateBaudRates();
    void setPortControlsEnabled(bool enabled);
    void updateCountLabel();
    void appendReceiveText(const QString &text);
};
