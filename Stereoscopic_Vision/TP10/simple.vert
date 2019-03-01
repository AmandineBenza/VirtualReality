// Cours de Réalité Virtuelle
// leo.donati@univ-cotedazur.fr
//
// EPU 2018-19
//

attribute vec3 pos;
attribute vec3 col;
varying mediump vec4 out_color;
uniform mat4 u_ModelViewProjectionMatrix;
uniform float u_opacity;

void main(void)
{
   gl_Position = u_ModelViewProjectionMatrix * vec4(pos, 1);
   out_color = vec4(col,u_opacity);
}
