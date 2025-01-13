#include "serialreader.h"

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <string>
#include <QVector2D>
#include <math.h>

SerialReader::SerialReader(QObject *parent)
    : QObject{parent}
{


    QList<QSerialPortInfo> serialPorts = QSerialPortInfo::availablePorts();
    qDebug() << serialPorts[0].portName();

    QSerialPort* port = new QSerialPort();
    port->setPort(serialPorts[0]);
    port->setBaudRate(115200,QSerialPort::AllDirections);
    port->setDataBits(QSerialPort::Data8);
    port->setParity(QSerialPort::NoParity);
    port->setStopBits(QSerialPort::OneStop);
    port->open(QIODevice::ReadOnly);


    QByteArray data;
    connect(port, &QSerialPort::readyRead, this, [this,port,data]() {
        static QByteArray data;
        if(data.isEmpty())
            data = port->readLine();
        else{
            data.append(port->readLine());

        }

        if(data[data.size()-1] != '\n'){
            return;
        }

        /*remove new line char*/
        data.removeLast();
        QString s = data.toStdString().c_str();

        //qDebug() << "Received data:" << s;

        QStringList list =  s.split(",");
        newValues(list);
        data.clear();
        //qDebug() << "free:" << port->bytesAvailable();

    });

}

float SerialReader::vrX() const
{
    return m_vrX;
}

void SerialReader::setvrX(float newVrX)
{
    if (qFuzzyCompare(m_vrX, newVrX))
        return;
    m_vrX = newVrX;
    emit vrXChanged();
}

float SerialReader::vrY() const
{
    return m_vrY;
}

void SerialReader::setvrY(float newVrY)
{
    if (qFuzzyCompare(m_vrY, newVrY))
        return;
    m_vrY = newVrY;
    emit vrYChanged();
}

void SerialReader::newValues(QStringList list)
{
    float x = m_vrX;
    float y = m_vrY;

    for(QString s : list){
        char k = s.toStdString().at(0);
        s.removeFirst();
        s.removeFirst();
        if(k == 'Y'){
            y =  std::stof(s.toStdString());
        }
        if( k == 'X'){
            x =  std::stof(s.toStdString());
        }
    }

    QVector2D v(x,y);

    float length = std::clamp(v.length(),-1.f,1.f );
    float angle = std::atan2(y,x);
    float y_new = length*sin(angle);
    float x_new = length*cos(angle);
    v = QVector2D(x_new,y_new);

    setvrX(v.x());
    setvrY(v.y());

}
