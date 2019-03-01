#include "camerasubjective.h"

CameraSubjective::CameraSubjective() : CameraStereo::CameraStereo(){

    this->m_lacet = 0;
    this->m_tangage = 0;
    this->m_jumping = false;
    this->m_going_down = false;
    this->m_max_jump_height = 25.0;
    this->m_speed = 3.0f;
    updateTarget();
}

float CameraSubjective::tangage() const
{
    return m_tangage;
}

void CameraSubjective::setTangage(float tangage)
{
    m_tangage = tangage;
    updateTarget();
}

float CameraSubjective::lacet() const
{
    return m_lacet;
}

void CameraSubjective::setLacet(float lacet)
{
    m_lacet = lacet;
    updateTarget();
}

void CameraSubjective::updateTarget(){
    float dx = qCos(qDegreesToRadians(m_tangage)) * qCos(qDegreesToRadians(m_lacet));
    float dy = qSin(qDegreesToRadians(m_tangage));
    float dz = - qCos(qDegreesToRadians(m_tangage)) * qSin(qDegreesToRadians(m_lacet));
    m_target.setX(m_position.x() + dx);
    m_target.setY(m_position.y() + dy);
    m_target.setZ(m_position.z() + dz);
}

void CameraSubjective::avance(float dist){
    float y = m_position.y();
    m_position = m_position + dist * (m_target - m_position);
    m_position.setY(y);
    updateTarget();
}

void CameraSubjective::lateral(float dist){
    float y = m_position.y();

    QVector3D crossProd = QVector3D::crossProduct(m_target,m_position);
    crossProd.normalize();
    m_position = m_position + dist * crossProd;

    m_position.setY(y);
    updateTarget();
}

void CameraSubjective::vertical(float dist){
    float y = m_position.y();

    if(y <= 50 && y > 2) {

        float x = m_position.x();
        float z = m_position.z();

        QVector3D rVect = QVector3D::crossProduct(m_target, m_up);
        rVect.normalize();
        QVector3D uVect = QVector3D::crossProduct(rVect, m_target);
        uVect.normalize();
        m_position += dist * uVect;

        m_position.setX(x);
        m_position.setZ(z);
        updateTarget();

    }
}

void CameraSubjective::verticalJump(float dist){

    float x = m_position.x();
    float z = m_position.z();

    QVector3D rVect = QVector3D::crossProduct(m_target, m_up);
    rVect.normalize();
    QVector3D uVect = QVector3D::crossProduct(rVect, m_target);
    uVect.normalize();
    m_position += dist * uVect;

    m_position.setX(x);
    m_position.setZ(z);
    updateTarget();

}

void CameraSubjective::jump(){
    if(m_jumping ||  m_going_down) return;

    m_jumping = true;
    m_start_jump_y = m_position.y();
}

void CameraSubjective::updateJump(){
    if(m_jumping){
        verticalJump(m_speed * 0.5f);

        if(m_position.y() >= m_start_jump_y + m_max_jump_height){
            float offsetToFix = (m_start_jump_y + m_max_jump_height) - m_position.y();
            verticalJump(-abs(offsetToFix));
            m_jumping = false;
            m_going_down = true;
        }
    } else if(m_going_down){
        verticalJump(-m_speed);

        if(m_position.y() <= m_start_jump_y){
            float offsetToFix = m_start_jump_y - m_position.y();
            verticalJump(abs(offsetToFix));
            m_going_down = false;
        }
    }
}

