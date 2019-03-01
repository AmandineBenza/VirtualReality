// Cours de Réalité Virtuelle
// leo.donati@univ-cotedazur.fr
//
// EPU 2018-19

#include "widgetopengl.h"

#define BUFFER_OFFSET(i)   ((char *)NULL + (i))

WidgetOpenGL::WidgetOpenGL(QWidget* parent)
    :QOpenGLWidget(parent),QOpenGLFunctions()
{
    m_programme = new QOpenGLShaderProgram(this);
    m_vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_vao = new QOpenGLVertexArrayObject(this);
    m_angleY = 30;
    m_angleX = 30;
    m_angleZ = 0;
    m_timer = new QTimer();
    rotationAnimation = false;
    fov = 30;
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

    initializeShader();
    initializeVAO();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));
    m_timer->start(0);

}

void WidgetOpenGL::initializeShader()
{
    bool resultat;
    m_programme->create();

    //Vertex Shader
    resultat = m_programme->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/simple.vert");
    if (!resultat)     {
        QMessageBox msg;
        msg.setWindowTitle("Vertex shader");
        msg.setText(m_programme->log());
        msg.exec();
    }

    //Fragment Shader
    resultat = m_programme->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/simple.frag");
    if (!resultat)     {
        QMessageBox msg;
        msg.setWindowTitle("Fragment shader");
        msg.setText(m_programme->log());
        msg.exec();
    }

    //Link
    resultat = m_programme->link();
    if (!resultat)     {
        QMessageBox msg;
        msg.setWindowTitle("Link du shader program");
        msg.setText(m_programme->log());
        msg.exec();
        exit(EXIT_FAILURE);
    }

    //Libération
    m_programme->release();
}

void WidgetOpenGL::initializeVAO()
{
    //Tableau des données : 3 sommets puis 3 couleurs
  /*  GLfloat vertex_data[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    }; */

    //CUBE
    QVector3D A(0,0,1);
    QVector3D B(1,0,1);
    QVector3D C(1,1,1);
    QVector3D D(0,1,1);
    QVector3D E(0,0,0);
    QVector3D F(1,0,0);
    QVector3D G(1,1,0);
    QVector3D H(0,1,0);

    //COULEURS
    QVector3D Red(1,0,0);
    QVector3D Blue(0,0,1);
    QVector3D Green(0,1,0);
    QVector3D Cyan(0,1,1);
    QVector3D Magenta(1,0,1);
    QVector3D Yellow(1,1,0);

    QVector3D vertex_data[] = {
            A, B, C, D, //avant
            B, F, G, C, //droite
            F, E, H, G, //arriere
            D, H, E, A, //gauche
            D, C, G, H, //haut
            E, F, B, A, //bas
            Red, Red, Red, Red,
            Blue, Blue, Blue, Blue,
            Green, Green, Green, Green,
            Cyan, Cyan, Cyan, Cyan,
            Magenta, Magenta, Magenta, Magenta,
            Yellow, Yellow, Yellow, Yellow
       };



    //creation du VA0 et du VBO
    m_vao->create();
    m_vbo->create();

    //Lien du VAO
    m_vao->bind();

        //lien du VBO
        m_vbo->bind();

        //Ecriture des données dans le VBO
        m_vbo->allocate(vertex_data,sizeof(vertex_data));
        m_vbo->setUsagePattern(QOpenGLBuffer::StaticDraw);

        //Lien entre VBO et les variables d'attribut du vertex shader
        m_programme->bind();

            //Lien avec les attributs du programme
            m_programme->setAttributeArray("pos", GL_FLOAT, BUFFER_OFFSET(0),3);
            m_programme->setAttributeArray("col", GL_FLOAT, BUFFER_OFFSET(24*sizeof(QVector3D)),3);

            //Activation des attributs
            m_programme->enableAttributeArray("pos");
            m_programme->enableAttributeArray("col");

        m_programme->release();

        //Liberation
        m_vbo->release();
    m_vao->release();

}



void WidgetOpenGL::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Définition de la matrice de projetcion
    QMatrix4x4 proj = QMatrix4x4();
    GLfloat aspect = GLfloat(width())/height();
    proj.perspective(fov, aspect, 0.1f, 100.0f);

    //Définiion de la matrice de vue
    QMatrix4x4 vue = QMatrix4x4();
    vue.translate(0, 0, -4);

    //Définition de la matrice de placement
    QMatrix4x4 model = QMatrix4x4();
    model.rotate(m_angleX,0,1,0);
    model.rotate(m_angleY,1,0,0);
    model.rotate(m_angleZ,0,0,1);
    model.translate(-0.5,-0.5,-0.5);


    //Produit des trois matrices (dans ce sens!)
    QMatrix4x4 matrix = proj * vue * model;

    m_programme->bind();
    m_programme->setUniformValue("u_ModelViewProjectionMatrix", matrix);
    m_programme->setUniformValue("u_opacity", m_opacity);


    m_vao->bind();

    for(int i = 0; i < 6; i++) {
        glDrawArrays(GL_TRIANGLE_FAN, 4 * i, 4);
    }

    m_vao->release();
    m_programme->release();
}


void WidgetOpenGL::resizeGL(int width, int height)
{
    //transformation de viewport
    glViewport(0, 0, width, height);
}

void WidgetOpenGL::update()
{
    if(rotationAnimation) {
        m_angleY += 4;
    }

    QOpenGLWidget::update();
}

void WidgetOpenGL::mousePressEvent(QMouseEvent* event){
    lastPos = event->pos();
}
void WidgetOpenGL::mouseMoveEvent(QMouseEvent* event){
    float dx = (event->pos().x() - lastPos.x()) / static_cast<float> (width());
    float dy = (event->pos().y() - lastPos.y()) / static_cast<float> (height());

    if(event->buttons() == Qt::RightButton) {
        m_angleX += dx*180;
        m_angleY += dy*180;
    }

     QOpenGLWidget::update();
     lastPos = event->pos();

}

void WidgetOpenGL::changeFov(int i){
    if(i < 10) i = 10;
    if(i > 120) i = 120;
    fov = i;
}

void WidgetOpenGL::startAnimation(){
    rotationAnimation = !rotationAnimation;
}

void WidgetOpenGL::changeOpacity(int i){
    if(i < 1) i = 1;
    if(i > 100) i= 100;
    m_opacity = i * 0.01f;

}
