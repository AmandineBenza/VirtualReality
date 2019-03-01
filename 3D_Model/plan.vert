// Cours de Réalité Virtuelle
// leo.donati@unice.fr
//
// 2017_2018
//
// TP8

attribute vec3 pos;
attribute vec3 tex;
attribute vec3 normal;

varying vec2 out_tex;
varying vec3 frag_pos;
varying vec3 out_normal;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;
uniform sampler2D texture1;
uniform float height_factor;

void main(void)
{
   vec4 machin = texture2D(texture1,tex.st);
   float hauteur = machin.r;
   vec4 coord = u_model * vec4(pos, 1.0);
   coord.y += hauteur * height_factor;
   gl_Position = u_projection * u_view * coord;
   frag_pos = vec3(coord);

   out_normal = vec3(u_model * vec4(normal,0));
   out_tex = tex.st;
}

