#ifndef CUBE_H
#define CUBE_H
#include "drawable.h"

class Cube : public Drawable
{
public:
    Cube();
    ~Cube();
    virtual void initializeVAO();
    virtual void draw();
    virtual QMatrix4x4 world();
    void setOpacity(int i);

};

#endif // CUBE_H
