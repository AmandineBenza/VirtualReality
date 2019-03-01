// Cours de Réalité Virtuelle
// leo.donati@univ-cotedazur.fr
//
// EPU 2018-19
//

attribute vec3 pos;
attribute vec3 tex;
varying mediump vec2 tex_coord;
uniform mat4 u_ModelViewProjectionMatrix;
uniform float u_opacity;

void main(void)
{
   gl_Position = u_ModelViewProjectionMatrix * vec4(pos, 1);
   tex_coord = tex.st;
}
