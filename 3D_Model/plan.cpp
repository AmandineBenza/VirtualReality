// Cours de Réalité Virtuelle
// leo.donati@unice.fr
//
// EPU 2017-18
//
// TP8

#include "plan.h"

Plan::Plan()
    :Drawable()
{
    m_ibo = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);

    largeur = 10;
    longueur = 10;
    segLargeur = 20;
    segLongueur = 20;
}

Plan::~Plan()
{
    delete m_ibo;
}

void Plan::initializeVAO()
{
    nbSommets = (segLargeur+1)*(segLongueur + 1);
    int nbTriangles = 2*(segLargeur)*(segLongueur);
    nbIndices = 3*nbTriangles;

    QVector3D* vertex_data = new QVector3D[nbSommets*3];
    GLushort* index_data = new GLushort[nbIndices];

    GLfloat posX = -this->largeur/2;
    GLfloat posY = 0;
    GLfloat posZ = -this->longueur/2;

    //Position
    for (int i=0; i<= segLongueur; i++)
    {
        for (int j = 0; j <= segLargeur; j++)
        {
            //coord 3D
            vertex_data[i*(segLargeur+1) + j] = QVector3D(posX+i*longueur/segLongueur, posY, posZ+j*largeur/segLargeur );
        }
    }

    //Coordonnées texture
    for (int i=0; i<= segLongueur; i++)
    {
        for (int j = 0; j <= segLargeur; j++)
        {
            //coord texture
            vertex_data[nbSommets + i*(segLargeur+1) + j] = QVector3D(i/((float)segLongueur), j/((float)segLargeur), 0 );
        }
    }

    //Normales
    for (int i=0; i<= segLongueur; i++)
    {
        for (int j = 0; j <= segLargeur; j++)
        {
            //coord texture
            vertex_data[nbSommets*2 + i*(segLargeur+1) + j] = QVector3D(0, 1, 0 );
        }
    }


    //Indices
    for (int i=0; i< segLongueur; i++)
    {
        for (int j = 0; j < segLargeur; j++)
        {
            index_data[6*(i*(segLargeur) + j)    ] = i*(segLargeur+1) + j;
            index_data[6*(i*(segLargeur) + j) + 1] = (i+1)*(segLargeur+1) + j;
            index_data[6*(i*(segLargeur) + j) + 2] = (i+1)*(segLargeur+1) + j + 1;
            index_data[6*(i*(segLargeur) + j) + 3] = i*(segLargeur+1) + j;
            index_data[6*(i*(segLargeur) + j) + 4] = (i+1)*(segLargeur+1) + j + 1;
            index_data[6*(i*(segLargeur) + j) + 5] = i*(segLargeur+1) + j + 1;
        }
    }

    initializeOpenGLFunctions();
    initializeShader(":/shaders/plan.vert", ":/shaders/plan.frag");

    //Génération du VAO et du VBO
    m_vao->create();
    m_vbo->create();
    m_ibo->create();

    //Lien du VAO
    m_vao->bind();

    //Liaison du VBO
    m_vbo->bind();

    //Ecriture des données dans le VBO
    m_vbo->allocate(vertex_data,3*nbSommets*sizeof(QVector3D));
    m_vbo->setUsagePattern(QOpenGLBuffer::StaticDraw);

    m_ibo->bind();
    m_ibo->allocate(index_data,nbIndices*sizeof(GLuint));
    m_ibo->setUsagePattern(QOpenGLBuffer::StaticDraw);

    //Lien entre VBO et les variables d'attribut du vertex shader
    m_programme->bind();
        m_programme->setAttributeArray("pos", GL_FLOAT, BUFFER_OFFSET(0),3);
        m_programme->setAttributeArray("tex", GL_FLOAT, BUFFER_OFFSET(nbSommets*sizeof(QVector3D)),3);
        m_programme->setAttributeArray("normal", GL_FLOAT, BUFFER_OFFSET(2*nbSommets*sizeof(QVector3D)),3);

        //Activation des attributs
        m_programme->enableAttributeArray("pos");
        m_programme->enableAttributeArray("tex");
        m_programme->enableAttributeArray("normal");
    m_programme->release();

    //Libération
    m_vao->release();

    delete[] index_data;
    delete[] vertex_data;
}

void Plan::draw()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);

    //Activation de la tetxure
    glEnable(GL_TEXTURE_2D);

    glActiveTexture(GL_TEXTURE0);
    m_texture->bind();
    m_texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    m_texture->setMagnificationFilter(QOpenGLTexture::Linear);

    QMatrix4x4 model, vue, proj;
    proj = m_camera->projection();
    vue = m_camera->view();
    model = this->world();

    m_programme->bind();

    m_programme->setUniformValue("u_model", model);
    m_programme->setUniformValue("u_view", vue);
    m_programme->setUniformValue("u_projection", proj);

    m_programme->setUniformValue("texture0",0);

    m_programme->setUniformValue("light_ambient_color", m_light->getAmbient_color());
    m_programme->setUniformValue("light_diffuse_color", m_light->getDiffuse_color());
    m_programme->setUniformValue("light_specular_color", m_light->getSpecular_color());
    m_programme->setUniformValue("light_specular_strength", m_light->getSpecular_strength());
    m_programme->setUniformValue("light_position", m_light->getLight_position());
    m_programme->setUniformValue("view_position", QVector3D());
    m_programme->setUniformValue("u_opacity", 1.0f);
    m_programme->setUniformValue("height_factor",50.0f);

    //Liaison du VAO
    m_vao->bind();

    glActiveTexture(GL_TEXTURE1);
    m_heightmap->bind();
    m_heightmap->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    m_heightmap->setMagnificationFilter(QOpenGLTexture::Linear);
    m_programme->setUniformValue("texture1",1);
    m_programme->setUniformValue("view_position",m_camera->position());


    //Commande de dessin
    glDrawElements(GL_TRIANGLES, nbIndices, GL_UNSIGNED_SHORT,0);

    //Libération
    m_vao->release();
    m_programme->release();

    if (m_texture)
        m_texture->release();
}

void Plan::setTexture(QString textureFilename)
{
    m_texture = new QOpenGLTexture(QImage(textureFilename));
}

void Plan::setHeightmap(QString textureFilename){
    m_heightmap = new QOpenGLTexture(QImage(textureFilename));
}

float Plan::getLargeur() const
{
    return largeur;
}

void Plan::setLargeur(float value)
{
    largeur = value;
}

float Plan::getLongueur() const
{
    return longueur;
}

void Plan::setLongueur(float value)
{
    longueur = value;
}

int Plan::getSegLargeur() const
{
    return segLargeur;
}

void Plan::setSegLargeur(int value)
{
    segLargeur = value;
}


int Plan::getSegLongueur() const
{
    return segLongueur;
}

void Plan::setSegLongueur(int value)
{
    segLongueur = value;
}


