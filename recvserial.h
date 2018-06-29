#ifndef RECVSERIAL_HPP
#define RECVSERIAL_HPP
#include <QThread>

class RcvSerialdata : public QThread
{
    Q_OBJECT
public:
    explicit RcvSerialdata(QObject *parent = nullptr);

protected:
    void run();

signals:
    void send2main_signal(int i);

public slots:
};

#endif // RECVSERIAL_HPP
