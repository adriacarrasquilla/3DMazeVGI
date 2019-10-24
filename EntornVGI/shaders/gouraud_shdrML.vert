//******** PRACTICA VISUALITZACIÓ GRÀFICA INTERACTIVA (EE-UAB)
//******** Entorn basic amb interficie MFC i Qt amb Status Bar
//******** Enric Marti (Desembre 2016)
// gouraud_shdrML.vert: Vertex Program en GLSL per implementar il.luminacio de Gouraud

uniform sampler2D texture0;
uniform bool texture;
uniform bool sw_intensity[4];
uniform bool sw_lights[gl_MaxLights];

void main ()
{

//-L14- Calcul variables previes.
    vec3 N = normalize(gl_NormalMatrix * gl_Normal);
    vec3 vertexPV = vec3(gl_ModelViewMatrix * gl_Vertex);
//  vec3 L = normalize(gl_LightSource[0].position.xyz - vertexPV);
//-L18- Multiples llums
    vec3 ILlums = vec3 (0.0,0.0,0.0);
    vec3 Idiffuse = vec3 (0.0,0.0,0.0);
    vec3 Ispecular = vec3 (0.0,0.0,0.0);

//-L23- Textura
    if (texture) {
        gl_TexCoord[0] = gl_MultiTexCoord0;
    }

//-L28- Compute emissive term
    vec3 Iemissive = vec3 (0.0,0.0,0.0);
    if (sw_intensity[0])  Iemissive = gl_FrontMaterial.emission.xyz;

//-L32- Compute ambient term
    vec3 Iambient = vec3 (0.0,0.0,0.0);
    if (sw_intensity[1]) {
        Iambient = gl_FrontMaterial.ambient.rgb * gl_Color.rgb * gl_LightModel.ambient.rgb;
        Iambient = clamp(Iambient, 0.0, 1.0);
    }

//-L39- Multiples llums
    for (int i=0;i<gl_MaxLights;i++) {
	if (sw_lights[i]) { 
		//-L42- Compute the diffuse term
    		Idiffuse = vec3 (0.0,0.0,0.0);
		vec3 L = normalize(gl_LightSource[i].position.xyz - vertexPV);
     		if (sw_intensity[2]) {
        		float diffuseLight = max(dot(N, L), 0.0);
        		Idiffuse = gl_FrontMaterial.diffuse.rgb * gl_Color.rgb * gl_LightSource[i].diffuse.rgb * diffuseLight;
        		Idiffuse = clamp(Idiffuse, 0.0, 1.0);
     			}

		//-L51- Compute the specular term
    		Ispecular = vec3 (0.0,0.0,0.0);
    		if (sw_intensity[3]) {
        		vec3 V = normalize(-vertexPV);
        		vec3 R = normalize (-reflect(L,N));
        		float specularLight = pow(max(dot(R, V), 0.0), gl_FrontMaterial.shininess);
			// if  (diffuseLight <= 0.0) specularLight = 0.0;
        		Ispecular = gl_FrontMaterial.specular.rgb * gl_Color.rgb * gl_LightSource[i].specular.rgb * specularLight;
        		Ispecular = clamp(Ispecular, 0.0, 1.0);
    			}

   		ILlums += Idiffuse + Ispecular;
		}
   }
    
//-L66- Transformacio de Visualitzacio amb MODELVIEW i GLPROJECTION
//    gl_Position=gl_ModelViewProjectionMatrix * gl_Vertex;
    gl_Position = ftransform();

//-L70- Calcul intensitat final del vertex
    gl_FrontColor.rgb = Iemissive + Iambient + ILlums;
    gl_FrontColor.a = 0.0;
    gl_BackColor = vec4(0.0,0.0,0.0,0.0);
}
