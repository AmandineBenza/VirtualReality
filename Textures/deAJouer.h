#ifndef DEAJOUER_H
#define DEAJOUER_H
#include "drawable.h"

class DeAJouer : public Drawable
{
public:
    DeAJouer();
    ~DeAJouer();
    void setTexture(QString textureFilename);
    QMatrix4x4 world();
    void initializeVAO();
    void draw();

    private :
    QOpenGLTexture* m_texture;
};

#endif // CUBETEX_H
