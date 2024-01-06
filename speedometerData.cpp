#include "speedometerData.h"
#include <iostream>
#include <QTimer>
#include <QFile>

EngineConfiguration::EngineConfiguration()
{
    m_maxEngineRPM = 4000;
    m_driveRatio = 3.4;
    m_tyreDiameter = 680;
    m_currentGear = 1;
    m_upShiftRPM = 3000;


    m_gearRatios.append(2.97);
    m_gearRatios.append(2.07);
    m_gearRatios.append(1.43);
    m_gearRatios.append(1.0);
    m_gearRatios.append(0.84);
    m_gearRatios.append(0.56);

    m_gearSpeeds.append(5);
    m_gearSpeeds.append(37);
    m_gearSpeeds.append(54);
    m_gearSpeeds.append(78);
    m_gearSpeeds.append(111);
    m_gearSpeeds.append(132);

    // this class(Qfile) able to open and read the updated distace and change according when user will accelerate

    QFile file("/Desktop/Qt/speeedoMeter/distance.txt");
    if(file.open(QIODevice::ReadWrite)) {
        while(!file.atEnd()) {
            QByteArray line = file.readLine();
            m_distance = line.toDouble();
        }
        file.close();
    }
    m_distanceString = QString::number(m_distance,'f',3);

    isAccelrerating = false;
    isBraking = false;

    // when timer is timout every 100 milisecond and it emit the signal means calculateSpeed have to change the value
    QTimer *timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&EngineConfiguration::calculateSpeed);
    timer->start(100);


    QTimer *distanceTimer = new QTimer(this);
    connect(distanceTimer,&QTimer::timeout,this,&EngineConfiguration::calculateDistance);
    distanceTimer->start(100);


}

void EngineConfiguration::setEngineRpm(int rpm){
    if(rpm > 0) {
        m_engineRPM = rpm;
    }

}
int EngineConfiguration::getEngineRpm() const{
    return m_engineRPM;
}


void EngineConfiguration::setSpeed(int speed) {
    m_speed = speed;
}

int EngineConfiguration::getSpeed() const {
    return m_speed;
}

// when user apply the brake then isBraking will true and isAccelreting is false it emit the signal
// of speedChanged and engineRPMChanged means it has to change the value

void EngineConfiguration::applyBrake(bool braks) {
    if(braks == true) {
        isBraking = true;
        isAccelrerating = false;
        emit speedChanged();
        emit engineRPMChanged();
    }

    else {
        isBraking = false;
        emit speedChanged();
        emit engineRPMChanged();
    }

}

// when user apply accelerate the speed using the upkey isBraking false and isAccelreting is true
// and it emit the signal of speedchanged and engineRPMChanged

void EngineConfiguration::accelerate(bool acc) {
    if(acc == true) {
        isBraking = false;
        isAccelrerating = true;
        emit speedChanged();
        emit engineRPMChanged();
    }

    else {
        isAccelrerating = false;
        emit speedChanged();
        emit engineRPMChanged();
    }
}

void EngineConfiguration::setMaxEngineRPM(double rpm) {
    m_maxEngineRPM = rpm;
    emit maxEngineRPMChanged();
}
double EngineConfiguration::getMaxEngineRPM() const {
    return m_maxEngineRPM;
}

void EngineConfiguration::setCurrentGear(int gear){
    m_currentGear = gear;

}
int EngineConfiguration::getCurrentGear() const {
    return m_currentGear;
}



void EngineConfiguration::setDistance(QString distance) {
    m_distanceString = distance;
}
QString EngineConfiguration::getDistance() const {
    return m_distanceString;
}

void EngineConfiguration::updateEngineProp(QString param, double value) {

    if(param.compare("engineRPM") == 0 ) {
        m_maxEngineRPM = value;
        emit maxEngineRPMChanged();
    }
    else if(param.compare("upShiftRPM") == 0 ) {
        m_upShiftRPM = value;
    }
    else if(param.compare("tyreDiameter") == 0 ) {
        m_tyreDiameter = value;
    }
    else if(param.compare("driveRatio") == 0 ) {
        m_driveRatio = value;
    }
    else if(param.compare("firstGear") == 0 ) {
        m_gearRatios[0] = value;
    }
    else if(param.compare("secondGear") == 0 ) {
        m_gearRatios[1] = value;
    }
    else if(param.compare("thirdGear") == 0 ) {
        m_gearRatios[2] = value;
    }
    else if(param.compare("fourthGear") == 0 ) {
        m_gearRatios[3] = value;
    }
    else if(param.compare("fifthGear") == 0 ) {
        m_gearRatios[4] = value;
    }
    else if(param.compare("sixthGear") == 0 ) {
        m_gearRatios[5] = value;
    }
}

double EngineConfiguration::getUpdateEngineProperty(QString param) {
    if(param.compare("engineRPM") == 0 ) {
        return m_maxEngineRPM ;
    }
    else if(param.compare("tyreDiameter") == 0 ) {
        return m_tyreDiameter;
    }
    else if(param.compare("driveRatio") == 0 ) {
        return m_driveRatio;
    }
    else if(param.compare("firstGear") == 0 ) {
        return m_gearRatios.at(0);
    }
    else if(param.compare("secondGear") == 0 ) {
        return m_gearRatios.at(1);
    }
    else if(param.compare("thirdGear") == 0 ) {
        return m_gearRatios.at(2);
    }
    else if(param.compare("fourthGear") == 0 ) {
        return m_gearRatios.at(3);
    }
    else if(param.compare("fifthGear") == 0 ) {
        return m_gearRatios.at(4);
    }
    else if(param.compare("sixthGear") == 0 ) {
        return m_gearRatios.at(5);
    }

    else if(param.compare("upShiftRPM") == 0 ) {
        return m_upShiftRPM;
    }

    return 0;

}
// this function calculate the speed using formula

void EngineConfiguration::calculateSpeed() {

    if(isAccelrerating && m_engineRPM < getMaxEngineRPM()) {
        m_engineRPM += 50;
    }

    else if(!isAccelrerating && m_engineRPM > 0) {
        m_engineRPM -= 50;
    }
    if(m_currentGear < 6 ) {
        if( isAccelrerating == true && m_engineRPM > m_upShiftRPM) {
            m_currentGear += 1;
            if(m_currentGear > 6)
                m_currentGear = 6;

            m_engineRPM = (m_speed * (30 * m_gearRatios[m_currentGear - 1] * m_driveRatio)) / (3.6 * 3.14 * (m_tyreDiameter/(2 * 1000)));
        }
    }

    if(!isAccelrerating && isBraking){
        m_engineRPM -= 200 ;
    }

    if(!isAccelrerating) {
        if(m_currentGear > 0) {
            if(m_speed < m_gearSpeeds.at(m_currentGear - 1)) {
                m_currentGear -= 1;
                if(m_currentGear < 1 )
                    m_currentGear = 1;

                m_engineRPM = (m_speed * (30 * m_gearRatios[m_currentGear - 1] * m_driveRatio)) / (3.6 * 3.14 * (m_tyreDiameter/(2 * 1000)));
            }
        }
    }


    m_speed = 3.6 * m_engineRPM * 3.14 * (m_tyreDiameter/(2 * 1000)) / (30 * m_gearRatios[m_currentGear - 1] * m_driveRatio);

    emit speedChanged();
    emit engineRPMChanged();
    emit currentGearChanged();
}

void EngineConfiguration::calculateDistance() {
    double secondDist = (double)m_speed / 3600;
    m_distance += secondDist;

    m_distanceString = QString::number(m_distance,'f',3);
    emit distanceChanged();

}

void EngineConfiguration::generateEvent() {
    saveDistance(m_distance);

}

void EngineConfiguration::saveDistance(double dist) {
    QFile file("Desktop/speedoMeter/distance.txt");
    if(file.open(QIODevice::ReadWrite)) {
        if(dist > 0) {
            QByteArray temp;
            temp.setNum(dist);
            file.write(temp);
        }
        file.close();
    }

}







