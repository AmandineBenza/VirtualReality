#include "cameraspherique.h"

CameraSpherique::CameraSpherique() : Camera::Camera(){
    this->m_rho = 10;
    this->m_phi = 0;
    this->m_theta = 0;
    this->cible = QVector3D(0.0f,0.0f,0.0f);
    update_position();
}

QVector3D CameraSpherique::getCible() const
{
    return cible;
}

void CameraSpherique::setCible(const QVector3D &value)
{
    cible = value;
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
    float x = cible.x() + m_rho * qCos(m_phi) * qCos(m_theta);
    float y = cible.y() + m_rho * qSin(m_phi);
    float z = cible.z() + m_rho * qCos(m_phi) * qSin(m_theta);

    m_position.setX(x);
    m_position.setY(y);
    m_position.setZ(z);
}
