#ifndef LIGHT_H
#define LIGHT_H

#include <QColor>
#include <QVector3D>


class Light
{
public:
    Light();

    QColor getAmbient_color() const;
    void setAmbient_color(const QColor &value);

    QColor getSpecular_color() const;
    void setSpecular_color(const QColor &value);

    QColor getDiffuse_color() const;
    void setDiffuse_color(const QColor &value);

    QVector3D getLight_position() const;
    void setLight_position(const QVector3D &value);

    float getSpecular_strength() const;
    void setSpecular_strength(float value);

private:
    QColor ambient_color;
    QColor specular_color;
    QColor diffuse_color;
    QVector3D light_position;
    float specular_strength;


};

#endif // LIGHT_H
