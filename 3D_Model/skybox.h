#ifndef SKYBOX_H
#define SKYBOX_H
#include "drawable.h"

class SkyBox : public Drawable
{
public:
    SkyBox();
    ~SkyBox();
    void setTexture(QString textureFilename, int face);
    QMatrix4x4 world();
    void initializeVAO();
    void draw();

    private :
    QOpenGLTexture* m_texture[6];
};

#endif // CUBETEX_H
