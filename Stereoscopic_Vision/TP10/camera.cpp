#include "camera.h"

Camera::Camera()
{
    m_position = QVector3D(0,0,4);
    m_target = QVector3D(0,0,0);
    m_up = QVector3D(0,1,0);
    m_fov = 30.0f;
    m_aspect_ratio = 4.0f / 3;
    m_zmin = 0.1f;
    m_zmax = 1000.0f;
}

float Camera::fov() const
{
    return m_fov;
}

void Camera::setFov(float fov)
{
    if(fov >= 5 && fov <=130)
    m_fov = fov;
}

float Camera::aspect_ratio() const
{
    return m_aspect_ratio;
}

void Camera::setAspect_ratio(float aspect_ratio)
{
    m_aspect_ratio = aspect_ratio;
}

float Camera::zmin() const
{
    return m_zmin;
}

void Camera::setZmin(float zmin)
{
    m_zmin = zmin;
}

float Camera::zmax() const
{
    return m_zmax;
}

void Camera::setZmax(float zmax)
{
    m_zmax = zmax;
}

QVector3D Camera::position() const
{
    return m_position;
}

void Camera::setPosition(const QVector3D &position)
{
    m_position = position;
}

QVector3D Camera::target() const
{
    return m_target;
}

void Camera::setTarget(const QVector3D &target)
{
    m_target = target;
}

void Camera::setUp(const QVector3D &up)
{
    m_up = up;
}

QMatrix4x4 Camera::projection(){
    //Définition de la matrice de projetcion
    QMatrix4x4 proj = QMatrix4x4();
    proj.perspective(m_fov, m_aspect_ratio, m_zmin, m_zmax);
    return proj;
}

QMatrix4x4 Camera::view(){
    QMatrix4x4 view = QMatrix4x4();
    view.lookAt(m_position, m_target, m_up);
    return view;
}
