#ifndef AVION_H
#define AVION_H

#include "model.h"

class Avion : public Model
{
public:
    Avion();

    float vitesse() const;
    void setVitesse(float vitesse);
    void avance(float deltaT);
    void accelere(float acc);

private :
    float m_vitesse;
};

#endif // AVION_H
