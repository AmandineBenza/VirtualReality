// Cours de Réalité Virtuelle
// leo.donati@unice.fr
//
// Inspiré du travail de Joey de Vries sur learnopengl.com
//
// 2017_2018
//

#include "model.h"

Model::Model(QString nomFichier)
    :Drawable(), m_meshes(), m_repertoire(nomFichier)
{
    m_repertoire.makeAbsolute();
    QString filePath = m_repertoire.path();
    m_repertoire.cdUp();
    loadModel(filePath);

}


void Model::loadModel(QString nomFichier)
{
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(nomFichier.toStdString(), aiProcess_Triangulate | aiProcess_FlipUVs);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        qDebug() << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
        return;
    }

    // Lance le traitement de tous les noeuds de la scène
    processNode(scene->mRootNode, scene);

    // Stocke le nombre de maillages contenu dans la scène
    m_nbMeshes = m_meshes.size();
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
    // On parcourt tous les maillages rattachés à ce noeud
    for(GLuint i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        //on convertit mesh qui est une instance de aiMesh
        //en maillage qui est une instance de Mesh
        Mesh* maillage = processMesh(mesh, scene);

        //on récupère l'information de placement de ce noeud
        //pour en faire la matrice world du maillage
        aiMatrix4x4t<float> mat =  node->mTransformation;
        aiVector3t<float> scal;
        aiQuaterniont<float> rot;
        aiVector3t<float> pos;
        mat.Decompose(scal, rot, pos);
        maillage->setPosition(pos.x, pos.y, pos.z);

        //on ajoute maillage au tableau des Mesh
        m_meshes.append(maillage);
    }
    //On appelle récursivement la fonction sur tous les fils du noeud
    for(GLuint i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

Mesh* Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    QVector<Vertex>* vertices = new QVector<Vertex>();
    QVector<GLuint>* indices = new QVector<GLuint>();

    //On travaille sur les sommets du aiMesh
    for(GLuint i = 0; i < mesh->mNumVertices; i++)
    {
        //Le Vertex qui va contenis les infos
        Vertex vertex;

        //On copie les coordonnées
        QVector3D vector;
        vector.setX(mesh->mVertices[i].x);
        vector.setY(mesh->mVertices[i].y);
        vector.setZ(mesh->mVertices[i].z);
        vertex.Position = vector;

        //on copie les normales
        QVector3D normal;
        normal.setX(mesh->mNormals[i].x);
        normal.setX(mesh->mNormals[i].y);
        normal.setX(mesh->mNormals[i].z);
        vertex.Normal = normal;

        //on copie les coordonnées textures
        QVector2D tex(0, 0);
        if(mesh->mTextureCoords[0]) // s'il y en a
        {
            tex.setX(mesh->mTextureCoords[0][i].x);
            tex.setY(mesh->mTextureCoords[0][i].y);
        }
        // sinon c'est (0, 0)
        vertex.TexCoords = tex;

        //Notre vertex est pret on le met dans le tableau
        vertices->append(vertex);
    }
    //On travaille sur les indices
    for(GLuint i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(GLuint j = 0; j < face.mNumIndices; j++)
            indices->append(face.mIndices[j]);
    }

    //On construit le Mesh
    Mesh* maillage = new Mesh();
    maillage->initializeVAO(vertices, indices);

    //Traitement du materiau
    if(mesh->mMaterialIndex >= 0)
    {
        //On récupère le matériau de l'aiMesh
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        //On en extrait le nom du fihier texture
        aiString str;
        material->GetTexture(aiTextureType_DIFFUSE,0, &str);
        //On l'utilise pour initialiser la texture de maillage
        maillage->setTexture(m_repertoire.filePath(str.C_Str()));
      //  maillage->setTexture(":models/GeeBee.jpg");
    }

    //On passe au maillage la valeur de la lumière et de la camera du modèle
    maillage->setLight(m_light);
    maillage->setCamera(m_camera);

    return maillage;
}

void Model::draw() {
    for(Mesh* mesh : m_meshes) {
        mesh->draw();
    }
}

void Model::tourne(float a, float b, float c) {
    m_tangage += a;
    m_lacet += b;
    m_roulis += c;

    for(Mesh* mesh : m_meshes) {
        mesh->tourne(a,b,c);
    }
}

void Model::setCamera(Camera *cam) {
    m_camera = cam;
    for(Mesh* mesh : m_meshes) {
        mesh->setCamera(m_camera);
    }
}

void Model::setScale(const GLfloat scale){
    m_scale = scale;
    for(Mesh* mesh : m_meshes) {
        mesh->setScale(m_scale);
    }
}

void Model::setLight(Light *light) {
    m_light = light;
    for(Mesh* mesh : m_meshes) {
        mesh->setLight(m_light);
    }
}
