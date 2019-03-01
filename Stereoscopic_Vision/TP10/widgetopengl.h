// Cours de Réalité Virtuelle
// leo.donati@univ-cotedazur.fr
//
// EPU 2018-19

#ifndef WIDGETOPENGL_H
#define WIDGETOPENGL_H

#include <QtGui>
#include <QMessageBox>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QMatrix4x4>
#include <QTimer>
#include <QtGamepad>
#include <iostream>
#include <QElapsedTimer>
#include "cube.h"
#include "cameraspherique.h"
#include "skybox.h"
#include "deAJouer.h"
#include "cubetex.h"
#include "cubeeclaire.h"
#include "model.h"
#include "plan.h"
#include "avion.h"
#include "camerasubjective.h"

enum SWITCH_CAMERA { NORMAL_VIEW, DDD_VIEW, DOUBLE_VIEW};

class WidgetOpenGL : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    WidgetOpenGL(QWidget* parent = nullptr);
    ~WidgetOpenGL();

    Light *light() const;
    void setLight(Light *light);
    void keyPressEvent(QKeyEvent*event);

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void initializeVAO();
    void initializeShader();
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);

private slots:
    void update();

private:
    QOpenGLVertexArrayObject* m_vao;
    QOpenGLBuffer* m_vbo;
    QOpenGLShaderProgram* m_programme;
    GLfloat m_angleY;
    GLfloat m_angleX;
    GLfloat m_angleZ;
    QPoint lastPos;
    int fov;
    float m_opacity;
    CameraSpherique* m_camera;
    Light* m_light;
    Model* m_batiment;
    CameraSubjective* m_cameraSub;
    QGamepad* m_gamepad;
    float m_fps;
    float m_fps_cpt;
    QElapsedTimer* m_timer;
    QElapsedTimer* m_help_timer;
    QElapsedTimer* m_switch_timer;
    bool m_help;
    int m_switch;
};

#endif // WIDGETOPENGL_H
