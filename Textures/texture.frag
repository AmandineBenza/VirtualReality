// Cours de Réalité Virtuelle
// leo.donati@univ-cotedazur.fr
//
// EPU 2018-19

varying mediump vec4 out_color;
varying mediump vec2 tex_coord;
uniform sampler2D texture0;

void main(void)
{    
    gl_FragColor = texture2D(texture0, tex_coord);

}
