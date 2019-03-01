#ifndef CAMERASPHERIQUE_H
#define CAMERASPHERIQUE_H

#include "camerastereo.h"

class CameraSpherique : public CameraStereo{
public:
    CameraSpherique();

    float getRho() const;
    void setRho(float rho);

    float getTheta() const;
    void setTheta(float theta);

    float getPhi() const;
    void setPhi(float phi);

    void update_position();
    void setPosition(const QVector3D &position);

private:
    float m_rho;
    float m_theta;
    float m_phi;

};

#endif // CAMERASPHERIQUE_H
