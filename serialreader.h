#ifndef SERIALREADER_H
#define SERIALREADER_H

#include <QObject>
class QSerialPort;

class SerialReader : public QObject
{
    Q_OBJECT
    Q_PROPERTY(float vrX READ vrX WRITE setvrX NOTIFY vrXChanged FINAL)
    Q_PROPERTY(float vrY READ vrY WRITE setvrY NOTIFY vrYChanged FINAL)
public:
    explicit SerialReader(QObject *parent = nullptr);

    float vrX() const;
    void setvrX(float newVrX);

    float vrY() const;
    void setvrY(float newVrY);

signals:

    void vrXChanged();
    void vrYChanged();

private:
    float m_vrX;
    float m_vrY;

    void newValues(QStringList list);

};

#endif // SERIALREADER_H
