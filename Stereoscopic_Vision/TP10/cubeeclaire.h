#ifndef CUBEECLAIRE_H
#define CUBEECLAIRE_H
#include "drawable.h"

class CubeEclaire : public Drawable
{
public:
    CubeEclaire();
    ~CubeEclaire();
    void setTexture(QString textureFilename);
    QMatrix4x4 world();
    void initializeVAO();
    void draw();

    private :
    QOpenGLTexture* m_texture;
};

#endif // CUBETEX_H
