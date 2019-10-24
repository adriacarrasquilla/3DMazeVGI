//******** PRACTICA VISUALITZACIÓ GRÀFICA INTERACTIVA (EE-UAB)
//******** Entorn basic amb interfície MFC i Status Bar
//******** Enric Marti (Març 2017)
// gouraud_shdrML.frag: Fragment Program en GLSL per implementar il.luminacio de Gouraud

uniform sampler2D texture0;
uniform bool texture;

void main ()

{
    if (texture) {
// Intensitat amb textura
    vec4 colorT = texture2D(texture0,gl_TexCoord[0].st);
//    gl_FragColor = gl_Color * 0.3 + colorT * 1.0;
    gl_FragColor = gl_Color * colorT;
    }
    else {
// Intensitat sense textura
    gl_FragColor = gl_Color;   
    }

}
