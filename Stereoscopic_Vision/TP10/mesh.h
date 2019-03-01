#ifndef MESH_H
#define MESH_H
#include "drawable.h"

struct Vertex {
QVector3D Position;
QVector3D Normal;
QVector2D TexCoords;};

class Mesh : public Drawable
{

public:
    Mesh();

    int nbVertices() const;
    void setNbVertices(int nbVertices);

    int nbIndices() const;
    void setNbIndices(int nbIndices);

    QOpenGLTexture *texture() const;
    void setTexture(QString textureFileName);

    void initializeVAO(QVector<Vertex>*vec,QVector<GLuint>*ind);
    void draw();

private:
    int m_nbVertices;
    int m_nbIndices;
    QOpenGLBuffer*  m_ibo;
    QOpenGLTexture* m_texture;

};

#endif // MESH_H
