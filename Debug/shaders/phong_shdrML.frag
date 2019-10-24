//******** PRACTICA VISUALITZACIÓ GRÀFICA INTERACTIVA (EE-UAB)
//******** Entorn basic amb interfície MFC i Status Bar
//******** Enric Marti (Setembre 2018)
// phong_shdrML.frag: Vertex Program en GLSL per implementar il.luminacio de Phong

uniform bool texture;
uniform sampler2D texture0;
uniform bool sw_intensity[4];
uniform bool sw_lights[gl_MaxLights];
varying vec3 vertexPV;
//varying vec3 lightVec[gl_MaxLights];
varying vec3 normVec;

void main ()
{
vec3 lightVec[gl_MaxLights];
vec3 R[gl_MaxLights];

//-L17- Calcul variables previes (Reflexio Especular)
    vec3 V = normalize(-vertexPV);
    for (int i=0;i<gl_MaxLights;i++) {
	lightVec[i] = vec3(gl_LightSource[i].position.xyz - vertexPV);
    	R[i] = normalize (-reflect(lightVec[i],normVec));
	}
//-L22- Multiples llums
    vec3 ILlums = vec3 (0.0,0.0,0.0);
    vec3 Idiffuse = vec3 (0.0,0.0,0.0);
    vec3 Ispecular = vec3 (0.0,0.0,0.0);
    float diffuseLight = 0.0;

//-L28- Compute emissive term
    vec3 Iemissive = vec3 (0.0,0.0,0.0);
    if (sw_intensity[0])  Iemissive = gl_FrontMaterial.emission.rgb;
    
//-L32- Compute ambient term
    vec3 Iambient = vec3 (0.0,0.0,0.0);
    if (sw_intensity[1]) {  
    	Iambient = gl_FrontMaterial.ambient.rgb * gl_LightModel.ambient.rgb;
    	Iambient = clamp(Iambient, 0.0, 1.0);
    }

//-L39- Multiples llums
    for (int i=0;i<gl_MaxLights;i++) {
	if (sw_lights[i]) { 
		//-L42- Compute the diffuse term
    		Idiffuse = vec3 (0.0,0.0,0.0);
     		if (sw_intensity[2]) {
    			diffuseLight = max(dot(normVec, lightVec[i]), 0.0);
    			Idiffuse = gl_FrontMaterial.diffuse.rgb * gl_LightSource[i].diffuse.rgb * diffuseLight;
    			Idiffuse = clamp(Idiffuse, 0.0, 1.0);
    		}

		//-50- Compute the specular term
    		Ispecular = vec3 (0.0,0.0,0.0);
    		if (sw_intensity[3]) {
    			float specularLight = pow(max(dot(R[i], V), 0.0), gl_FrontMaterial.shininess);
			// if (diffuseLight <= 0.0) specularLight = 0.0;
    			Ispecular = gl_FrontMaterial.specular.rgb * gl_LightSource[i].specular.rgb * specularLight;
    			Ispecular = clamp(Ispecular, 0.0, 1.0);
			}
		ILlums += Idiffuse + Ispecular;
		}
   }

//-L62- Calcul intensitat final del pixel
   vec3 IColor = Iemissive + Iambient + ILlums;

   if (texture) {
//-L66- Intensitat amb textura
        vec4 colorT = texture2D(texture0,gl_TexCoord[0].st);
//        gl_FragColor.rgb = IColor * 0.3 + colorT.rgb * 1.0;
        gl_FragColor.rgb = IColor * colorT.rgb;
        gl_FragColor.a = 1.0;
    }
    else {
//-L73- Intensitat sense textura
      gl_FragColor.rgb = IColor;   
      gl_FragColor.a = 1.0;
      }
}
