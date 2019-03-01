#include "cameraspherique.h"

CameraSpherique::CameraSpherique() : CameraStereo::CameraStereo(){
    this->m_rho = 0;
    this->m_phi = 0;
    this->m_theta = 0;
    update_position();
}

float CameraSpherique::getRho() const
{
    return m_rho;
}

void CameraSpherique::setRho(float rho)
{
    if(rho > 0) {
        m_rho = rho;
        update_position();
    }
}

float CameraSpherique::getTheta() const
{
    return m_theta;
}

void CameraSpherique::setTheta(float theta)
{
    m_theta = theta;
    update_position();
}

float CameraSpherique::getPhi() const
{
    return m_phi;
}

void CameraSpherique::setPhi(float phi)
{
    if(phi > -(M_PI_2) && phi < M_PI_2 ) {
        m_phi = phi;
        update_position();
    }
}

void CameraSpherique::update_position(){
    float x = m_target.x() + m_rho * qCos(m_phi) * qCos(m_theta);
    float y = m_target.y() + m_rho * qSin(m_phi);
    float z = m_target.z() + m_rho * qCos(m_phi) * qSin(m_theta);

    m_position.setX(x);
    m_position.setY(y);
    m_position.setZ(z);
}

void CameraSpherique::setPosition(const QVector3D &position){
    m_position = position;
    update_position();
}
