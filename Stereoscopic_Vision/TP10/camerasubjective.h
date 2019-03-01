#ifndef CAMERASUBJECTIVE_H
#define CAMERASUBJECTIVE_H

#include "camerastereo.h"
#include <QElapsedTimer>

class CameraSubjective : public CameraStereo{
public:
    CameraSubjective();

    float tangage() const;
    void setTangage(float tangage);

    float lacet() const;
    void setLacet(float lacet);

    void updateTarget();
    void avance(float dist);
    void lateral(float dist);
    void vertical(float dist);
    void jump();
    void updateJump();
    void verticalJump(float dist);


private:
    float m_tangage;
    float m_lacet;

    bool m_jumping;
    bool m_going_down;
    float m_start_jump_y;
    float m_speed;
    float m_max_jump_height;

};

#endif // CAMERASUBJECTIVE_H
