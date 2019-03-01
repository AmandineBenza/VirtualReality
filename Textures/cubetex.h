#ifndef CUBETEX_H
#define CUBETEX_H
#include "drawable.h"

class CubeTex : public Drawable
{
public:
    CubeTex();
    ~CubeTex();
    void setTexture(QString textureFilename);
    QMatrix4x4 world();
    void initializeVAO();
    void draw();

    private :
    QOpenGLTexture* m_texture;
};

#endif // CUBETEX_H
