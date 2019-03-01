// Cours de Réalité Virtuelle
// leo.donati@unice.fr
//
// 2016_2017
//
// Correction TP3


#include "drawable.h"

Drawable::Drawable()
    : QOpenGLFunctions(),
      m_position(0.0f,0.0f,0.0f),
      m_roulis(0.0f),
      m_tangage(0.0f),
      m_lacet(0.0f)
{
    m_programme = new QOpenGLShaderProgram();
    m_vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_vao = new QOpenGLVertexArrayObject();
}

Drawable::~Drawable()
{
    m_programme->removeAllShaders();
    delete m_programme;
    delete m_vbo;
    delete m_vao;
}

void Drawable::initializeShader(QString vs, QString fs)
{
    initializeOpenGLFunctions();

    bool resultat;
    m_programme->create();

    //Vertex Shader
    resultat = m_programme->addShaderFromSourceFile(QOpenGLShader::Vertex, vs);
    if (!resultat)     {
        QMessageBox msg;
        msg.setWindowTitle("Vertex shader");
        msg.setText(m_programme->log());
        msg.exec();
    }

    //Fragment Shader
    resultat = m_programme->addShaderFromSourceFile(QOpenGLShader::Fragment, fs);
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



void Drawable::setPosition(GLfloat x, GLfloat y, GLfloat z)
{
    m_position = QVector3D(x, y,z);
}

void Drawable::setOrientation(GLfloat roulis, GLfloat tangage, GLfloat lacet)
{
    m_roulis = roulis;
    m_tangage = tangage;
    m_lacet = lacet;
}



Camera *Drawable::camera() const
{
    return m_camera;
}

void Drawable::setCamera(Camera *camera)
{
    m_camera = camera;
}

QMatrix4x4 Drawable::world(){
    //Définition de la matrice de placement
    QMatrix4x4 model = QMatrix4x4();
    model.translate(m_position);
    model.rotate(m_tangage,1,0,0);
    model.rotate(m_lacet,0,1,0);
    model.rotate(m_roulis,0,0,1);
    return model;
}

void Drawable::tourne(float a, float b, float c){
    m_tangage += b;
    m_roulis += a;
    m_lacet += c;
}

