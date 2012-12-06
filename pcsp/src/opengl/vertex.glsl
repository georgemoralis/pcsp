#version %VERSION%
#extension GL_EXT_gpu_shader4 : enable
#if %VERSION% >= 130
#define attribute   in
#define varying     out
#else
#define texture     texture2D
#define textureProj texture2DProj
#endif


attribute vec3 Pv;
#if %vtype.ne%
attribute vec3 Nv;
#endif
#if %vtype.te%
attribute vec2 Tv;
#endif
#if %vtype.ce%
attribute vec4 Cv;
#endif
#if %vtype.we%
attribute vec4 Wv_0_3;
#if %vtype.wc% > 3
attribute vec4 Wv_4_7;
#endif
#endif

varying vec4 Cp;
varying vec4 Cs;

#if %vtype.tm% // THROUGH MODE
void main()
{
    gl_Position = gl_ProjectionMatrix * vec4(Pv, 1.0);
   
#if !%cm% && %vtype.te%
    gl_TexCoord[0] = vec4(Tv, 0.0, 1.0);
#endif

    Cp = Cv;
    Cs = vec4(0.0);
}
#else

uniform mat4 WM;
uniform mat4 VM;
uniform mat4 PM;

/// BONES
#if %vtype.we%
uniform mat4 BM[8];
#endif

/// TEXTURE
#if %vtype.te%
#if   %tmap.tmn% == 0 
uniform vec2  Tscale;
uniform vec2  Ttrans;
#elif %tmap.tmn% == 1
uniform mat4  Tproj;
#elif %tmap.tmn% == 2
uniform ivec2 Tshade;
#endif
#endif

/// LIGHTING
uniform mat4   LV;
uniform mat4   LD;
uniform mat4   LAC;
uniform mat4   LDC;
uniform mat4   LSC;
uniform mat4   MC;
uniform mat4   LKA;
uniform vec4   LKS;
uniform vec4   LKO;
uniform vec4   AC;
uniform float  MK;
uniform float  NREV;
 
#if %le% & 1
void ComputeLight0(in vec3 V, in vec3 En, in vec3 Nn, inout vec3 A, inout vec3 D, inout vec3 S)
{
    vec3  L     = vec3(VM * LV[0]) - V * LV[0].w;
    float d     = length(L);
    L           = normalize(L);

#if   %ltype0.type% == 0
    float att   = 1.0;
#elif %ltype0.type% == 2
    float att   = dot(normalize(LD[0].xyz), -L) /* spot */; 
    att         = (att /* spot */ <= LKO[0]) ? 0.0 : pow(att /* spot */, LKS[0]);
#else
    float att   = clamp(1.0 / (dot(LKA[0].xyz, vec3(1.0, d, d*d))), 0.0, 1.0);
#endif

    A += att * LAC[0].rgb;

#if %ltype0.kind% == 2
    D += att * LDC[0].rgb * pow(max(dot(Nn, L), 0.0) /*NdotL*/, MK);
#else
    D += att * LDC[0].rgb * max(dot(Nn, L), 0.0) /*NdotL*/;
#endif
    
#if %ltype0.kind% != 0
    S += att * LSC[0].rgb * pow(max(dot(Nn, normalize(En + L) /*H*/), 0.0) /*NdotH*/, MK);
#endif
}
#endif

#if %le% & 2
void ComputeLight1(in vec3 V, in vec3 En, in vec3 Nn, inout vec3 A, inout vec3 D, inout vec3 S)
{
    vec3  L     = vec3(VM * LV[1]) - V * LV[1].w;
    float d     = length(L);
    L           = normalize(L);

#if   %ltype1.type% == 0
    float att   = 1.0;
#elif %ltype1.type% == 2
    float att   = dot(normalize(LD[1].xyz), -L) /* spot */; 
    att         = (att /* spot */ <= LKO[1]) ? 0.0 : pow(att /* spot */, LKS[1]);
#else
    float att   = clamp(1.0 / (dot(LKA[1].xyz, vec3(1.0, d, d*d))), 0.0, 1.0);
#endif

    A += att * LAC[1].rgb;

#if %ltype1.kind% == 2
    D += att * LDC[1].rgb * pow(max(dot(Nn, L), 0.0) /*NdotL*/, MK);
#else
    D += att * LDC[1].rgb * max(dot(Nn, L), 0.0) /*NdotL*/;
#endif
    
#if %ltype1.kind% != 0
    S += att * LSC[1].rgb * pow(max(dot(Nn, normalize(En + L) /*H*/), 0.0) /*NdotH*/, MK);
#endif
}
#endif

#if %le% & 4
void ComputeLight2(in vec3 V, in vec3 En, in vec3 Nn, inout vec3 A, inout vec3 D, inout vec3 S)
{
    vec3  L     = vec3(VM * LV[2]) - V * LV[2].w;
    float d     = length(L);
    L           = normalize(L);

#if   %ltype2.type% == 0
    float att   = 1.0;
#elif %ltype2.type% == 2
    float att   = dot(normalize(LD[2].xyz), -L) /* spot */; 
    att         = (att /* spot */ <= LKO[2]) ? 0.0 : pow(att /* spot */, LKS[2]);
#else
    float att   = clamp(1.0 / (dot(LKA[2].xyz, vec3(1.0, d, d*d))), 0.0, 1.0);
#endif

    A += att * LAC[2].rgb;

#if %ltype2.kind% == 2
    D += att * LDC[2].rgb * pow(max(dot(Nn, L), 0.0) /*NdotL*/, MK);
#else
    D += att * LDC[2].rgb * max(dot(Nn, L), 0.0) /*NdotL*/;
#endif
    
#if %ltype2.kind% != 0
    S += att * LSC[2].rgb * pow(max(dot(Nn, normalize(En + L) /*H*/), 0.0) /*NdotH*/, MK);
#endif
}
#endif

#if %le% & 8
void ComputeLight3(in vec3 V, in vec3 En, in vec3 Nn, inout vec3 A, inout vec3 D, inout vec3 S)
{
    vec3  L     = vec3(VM * LV[3]) - V * LV[3].w;
    float d     = length(L);
    L           = normalize(L);

#if   %ltype3.type% == 0
    float att   = 1.0;
#elif %ltype3.type% == 2
    float att   = dot(normalize(LD[3].xyz), -L) /* spot */; 
    att         = (att /* spot */ <= LKO[3]) ? 0.0 : pow(att /* spot */, LKS[3]);
#else
    float att   = clamp(1.0 / (dot(LKA[3].xyz, vec3(1.0, d, d*d))), 0.0, 1.0);
#endif

    A += att * LAC[3].rgb;

#if %ltype3.kind% == 2
    D += att * LDC[3].rgb * pow(max(dot(Nn, L), 0.0) /*NdotL*/, MK);
#else
    D += att * LDC[3].rgb * max(dot(Nn, L), 0.0) /*NdotL*/;
#endif
    
#if %ltype3.kind% != 0
    S += att * LSC[3].rgb * pow(max(dot(Nn, normalize(En + L) /*H*/), 0.0) /*NdotH*/, MK);
#endif
}
#endif

void main()
{
#if %vtype.ne%
    vec3 N = Nv * Nrev;
#endif
    vec4 V = vec4(Pv, 1.0);
    mat4 M;
#if %vtype.we% && %vtype.ne%
    {
		vec3 Ns = vec3(0.0);
		vec3 Vs = vec3(0.0);
		
#if %vtype.wc% > 0
		M = Wv_0_3.x * BM[0]; Vs += M * V; Ns += mat3(M) * N;
#if %vtype.wc% > 1
		M = Wv_0_3.y * BM[1]; Vs += M * V; Ns += mat3(M) * N;
#if %vtype.wc% > 2
		M = Wv_0_3.z * BM[2]; Vs += M * V; Ns += mat3(M) * N;
#if %vtype.wc% > 3
		M = Wv_0_3.w * BM[3]; Vs += M * V; Ns += mat3(M) * N;
#if %vtype.wc% > 4
		M = Wv_4_7.x * BM[4]; Vs += M * V; Ns += mat3(M) * N;
#if %vtype.wc% > 5
		M = Wv_4_7.y * BM[5]; Vs += M * V; Ns += mat3(M) * N;
#if %vtype.wc% > 6
		M = Wv_4_7.z * BM[6]; Vs += M * V; Ns += mat3(M) * N;
#if %vtype.wc% > 7
		M = Wv_4_7.w * BM[7]; Vs += M * V; Ns += mat3(M) * N;
#endif		
#endif		
#endif		
#endif		
#endif		
#endif		
#endif		
#endif		

		M = VM * WM;
		
		N = mat3(M) * Ns;
		V = mat4(M) * vec4(Vs.xyz, V.w);
    }
#else
	{
		M = VM * WM;

#if %vtype.ne%
		N = mat3(M) * N;
#endif
		V = mat4(M) * V;
	}
#endif
	gl_Position = PM * V;
	
#if %vtype.ne%
    vec3 Nn = normalize(N);
#endif
	
#if %le% && %vtype.ne%
    {    
#if %material% & 1
		vec4 Am = Cv.rgba;
#else
		vec4 Am = MC[0].rgba;
#endif		
#if %material% & 2
		vec3 Dm = Cv.rgb;
#else
		vec3 Dm = MC[1].rgb;
#endif		
#if %material% & 4
		vec3 Sm = Cv.rgb;
#else
		vec3 Sm = MC[2].rgb;
#endif		
		vec3 Em = MC[3].rgb;

		vec4 Al = AC;
		vec3 Dl = vec3(0.0);
		vec3 Sl = vec3(0.0);
		vec3 En = -normalize(V.xyz);

#if %le% & 1
		ComputeLight0(V, En, Nn, Al.rgb, Dl.rgb, Sl.rgb);
#endif
#if %le% & 2
		ComputeLight1(V, En, Nn, Al.rgb, Dl.rgb, Sl.rgb);
#endif
#if %le% & 4
		ComputeLight2(V, En, Nn, Al.rgb, Dl.rgb, Sl.rgb);
#endif
#if %le% & 8
		ComputeLight3(V, En, Nn, Al.rgb, Dl.rgb, Sl.rgb);
#endif

#if %material% & 8
		Cp.rgb = Em.rgb + Al.rgb * Am.rgb + Dl.rgb * Dm.rgb;
		Cs.rgb = Sl.rgb * Sm.rgb;
        Cs.a   = 0.0;
#else
		Cp.rgb = Em.rgb + Al.rgb * Am.rgb + Dl.rgb * Dm.rgb + Sl.rgb * Sm.rgb;
        Cs     = vec4(0.0);
#endif
		Cp.a = Al.a * Am.a;
    }
#else
    {
        Cp = Cv;
        Cs = vec4(0.0);
	}
#endif

#if %vtype.te%
#if   %tmap.tmn% == 0  // UV mapping
	gl_TexCoord[0] = vec4(Tscale * T.st + Ttrans, 1.0, 1.0);
#elif %tmap.tmn% == 1 // Projection mapping
#if   %tmap.tmi% == 0 // Model Coordinate Projection (XYZ)
	gl_TexCoord[0] = Tproj * vec4(Pv, 1.0);
#elif %tmap.tmi% == 1 // Texture Coordinate Projection (UV0)
	gl_TexCoord[0] = Tproj * vec4(Tv.st, 0.0, 1.0);
#elif %tmap.tmi% == 2 // Normalized Normal Coordinate projection (N/|N|)
	gl_TexCoord[0] = Tproj * vec4(normalize(Nv.xyz), 1.0);
#elif %tmap.tmi% == 3 // Non-normalized Normal Coordinate projection (N)
	gl_TexCoord[0] = Tproj * vec4(Nv.xyz, 1.0);
#endif
#elif %tmap.tmn% == 2 // Shade mapping
	{
		vec3  R  = normalize(reflect(V.xyz, Nn));
		float Pu = dot(R, vec3(VM * LV[Tshade.x]));
		float Pv = dot(R, vec3(VM * LV[Tshade.y]));
		gl_TexCoord[0] = vec4(1.0 + Pu, 1.0 + Pv, 2.0, 1.0);
	}
#endif
}
#endif