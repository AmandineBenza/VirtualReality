// Cours de Réalité Virtuelle
// leo.donati@univ-cotedazur.fr
//
// EPU 2018-19

varying vec3 frag_pos;
varying vec3 out_normal;
varying mediump vec2 tex_coord;

uniform sampler2D texture0;
uniform vec4 light_ambient_color;
uniform vec4 light_diffuse_color;
uniform vec4 light_specular_color;
uniform float light_specular_strength;
uniform vec3 light_position;
uniform vec3 view_position;
uniform float opacity;

void main(void)
{
    vec4 out_tex = texture2D(texture0, tex_coord);

    vec4 ambient = out_tex * light_ambient_color;

    vec3 norm = normalize(out_normal);
    vec3 lightdir = normalize(light_position - frag_pos);
    float coeff_diffusion = max(dot(lightdir, norm), 0.0);
    vec4 diffuse = (coeff_diffusion * light_diffuse_color) * out_tex;

    vec3 viewdir = normalize(frag_pos - view_position);
    vec3 reflectdir = reflect(lightdir, norm);
    float coeff_specular = pow(max(dot(viewdir, reflectdir), 0.0), light_specular_strength);
    vec4 specular = (coeff_specular * light_specular_color) * out_tex;

    gl_FragColor = (ambient + diffuse + specular);
    gl_FragColor.a = opacity;
}
