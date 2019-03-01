#include "light.h"

Light::Light()
{
    ambient_color = QColor(23,23,23,255);
    diffuse_color = QColor(255,255,255,255);
    specular_color = QColor(255,255,0,255);
    light_position = QVector3D(0,0,2);
    specular_strength  = 250.0f;
}

QColor Light::getAmbient_color() const
{
    return ambient_color;
}

void Light::setAmbient_color(const QColor &value)
{
    ambient_color = value;
}

QColor Light::getSpecular_color() const
{
    return specular_color;
}

void Light::setSpecular_color(const QColor &value)
{
    specular_color = value;
}

QColor Light::getDiffuse_color() const
{
    return diffuse_color;
}

void Light::setDiffuse_color(const QColor &value)
{
    diffuse_color = value;
}

QVector3D Light::getLight_position() const
{
    return light_position;
}

void Light::setLight_position(const QVector3D &value)
{
    light_position = value;
}

float Light::getSpecular_strength() const
{
    return specular_strength;
}

void Light::setSpecular_strength(float value)
{
    specular_strength = value;
}
