//******** PRACTICA VISUALITZACIÓ GRÀFICA INTERACTIVA (EE-UAB)
//******** Entorn basic amb interfície MFC i Status Bar
//******** Enric Marti (Setembre 2018)
// phong_shdrML.vert: Vertex Program en GLSL per implementar il.luminacio de Phong

uniform bool texture;
uniform sampler2D texture0;
uniform bool sw_intensity[4];
varying vec3 vertexPV;
//varying vec3 lightVec[gl_MaxLights];
varying vec3 normVec;

void main()
{
    normVec = normalize(gl_NormalMatrix * gl_Normal);
    vertexPV = vec3(gl_ModelViewMatrix * gl_Vertex);
//    for (int i=0;i<gl_MaxLights;i++) {
//    	lightVec[i] = vec3(gl_LightSource[i].position.xyz - vertexPV);
//    	}

// Textura
    if (texture) {
        gl_TexCoord[0] = gl_MultiTexCoord0;
    }
    
// Transformacio de Visualitzacio amb MODELVIEW i GLPROJECTION
//    gl_Position=gl_ModelViewProjectionMatrix * gl_Vertex;
    gl_Position = ftransform();

// Calcul intensitat final del vertex
    gl_FrontColor = gl_Color;
}

