// Cours de Réalité Virtuelle
// leo.donati@univ-cotedazur.fr
//
// EPU 2018-19

#include "widgetopengl.h"

#define BUFFER_OFFSET(i)   ((char *)NULL + (i))

WidgetOpenGL::WidgetOpenGL(QWidget* parent)
    :QOpenGLWidget(parent),QOpenGLFunctions()
{
    m_angleY = 30;
    m_angleX = 30;
    m_angleZ = 0;
    m_timer = new QTimer();
    rotationAnimation = false;
    m_opacity = 1.0f;
}

WidgetOpenGL::~WidgetOpenGL()
{
    m_programme->removeAllShaders();
    delete m_programme;
    delete m_vbo;
    delete m_vao;
}

void WidgetOpenGL::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0.8f,0.8f,0.8f,1.0f);  //gris clair

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));
    m_timer->start(0);
    m_camera = new CameraSpherique();
    m_camera->setAspect_ratio(GLfloat(width())/height());

    m_objets = QList<Drawable*>();
    m_light = new Light();

      SkyBox* skybox = new SkyBox();
      skybox->setPosition(0.0f,0.0f,0.0f);
      skybox->setOrientation(0.0f,0.0f,0.0f);
      skybox->initializeVAO();
      skybox->setCamera(m_camera);
      skybox->setTexture(":images/front",0);
      skybox->setTexture(":images/left",1);
      skybox->setTexture(":images/back",2);
      skybox->setTexture(":images/right",3);
      skybox->setTexture(":images/top",4);
      skybox->setTexture(":images/bottom",5);

 /*   Cube* m_cube = new Cube();
    m_cube->setOrientation(0.0f, 20.0f, 20.0f);
    m_cube->setPosition(0.0f,0.0f,0.0f);
    m_cube->initializeVAO();
    m_cube->setCamera(m_camera);

    CubeTex* cubetex = new CubeTex();
    cubetex->setPosition(2.0f,0.0f,0.0f);
    cubetex->setOrientation(0.0f, 20.0f, 20.0f);
    cubetex->setTexture(":images/cubeRose128");

    DeAJouer* dee = new DeAJouer();
    dee->setPosition(-2.0f,0.0f,0.0f);
    dee->setOrientation(0.0f, 20.0f, 20.0f);
    dee->setTexture(":images/texture_de"); */


    CubeEclaire* cubeeclaire = new CubeEclaire();
    cubeeclaire->setPosition(0.0f,0.0f,0.0f);
    cubeeclaire->setOrientation(0.0f, 0.0f, 0.0f);
    cubeeclaire->setLight(m_light);
    cubeeclaire->setTexture(":images/container");

    m_objets.append(skybox);
 //   m_objets.append(m_cube);
 //   addDrawable(cubetex);
 //   addDrawable(dee);
    addDrawable(cubeeclaire);
}

void WidgetOpenGL::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for(Drawable* object : m_objets) {
        object->draw();
    }
}

void WidgetOpenGL::resizeGL(int width, int height)
{
    //transformation de viewport
    glViewport(0, 0, width, height);
}

void WidgetOpenGL::update()
{

    if(rotationAnimation) {
        for(Drawable* object : m_objets) {
            if(object != m_objets[0]) {
                object->tourne(1.0f, 1.0f, 1.0f);
            }
        }
    }

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

void WidgetOpenGL::changeFov(int i){
    if(i < 10) i = 10;
    if(i > 120) i = 120;
    m_camera->setFov(i);
}

void WidgetOpenGL::startAnimation(){
    rotationAnimation = !rotationAnimation;
}

void WidgetOpenGL::changeOpacity(int i){

    //    if(i < 1) i = 1;
    //    if(i > 100) i= 100;
    //    m_opacity = i * 0.01f;

}

void WidgetOpenGL::addDrawable(Drawable *d){
    this->makeCurrent();
    d->initializeVAO();
    d->setCamera(m_camera);
    m_objets.append(d);
}

void WidgetOpenGL::reset(){
    Drawable* skybox = m_objets[0];
    m_objets.clear();
    m_objets.append(skybox);
}

Light *WidgetOpenGL::light() const
{
    return m_light;
}

void WidgetOpenGL::setLight(Light *light)
{
    m_light = light;
}
