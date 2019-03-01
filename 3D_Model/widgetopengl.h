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
#include "cube.h"
#include "cameraspherique.h"
#include "skybox.h"
#include "deAJouer.h"
#include "cubetex.h"
#include "cubeeclaire.h"
#include "model.h"
#include "plan.h"
#include "avion.h"


class WidgetOpenGL : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    WidgetOpenGL(QWidget* parent = nullptr);
    ~WidgetOpenGL();
    void addDrawable(Drawable* d);

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
    Plan* m_plan;
    Avion* m_avion;
};

#endif // WIDGETOPENGL_H
