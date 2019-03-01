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




class WidgetOpenGL : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    WidgetOpenGL(QWidget* parent = nullptr);
    ~WidgetOpenGL();
    void addDrawable(Drawable* d);

    Light *light() const;
    void setLight(Light *light);

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
    void changeFov(int i);
    void startAnimation();
    void changeOpacity(int i);
    void reset();

private:
    QOpenGLVertexArrayObject* m_vao;
    QOpenGLBuffer* m_vbo;
    QOpenGLShaderProgram* m_programme;
    QTimer* m_timer;
    GLfloat m_angleY;
    GLfloat m_angleX;
    GLfloat m_angleZ;
    QPoint lastPos;
    GLboolean rotationAnimation;
    int fov;
    float m_opacity;
//    Cube* m_cube;
    CameraSpherique* m_camera;
    QList<Drawable*> m_objets;
    Light* m_light;
};

#endif // WIDGETOPENGL_H
