#ifndef CAMERASTEREO_H
#define CAMERASTEREO_H
#include "camera.h"

//#define RV_CAMERA_MONO 0;
//#define RV_CAMERA_LEFT 1;
//#define RV_CAMERA_RIGHT 2;

enum RV_CAMERA { MONO, LEFT, RIGHT };

class CameraStereo : public Camera {
public:
    CameraStereo();

    float distanceInterOeil() const;
    void setDistanceInterOeil(float distanceInterOeil);

    float distanceFocale() const;
    void setDistanceFocale(float distanceFocale);

    int typeCamera() const;
    void setTypeCamera(int typeCamera);

    QMatrix4x4 vueGauche();
    QMatrix4x4 projectionGauche();
    QMatrix4x4 vueDroite();
    QMatrix4x4 projectionDroite();

    QMatrix4x4 view();
    QMatrix4x4 projection();

private:
    float m_distanceInterOeil;
    float m_distanceFocale;
    int m_typeCamera;


};

#endif // CAMERASTEREO_H
