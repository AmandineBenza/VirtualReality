#ifndef CAMERASPHERIQUE_H
#define CAMERASPHERIQUE_H

#include "camera.h"

class CameraSpherique : public Camera{
public:
    CameraSpherique();

    QVector3D getCible() const;
    void setCible(const QVector3D &value);

    float getRho() const;
    void setRho(float rho);

    float getTheta() const;
    void setTheta(float theta);

    float getPhi() const;
    void setPhi(float phi);

private:
    float m_rho;
    float m_theta;
    float m_phi;

    QVector3D cible;

    void update_position();
};

#endif // CAMERASPHERIQUE_H
