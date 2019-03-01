#include "camerastereo.h"

CameraStereo::CameraStereo() : Camera::Camera(){
    this->m_distanceInterOeil = 4;
    this->m_distanceFocale = 60;
    this->m_typeCamera = MONO;

}

float CameraStereo::distanceInterOeil() const
{
    return m_distanceInterOeil;
}

void CameraStereo::setDistanceInterOeil(float distanceInterOeil)
{
    m_distanceInterOeil = distanceInterOeil;
}

float CameraStereo::distanceFocale() const
{
    return m_distanceFocale;
}

void CameraStereo::setDistanceFocale(float distanceFocale)
{
    m_distanceFocale = distanceFocale;
}

int CameraStereo::typeCamera() const
{
    return m_typeCamera;
}

void CameraStereo::setTypeCamera(int typeCamera)
{
    m_typeCamera = typeCamera;
}

QMatrix4x4 CameraStereo::view(){
    switch (m_typeCamera) {
        case RV_CAMERA::MONO :
            return Camera::view();
        case RV_CAMERA::LEFT :
            return this->vueGauche();
        case RV_CAMERA::RIGHT :
            return this->vueDroite();
    }
}

QMatrix4x4 CameraStereo::projection(){
    switch (m_typeCamera) {
        case RV_CAMERA::MONO :
            return Camera::projection();
        case RV_CAMERA::LEFT :
            return this->projectionGauche();
        case RV_CAMERA::RIGHT :
            return this->projectionDroite();
    }
}

QMatrix4x4 CameraStereo::vueGauche(){
    QVector3D v = QVector3D::crossProduct((m_target - m_position), m_up);
    float norm = sqrt(v.x() * v.x() + v.y() * v.y() + v.z() * v.z());
    QVector3D vdn = v / norm;
    float dOEIL2 = m_distanceInterOeil / 2;
    QVector3D posOG = m_position - (dOEIL2 * vdn);
    QVector3D cibleOG = m_target - (dOEIL2 * vdn);

    QMatrix4x4 viewMatrix = QMatrix4x4();
    viewMatrix.lookAt(posOG, cibleOG, m_up);
    return viewMatrix;
}

QMatrix4x4 CameraStereo::vueDroite(){
    QVector3D v = QVector3D::crossProduct((m_target - m_position), m_up);
    float norm = sqrt(v.x() * v.x() + v.y() * v.y() + v.z() * v.z());
    QVector3D vdn = v / norm;
    float dOEIL2 = m_distanceInterOeil / 2;
    QVector3D posOD = m_position + (dOEIL2 * vdn);
    QVector3D cibleOD = m_target + (dOEIL2 * vdn);

    QMatrix4x4 viewMatrix = QMatrix4x4();
    viewMatrix.lookAt(posOD, cibleOD, m_up);
    return viewMatrix;
}

QMatrix4x4 CameraStereo::projectionGauche(){

    float fovd2 = qDegreesToRadians(m_fov / 2.0f);
    float top  = m_zmin * tan(fovd2);
    float bottom = -top;
    float a = m_distanceFocale * m_aspect_ratio * tan(fovd2);
    float b = a - (m_distanceInterOeil / 2.0f);
  //  float c = (2 * a) - b;
    float c = a + (m_distanceInterOeil / 2.0f);
    float dleft = (b * m_zmin) / m_distanceFocale;
    float dright = (c * m_zmin) / m_distanceFocale;

    QMatrix4x4 projectionMatrix = QMatrix4x4();
    projectionMatrix.frustum(-dleft, dright, bottom, top, m_zmin, m_zmax);
    return projectionMatrix;
}

QMatrix4x4 CameraStereo::projectionDroite(){

    float fovd2 = qDegreesToRadians(m_fov / 2.0f);
    float top  = m_zmin * tan(fovd2);
    float bottom = -top;
    float a = m_distanceFocale * m_aspect_ratio * tan(fovd2);
    float b = a - (m_distanceInterOeil / 2.0f);
    float c = a + (m_distanceInterOeil / 2.0f);
    float dleft = (c * m_zmin) / m_distanceFocale;
    float dright = (b * m_zmin) / m_distanceFocale;

    QMatrix4x4 projectionMatrix = QMatrix4x4();
    projectionMatrix.frustum(-dleft, dright, bottom, top, m_zmin, m_zmax);
    return projectionMatrix;
}

