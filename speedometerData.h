#ifndef ENGINECONFIGURATION_H
#define ENGINECONFIGURATION_H

#include <QObject>
#include <QVector>
#include <QString>

class EngineConfiguration : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int getEngineRpm READ getEngineRpm WRITE setEngineRpm NOTIFY engineRPMChanged)
    Q_PROPERTY(int getSpeed READ getSpeed WRITE setSpeed NOTIFY speedChanged )
    Q_PROPERTY(double getMaxEngineRPM READ getMaxEngineRPM WRITE setMaxEngineRPM NOTIFY maxEngineRPMChanged);
    Q_PROPERTY(int getCurrentGear READ getCurrentGear WRITE setCurrentGear NOTIFY currentGearChanged);
    Q_PROPERTY(QString getDistance READ getDistance WRITE setDistance NOTIFY distanceChanged);

public:
    EngineConfiguration();

    void setEngineRpm(int rpm);
    int getEngineRpm() const;

    void setSpeed(int speed);
    int getSpeed() const;

    void setMaxEngineRPM(double rpm);
    double getMaxEngineRPM() const;

    void setCurrentGear(int gear);
    int getCurrentGear() const;

    void setFuelLevel(int fuel);
    int getFuelLevel() const;

    void setTempLevel(int temp);
    int getTempLevel() const;

    void setDistance(QString distance);
    QString getDistance() const;


    Q_INVOKABLE void accelerate(bool acc);
    Q_INVOKABLE void applyBrake(bool braks);
    Q_INVOKABLE void updateEngineProp(QString param, double value);
    Q_INVOKABLE double getUpdateEngineProperty(QString param);

public slots:
    void calculateSpeed();
    void generateEvent();
    void calculateDistance();
signals:
    void engineRPMChanged();
    void speedChanged();
    void maxEngineRPMChanged();
    void currentGearChanged();
    void distanceChanged();
    void eventGenerated(QString event);
private:

    void saveDistance(double dist);
    int m_engineRPM;
    int m_speed;
    int m_currentGear;
    bool isAccelrerating;
    bool isBraking;


    double m_distance;
    QString m_distanceString;

    double m_maxEngineRPM;
    double m_tyreDiameter;
    QVector<double>m_gearRatios;
    QVector<int> m_gearSpeeds;

    double m_driveRatio;
    int m_upShiftRPM;

};

#endif // ENGINECONFIGURATION_H
