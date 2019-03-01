// Cours de Réalité Virtuelle
// leo.donati@univ-cotedazur.fr
//
// EPU 2018-19

#include "widgetopengl.h"

#define BUFFER_OFFSET(i)   ((char *)NULL + (i))

WidgetOpenGL::WidgetOpenGL(QWidget* parent)
    :QOpenGLWidget(parent),QOpenGLFunctions()
{
    grabKeyboard();
}

WidgetOpenGL::~WidgetOpenGL()
{
}

void WidgetOpenGL::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor ( 0 , 0.204f, 0.627f, 0.792f );
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    m_camera = new CameraSpherique();
    m_camera->setAspect_ratio(GLfloat(width())/height());
    m_camera->setPosition(QVector3D(0, 1, 5));
    m_camera->setRho(50);

    m_light = new Light();
    m_light->setLight_position(QVector3D(0,20,0));
    m_light->setSpecular_strength(500);

    m_plan = new Plan();
    m_plan->setLargeur(300);
    m_plan->setLongueur(300);
    m_plan->setPosition(0, -20, 0);
    m_plan->setSegLargeur(100);
    m_plan->setSegLongueur(100);
    m_plan->setTexture(":/images/snow1");
    m_plan->setHeightmap(":/images/heightmap7-420x420.png");
    m_plan->initializeVAO();
    m_plan->setCamera(m_camera);
    m_plan->setLight(m_light);

    m_avion = new Avion();
    m_avion->setPosition(0, 0, 0);
    m_avion->setScale(0.5f);
    m_avion->initializeVAO();
    m_avion->setCamera(m_camera);
    m_avion->setLight(m_light);

//    addDrawable(m_plan);
//    addDrawable(m_avion);
}

void WidgetOpenGL::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_plan->draw();
    m_avion->draw();
    update();
}

void WidgetOpenGL::resizeGL(int width, int height)
{
    //transformation de viewport
    glViewport(0, 0, width, height);
}

void WidgetOpenGL::update()
{
    m_avion->avance(0.1f);
    m_camera->setTarget(m_avion->position());
    m_camera->setTheta(qDegreesToRadians(90 - m_avion->lacet()));
    m_camera->setPhi(qDegreesToRadians(90 - m_avion->tangage())); // 90 - ...
    m_camera->update_position();
    QOpenGLWidget::update();
}

void WidgetOpenGL::mousePressEvent(QMouseEvent* event){
    lastPos = event->pos();
}

void WidgetOpenGL::mouseMoveEvent(QMouseEvent* event){
    float dx = (event->pos().x() - lastPos.x()) / static_cast<float> (width());
    float dy = (event->pos().y() - lastPos.y()) / static_cast<float> (height());

    m_camera->setTheta(m_camera->getTheta() + dx * 4);
    m_camera->setPhi(m_camera->getPhi() + dy * 4);
    QOpenGLWidget::update();
    lastPos = event->pos();
}

void WidgetOpenGL::addDrawable(Drawable *d){
    // this->makeCurrent();
//    d->initializeVAO();
//    d->setCamera(m_camera);
//    d->setLight(m_light);
}

Light *WidgetOpenGL::light() const
{
    return m_light;
}

void WidgetOpenGL::setLight(Light *light)
{
    m_light = light;
}

void WidgetOpenGL::keyPressEvent(QKeyEvent*event){
    float speed = 1.0f;
    switch(event->key()){
        case Qt::Key_Left:
            m_avion->tourne(0, speed, speed);
            break;
        case Qt::Key_Right:
            m_avion->tourne(0, -speed, -speed);
            break;
        case Qt::Key_Up:
            m_avion->tourne(-speed, 0, 0);
            break;
      //  case Qt::Key_Down:
         //   m_avion->tourne(speed, 0, 0);
         //   break;
        case Qt::Key_Space:
            m_avion->setVitesse(m_avion->vitesse() + 1.0);
            break;
        case Qt::Key_Backspace:
            m_avion->setVitesse(m_avion->vitesse() - 1.0);
            break;
        default:
            m_avion->setVitesse(m_avion->vitesse() * 0.98f);
            break;
    }

    update();

}

