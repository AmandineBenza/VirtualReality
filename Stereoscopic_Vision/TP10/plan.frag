// Cours de Realite Virtuelle
// leo.donati@unice.fr
//
// 2017_2018
//
// TP8

varying vec2 out_tex;
varying vec3 frag_pos;
varying vec3 out_normal;

uniform sampler2D texture0;

uniform vec4 light_ambient_color;
uniform vec4 light_diffuse_color;
uniform vec4 light_specular_color;
uniform float light_specular_strength;
uniform vec3 light_position;
uniform vec3 view_position;
uniform float u_opacity;

void main(void)
{
    //Lecture de la texture
    vec4 color = texture2D(texture0, out_tex);

    //calcul de la composante ambiante
    vec4 ambient = color * light_ambient_color;

    //calcul de la composante diffuse
    vec3 norm = normalize(out_normal);
    vec3 lightdir = normalize(light_position - frag_pos);
    float coeff_diffusion = max(dot(lightdir, norm), 0.0);
    vec4 diffuse = (coeff_diffusion * light_diffuse_color) * color;

    //calcul de la composante spéculaire
    vec3 viewdir = normalize(frag_pos - view_position);
    vec3 reflectdir = reflect(lightdir, norm);
    float coeff_specular = pow(max(dot(viewdir, reflectdir), 0.0), light_specular_strength);
    vec4 specular = (coeff_specular * light_specular_color) * vec4(1.0, 1.0, 1.0, 1.0);

    //couleur finale
    gl_FragColor = ambient + diffuse + specular;
    gl_FragColor.a = 1.0;

    float coef_attenuation = 50.0/(distance(light_position,frag_pos));

    gl_FragColor.r = gl_FragColor.r * coef_attenuation;
    gl_FragColor.g = gl_FragColor.g * coef_attenuation;
    gl_FragColor.b = gl_FragColor.b * coef_attenuation;
}
