#include "avion.h"

Avion::Avion() : Model::Model("C:/Users/user/Desktop/RealiteVirtuelle/TP7/GeeBee2.x")
{
    m_vitesse = 0.0f;
    m_tangage = 0.0f;
    m_roulis = 0.0f;
    m_lacet = 0.0f;
    m_position = QVector3D(0,0,0);
    m_scale = 0.5f;
}


float Avion::vitesse() const
{
    return m_vitesse;
}

void Avion::setVitesse(float vitesse)
{
    m_vitesse = vitesse;
}

void Avion::avance(float deltaT){
   float dv = deltaT * m_vitesse;

   /* float dz = dv * -qCos(qDegreesToRadians(m_lacet)) * qCos(qDegreesToRadians(m_tangage));
    float dy = dv * qSin(qDegreesToRadians(m_lacet)) * qCos(qDegreesToRadians(m_tangage));
    float dx = dv * qSin(qDegreesToRadians(m_tangage));

    QVector3D variation(dx, dy, dz);

    m_position += variation;

    for(Mesh* mesh : m_meshes){
        QVector3D newPos = mesh->position() + variation;
        mesh->setPosition(newPos.x(), newPos.y(), newPos.z());
    }*/

    GLfloat dx = dv * sin(qDegreesToRadians(m_lacet)) * -1;
    GLfloat dy = dv * qDegreesToRadians(m_tangage);
    GLfloat dz = dv * cos(qDegreesToRadians(m_lacet)) * -1;

    QVector3D newPos(dx, dy, dz);

    m_position += newPos;

    for(Mesh* mesh : m_meshes){
        QVector3D newPosMesh = mesh->position() + newPos;
        mesh->setPosition(newPosMesh.x(), newPosMesh.y(), newPosMesh.z());
    }

    //Helice
    Mesh* helice = m_meshes[2];
    helice->tourne(0.0, 0.0, m_vitesse * 2);

    m_roulis = m_roulis * 0.98f;

    for(int i = 0; i < m_meshes.size(); ++i){
        if(i == 2) continue;
        m_meshes.at(i)->setRoulis(m_meshes.at(i)->roulis() * 0.98f);
    }
}

void Avion::accelere(float acc){
    m_vitesse += acc;
}
