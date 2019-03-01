#include "deAJouer.h"

DeAJouer::DeAJouer() : Drawable::Drawable()
{
}

void DeAJouer::setTexture(QString textureFilename) {
    m_texture = new QOpenGLTexture(QImage(textureFilename).mirrored());
}

QMatrix4x4 DeAJouer::world(){
    QMatrix4x4 model = Drawable::world();
    model.translate(-0.5, -0.5, -0.5);
    return model;
}

void DeAJouer::initializeVAO(){
    initializeOpenGLFunctions();
    initializeShader(":/shaders/texture.vert", ":/shaders/texture.frag");


    //CUBE
    QVector3D A(0,0,1);
    QVector3D B(1,0,1);
    QVector3D C(1,1,1);
    QVector3D D(0,1,1);
    QVector3D E(0,0,0);
    QVector3D F(1,0,0);
    QVector3D G(1,1,0);
    QVector3D H(0,1,0);

    // TEXTURE PART
    QVector3D SW(0,0,0);
    QVector3D NW(0,1,0);
    QVector3D NE(1,1,0);
    QVector3D SE(1,0,0);

    QVector3D vertex_data[] = {
            A, B, C, D, //avant
            B, F, G, C, //droite
            F, E, H, G, //arriere
            D, H, E, A, //gauche
            D, C, G, H, //haut
            E, F, B, A, //bas

            //Face de : SW, NW, NE, SE
            QVector3D(0,0.5,0), QVector3D(0,0.75,0), QVector3D(0.25,0.75,0), QVector3D(0.25,0.5,0),  //1 avant
            QVector3D(0.25,0.5,0), QVector3D(0.25,0.75,0), QVector3D(0.5,0.75,0), QVector3D(0.5,0.5,0), // 5 droite
            QVector3D(0.5,0.5,0), QVector3D(0.5,0.75,0),  QVector3D(0.75,0.75,0), QVector3D(0.75,0.5,0),//6 arriere
            QVector3D(0.75,0.5,0), QVector3D(0.75,0.75,0),  QVector3D(1,0.75,0), QVector3D(1,0.5,0),//2 gauche
            QVector3D(0,0.75,0), QVector3D(0,1,0), QVector3D(0.25,1,0), QVector3D(0.25,0.75,0), // 3 haut
            QVector3D(0,0.25,0), QVector3D(0,0.5,0), QVector3D(0.25,0.5,0), QVector3D(0.25,0.25,0)  // 4 bas

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
            m_programme->setAttributeArray("tex", GL_FLOAT, BUFFER_OFFSET(24*sizeof(QVector3D)),3);

            //Activation des attributs
            m_programme->enableAttributeArray("pos");
            m_programme->enableAttributeArray("tex");

        m_programme->release();

        //Liberation
        m_vbo->release();
    m_vao->release();



}

void DeAJouer::draw(){

    //Produit des trois matrices (dans ce sens!)
    QMatrix4x4 matrix = m_camera->projection() * m_camera->view() * this->world();

    m_programme->bind();
    m_programme->setUniformValue("u_ModelViewProjectionMatrix", matrix);
    m_programme->setUniformValue("u_opacity", 0.5f);

    m_vao->bind();

    m_texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    m_texture->setMagnificationFilter(QOpenGLTexture::Linear);      //Liaison de la texture
    m_texture->bind();     //Activation de la tetxure
    m_programme->setUniformValue("texture0",0);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);

    for(int i = 0; i < 6; ++i){
        glDrawArrays(GL_TRIANGLE_FAN, 4 * i, 4);
    }

    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);

    m_vao->release();
    m_programme->release();

}
