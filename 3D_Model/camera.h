#ifndef CAMERA_H
#define CAMERA_H

#include <QMatrix4x4>
#include <QtGui>
#include <QMessageBox>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>

class Camera
{

public:
    Camera();

    float fov() const;
    void setFov(float fov);

    float aspect_ratio() const;
    void setAspect_ratio(float aspect_ratio);

    float zmin() const;
    void setZmin(float zmin);

    float zmax() const;
    void setZmax(float zmax);

    QVector3D position() const;
    virtual void setPosition(const QVector3D &position);

    QVector3D target() const;
    void setTarget(const QVector3D &target);

    void setUp(const QVector3D &up);

    QMatrix4x4 view();
    QMatrix4x4 projection();

protected:
    float m_fov;
    float m_aspect_ratio;
    float m_zmin;
    float m_zmax;
    QVector3D m_position;
    QVector3D m_target;
    QVector3D m_up;

};

#endif // CAMERA_H

