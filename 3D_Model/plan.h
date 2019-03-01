// Cours de Réalité Virtuelle
// leo.donati@unice.fr
//
// EPU 2017-18
//
// TP8

#ifndef PLAN_H
#define PLAN_H

#include <QOpenGLTexture>

#include "drawable.h"

class Plan : public Drawable
{
public:
    Plan();
    ~Plan();

    void initializeVAO();
    void draw();

    float getLargeur() const;
    void setLargeur(float value);
    float getLongueur() const;
    void setLongueur(float value);
    int getSegLargeur() const;
    void setSegLargeur(int value);
    int getSegLongueur() const;
    void setSegLongueur(int value);

    void setTexture(QString textureFilename);

    void setHeightmap(QString textureFilename);

protected:
    QOpenGLBuffer* m_ibo;   //encapsule l'index buffer
    QOpenGLTexture* m_texture;
    QOpenGLTexture* m_heightmap;

    GLfloat largeur;
    GLfloat longueur;
    GLint segLargeur;
    GLint segLongueur;
    GLint nbIndices;
    GLint nbSommets;
};

#endif // PLAN_H
