// Cours de Réalité Virtuelle
// leo.donati@unice.fr
//
// Inspiré du travail de Joey de Vries sur learnopengl.com
//
// 2017_2018
//

#ifndef MODEL_H
#define MODEL_H

#include <QString>
#include <QDir>
#include <QVector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/matrix4x4.h>
#include <QtDebug>

#include "drawable.h"
#include "camera.h"
#include "light.h"
#include "mesh.h"


class Model : public Drawable
{
public:
    //constructeur (fourni)
    Model(QString nomFichier);

    void draw();
    void setCamera(Camera* cam);
    void setLight(Light* light);
    void tourne(float a, float b, float c);
    void setScale(GLfloat scale);

protected:
    //variables membres
    QVector<Mesh*> m_meshes;
    QDir m_repertoire;
    int m_nbMeshes;

private:
    //Méthodes privées fournies
    void loadModel(QString nomFichier);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh* processMesh(aiMesh* mesh, const aiScene* scene);
};

#endif // MODEL_H
