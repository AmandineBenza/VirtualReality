// Cours de Réalité Virtuelle
// leo.donati@univ-cotedazur.fr
//
// EPU 2018-19
//

attribute vec3 pos;
attribute vec2 tex;
attribute vec3 normal;

varying mediump vec2 tex_coord;
varying vec3 frag_pos;
varying vec3 out_normal;

uniform mat4 view;
uniform mat4 model;
uniform mat4 projection;

void main(void)
{
   gl_Position = projection * view * model * vec4(pos, 1);
   frag_pos = vec3(view * model * vec4(pos,1));
   out_normal = vec3(view * model * vec4(normal,0));
   tex_coord = tex.st;

}


