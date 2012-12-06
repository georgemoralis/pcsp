
const vec4 unsigned_scale = vec4(0.0, 1.0/128.0, 1.0/128.0, 1.0); 

uniform int vflags;

in vec3 Pv;
in vec4 Cv;
#if GE_VTYPE_TT
in vec2 Tv;
#endif

#if GE_VTYPE_TM

out vec4 Cp;
out vec4 Cs;
centroid out vec2 Tp;

uniform mat4 PM;

void main()
{
    gl_Position = PM * vec4(Pv, 1.0);
    
#if GE_VTYPE_TT
    Tp = Tv;
#else
    Tp = vec2(0.0);
#endif    

    Cp = Cv;
    Cs = vec4(0.0);
}

#else

#if GE_VTYPE_NT
in vec3 Nv;
#endif
#if GE_VTYPE_WT
in vec4 Wv_0_3;
#if GE_VTYPE_WC > 3
in vec4 Wv_4_7;
#endif
#endif

out vec4 Cp;
out vec4 Cs;
centroid out vec3 Tp;

uniform mat4 WM;
uniform mat4 VM;
uniform mat4 PM;

/// BONES
uniform mat4 BM[8];

/// LIGHTING
uniform ivec4  LTYPE[2];
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
uniform int    Le;
uniform int    Lmads;
uniform float  MK;
uniform float  NREV;

#if GE_VTYPE_NT
#if 1
void ComputeLight(in int i, in vec3 V, in vec3 En, in vec3 Nn, inout vec3 A, inout vec3 D, inout vec3 S)
{
    vec3  L     = vec3(VM * LV[i]) - V * vec3(LV[i].w); //vec3(VM * vec4(LV[i].xyz, 1.0)) - V * vec3(LV[i].w);
    float d     = length(L);
    L           = normalize(L);
    float NdotL = max(dot(Nn, L), 0.0);
    vec3 Dk;
    if (LTYPE[1][i] == 2)
    {
        Dk = vec3(pow(NdotL, MK));
    }
    else
    {
        Dk = vec3(NdotL);
    }
    if (LTYPE[0][i] == 0)
    {
        A += LAC[i].rgb;
        D += LDC[i].rgb * Dk;
    }
    else
    {
        if (LTYPE[0][i] == 2)
        {
            float spot = dot(normalize(LD[i].xyz), -L);
            if (spot <= LKO[i])
            {
                vec3 att = vec3(clamp(1.0 / (dot(LKA[i].xyz, vec3(1.0, d, d*d))), 0.0, 1.0) * pow(spot, LKS[i]));
                A += att * LAC[i].rgb;
                D += att * LDC[i].rgb * Dk;
                if (LTYPE[1][i] != 0)
                {
                    S += att * LSC[i].rgb * vec3(pow(max(dot(Nn, normalize(En + L)), 0.0), MK));
                }
            }
        }
        else
        {
            vec3 att = vec3(clamp(1.0 / (dot(LKA[i].xyz, vec3(1.0, d, d*d))), 0.0, 1.0));
            A += att * LAC[i].rgb;
            D += att * LDC[i].rgb * Dk;
            if (LTYPE[1][i] != 0)
            {
                S += att * LSC[i].rgb * vec3(pow(max(dot(Nn, normalize(En + L)), 0.0), MK));
            }
        }      
    }
}
#else
void ComputeLight(in int i, in vec3 V, in vec3 En, in vec3 Nn, inout vec3 A, inout vec3 D, inout vec3 S)
{
    vec3  L     = vec3(VM * vec4(LV[i].xyz, 1.0)) - V * vec3(LV[i].w); //vec3(VM * LV[i]) - V * LV[i].w;
    float d     = length(L);
    L           = normalize(L);
    vec3  H     = normalize(En + L);
    float NdotL = max(dot(Nn, L), 0.0);
    float NdotH = max(dot(Nn, H), 0.0);
    float Dk    = (LTYPE[1][i] == 2) ? pow(NdotL, MK) : NdotL;
    float Sk    = (LTYPE[1][i] != 0) ? pow(NdotH, MK) : 0.0;
    float att   = (LTYPE[0][i] == 0) ? 1.0 : clamp(1.0 / (dot(LKA[i].xyz, vec3(1.0, d, d*d))), 0.0, 1.0);
    if (LTYPE[0][i] == 2)
    {
        float spot = dot(normalize(LD[i].xyz), -L);
        att       *= (spot <= LKO[i]) ? 0.0 : pow(spot, LKS[i]);
    }
    A += att * LAC[i].rgb;
    D += att * LDC[i].rgb * Dk;
    S += att * LSC[i].rgb * Sk;  
}
#endif

void ApplyLighting(inout vec4 Cp, inout vec4 Cs, in vec3 V, in vec3 En, in vec3 Nn)
{
    vec4 Am = bool(Lmads & 1) ? Cp.rgba : MC[0].rgba;
    vec3 Dm = bool(Lmads & 2) ? Cp.rgb  : MC[1].rgb;
    vec3 Sm = bool(Lmads & 4) ? Cp.rgb  : MC[2].rgb;
    vec3 Em =                             MC[3].rgb;

    vec4 Al = AC;
    vec3 Dl = vec3(0.0);
    vec3 Sl = vec3(0.0);

    if (bool(Le & 1)) ComputeLight(0, V, En, Nn, Al.rgb, Dl.rgb, Sl.rgb);
    if (bool(Le & 2)) ComputeLight(1, V, En, Nn, Al.rgb, Dl.rgb, Sl.rgb);
    if (bool(Le & 4)) ComputeLight(2, V, En, Nn, Al.rgb, Dl.rgb, Sl.rgb);
    if (bool(Le & 8)) ComputeLight(3, V, En, Nn, Al.rgb, Dl.rgb, Sl.rgb);

    if (bool(Lmads & 8))
    {
        Cp.rgb = Em.rgb + Al.rgb * Am.rgb + Dl.rgb * Dm.rgb;
        Cs.rgb = Sl.rgb * Sm.rgb;
    }
    else
    {
        Cp.rgb = Em.rgb + Al.rgb * Am.rgb + Dl.rgb * Dm.rgb + Sl.rgb * Sm.rgb;
    }
    Cp.a = Al.a * Am.a;
}
#endif

/// TEXTURE
uniform ivec2 Tmap;
uniform ivec2 Tshade;
uniform vec2  Tscale;
uniform vec2  Ttrans;
uniform mat4  Tproj;

vec3 GetTexture_projection_mapping()
{
    vec3 T;
    if      (Tmap[1] == 0) // Model Coordinate Projection (XYZ)
    {
        T = Pv.xyz;
    }
#if GE_VTYPE_TT
    else if (Tmap[1] == 1) // Texture Coordinate Projection (UV0)
    {
        T = vec3(Tv.st, 0.0);
    }
#endif
#if GE_VTYPE_NT
    else if (Tmap[1] == 2) // Normalized Normal Coordinate projection (N/|N|)
    {
        T = normalize(Nv.xyz);
    }
    else if (Tmap[1] == 3) // Non-normalized Normal Coordinate projection (N)
    {
        T = Nv.xyz;
    }
#endif
    else
    {
        T = vec3(0.0);
    }
    return T;
}

vec2 GetTexture_shade_mapping(in vec3 V, in vec3 En, in vec3 Nn)
{
    vec3  R  = normalize(reflect(V, Nn));
    float Pu = dot(R, vec3(mat3(VM) * LV[Tshade.x].xyz));
    float Pv = dot(R, vec3(mat3(VM) * LV[Tshade.y].xyz));
    return vec2(1.0 + Pu, 1.0 + Pv);
}

void main()
{
#if GE_VTYPE_WT
    mat4  M;
    vec4  V  = vec4(0.0, 0.0, 0.0, 1.0);
#if GE_VTYPE_NT
    vec3  N  = vec3(0.0, 0.0, 0.0);
#endif
    {     
        vec4  Vw = vec4(Pv.xyz, 1.0);
#if GE_VTYPE_NT
        vec3  Nw = Nv * vec3(NREV);
#endif

        M = Wv_0_3.x * BM[0];
        V.xyz += vec3(M * Vw);
#if GE_VTYPE_NT
        N.xyz += mat3(M) * Nw;
#endif

#if GE_VTYPE_WC > 0
        M = Wv_0_3.y * BM[1];
        V.xyz += vec3(M * Vw);
#if GE_VTYPE_NT
        N.xyz += mat3(M) * Nw;
#endif
#endif

#if GE_VTYPE_WC > 1
        M = Wv_0_3.z * BM[2];
        V.xyz += vec3(M * Vw);
#if GE_VTYPE_NT
        N.xyz += mat3(M) * Nw;
#endif
#endif

#if GE_VTYPE_WC > 2
        M = Wv_0_3.w * BM[3];
        V.xyz += vec3(M * Vw);
#if GE_VTYPE_NT
        N.xyz += mat3(M) * Nw;
#endif
#endif

#if GE_VTYPE_WC > 3
        M = Wv_4_7.x * BM[4];
        V.xyz += vec3(M * Vw);
#if GE_VTYPE_NT
        N.xyz += mat3(M) * Nw;
#endif
#endif

#if GE_VTYPE_WC > 4
        M = Wv_4_7.y * BM[5];
        V.xyz += vec3(M * Vw);
#if GE_VTYPE_NT
        N.xyz += mat3(M) * Nw;
#endif
#endif

#if GE_VTYPE_WC > 5
        M = Wv_4_7.z * BM[6];
        V.xyz += vec3(M * Vw);
#if GE_VTYPE_NT
        N.xyz += mat3(M) * Nw;
#endif
#endif

#if GE_VTYPE_WC > 6
        M = Wv_4_7.w * BM[7];
        V.xyz += vec3(M * Vw);
#if GE_VTYPE_NT
        N.xyz += mat3(M) * Nw;
#endif
#endif
    }
    M = VM * WM;
#else    
#if GE_VTYPE_NT
    vec3 N = Nv * vec3(NREV);
#endif    
    vec4 V = vec4(Pv.xyz, 1.0);
    mat4 M = VM * WM;
#endif       
           
#if GE_VTYPE_NT
    N  = mat3(M) * N;
#endif    
    V  = mat4(M) * V;
    
    gl_Position = PM * V;
    
#if GE_VTYPE_NT
    vec3 En = -normalize(V.xyz);
    vec3 Nn = normalize(N);
#endif    
    
    if (bool(vflags & 2)) 
    {    
        vec4 Ca = Cv;
        vec4 Cb = vec4(0.0);
#if GE_VTYPE_NT
        ApplyLighting(Ca, Cb, V.xyz, En, Nn);
#endif    
        Cp = Ca;
        Cs = Cb;
    }
    else
    {
        Cp = Cv;
        Cs = vec4(0.0);
    }

    if (bool(vflags & 4))
    {    
        //Tp  = vec4(Tv * unsigned_scale[vtype.y], 1.0, 1.0);
         
        if      (Tmap[0] == 1)
        {
            Tp = vec3(Tproj * vec4(GetTexture_projection_mapping(), 1.0));
        }
#if GE_VTYPE_TT
        else if (Tmap[0] == 0)
        {
            Tp = vec3(Tscale * Tv.st + Ttrans, 1.0);
        }
#endif
#if GE_VTYPE_NT
        else if (Tmap[0] == 2)
        {
            Tp = vec3(GetTexture_shade_mapping(V.xyz, En, Nn), 2.0);
        }
#endif
        else
#if GE_VTYPE_TT
        {
            Tp  = vec3(Tv, 1.0);
        }
#else
        {
            Tp = vec3(0.0, 0.0, 1.0);
        }
#endif
    }
}
#endif