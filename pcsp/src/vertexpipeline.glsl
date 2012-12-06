// 
// NShader - HLSL - GLSL - CG - Shader Syntax Highlighter AddIn for Visual Studio : http://nshader.codeplex.com/
//

//varying vec4  V;
//varying vec4  Cp;
//varying vec4  Cs;
//varying vec3  N;
//varying vec4  UV;
//varying float Pw;

/// VIEWPORT
uniform float Sz;
uniform float Tz;

/// VERTEX WEIGHTS
attribute vec4 Wabcd;
attribute vec4 Wefgh;

/// BONES
uniform mat3 BS[8];
uniform vec3 BT[8];
uniform int  Wn;

void ApplySkinning(inout vec3 Vv, inout vec3 Nv)
{
    vec3  V = vec3(0.0, 0.0, 0.0);
    vec3  N = V;
    float W;
    switch (Wn - 1)
    {
    case 7: W = Wefgh[3]; V += (BS[7] * Vv + BT[7]) * W; N += BS[7] * Nv * W;
    case 6: W = Wefgh[2]; V += (BS[6] * Vv + BT[6]) * W; N += BS[6] * Nv * W;
    case 5: W = Wefgh[1]; V += (BS[5] * Vv + BT[5]) * W; N += BS[5] * Nv * W; 
    case 4: W = Wefgh[0]; V += (BS[4] * Vv + BT[4]) * W; N += BS[4] * Nv * W; 
    case 3: W = Wabcd[3]; V += (BS[3] * Vv + BT[3]) * W; N += BS[3] * Nv * W;
    case 2: W = Wabcd[2]; V += (BS[2] * Vv + BT[2]) * W; N += BS[2] * Nv * W;
    case 1: W = Wabcd[1]; V += (BS[1] * Vv + BT[1]) * W; N += BS[1] * Nv * W; 
    case 0: W = Wabcd[0]; V += (BS[0] * Vv + BT[0]) * W; N += BS[0] * Nv * W; 
    }
    Vv = V;
    Nv = N;
}

/// LIGHTING
uniform bool  Lte; 
uniform bvec4 Le;
uniform bool  Lmode;
uniform bvec3 Lads;
uniform bvec3 Ltype;
uniform ivec4 Lcomp;


// Note : DirectionalLight can be detected if gl_LightSource[i].position.w == 0.0
void ApplyDirectionalLight(in int i, in vec3 N, inout vec4 A, inout vec4 D, inout vec4 S)
{
    vec3  L     = normalize(gl_LightSource[i].position.xyz);
    vec3  H     = gl_LightSource[i].halfVector.xyz;
    float NdotL = max(dot(N, L), 0.0);
    float NdotH = max(dot(N, H), 0.0);
    if (NdotH > 0.0)
    {
        float k  = gl_FrontMaterial.shininess;
        float Dk = (Lcomp[i] == 2) ? max(pow(NdotL, k), 0.0) : NdotL;
        float Sk = (Lcomp[i] != 0) ? max(pow(NdotH, k), 0.0) : 0.0;
        A  += gl_LightSource[i].ambient;
        D  += gl_LightSource[i].diffuse  * Dk;
        S  += gl_LightSource[i].specular * Sk;
    }
}

// Note : PointLight can be detected if gl_LightSource[i].position.w == 1.0 and gl_LightSource[i].spotCosCutoff == 180.0
void ApplyPointLight(in int i, in vec3 V, in vec3 N, inout vec4 A, inout vec4 D, inout vec4 S)
{
    vec3  L     = normalize(gl_LightSource[i].position.xyz - V);
    vec3  H     = gl_LightSource[i].halfVector.xyz;
    float NdotL = max(dot(N, L), 0.0);
    float NdotH = max(dot(N, H), 0.0);
    if (NdotH > 0.0)
    {
        float d   = length(L);
        float att = 1.0 / clamp(1.0 / (gl_LightSource[i].constantAttenuation + (gl_LightSource[i].linearAttenuation + gl_LightSource[i].quadraticAttenuation * d) * d), 0.0, 1.0);
        float k   = gl_FrontMaterial.shininess;
        float Dk  = (Lcomp[i] == 2) ? max(pow(NdotL, k), 0.0) : NdotL;
        float Sk  = (Lcomp[i] != 0) ? max(pow(NdotH, k), 0.0) : 0.0;
        A  += gl_LightSource[i].ambient  * att;
        D  += gl_LightSource[i].diffuse  * att * Dk;
        S  += gl_LightSource[i].specular * att * Sk;
    }

}

// Note : SpotLight can be detected if gl_LightSource[i].position.w == 1.0 and gl_LightSource[i].spotCosCutoff != 180.0
void ApplySpotlight(in int i, in vec3 V, in vec3 N, inout vec4 A, inout vec4 D, inout vec4 S)
{
    vec3  L     = normalize(gl_LightSource[i].position.xyz - V);
    vec3  H     = gl_LightSource[i].halfVector.xyz;
    float NdotL = max(dot(N, L), 0.0);
    float NdotH = max(dot(N, H), 0.0);
    if (NdotH > 0.0)
    {
        float spot  = dot(normalize(gl_LightSource[i].spotDirection), -L);
        if (spot > gl_LightSource[i].spotCosCutoff)
        {
            float d   = length(L);
            float k   = gl_FrontMaterial.shininess;
            float Dk  = (Lcomp[i] == 2) ? max(pow(NdotL, k), 0.0) : NdotL;
            float Sk  = (Lcomp[i] != 0) ? max(pow(NdotH, k), 0.0) : 0.0;
            spot = pow(spot, gl_LightSource[0].spotExponent) / clamp(1.0 / (gl_LightSource[i].constantAttenuation + (gl_LightSource[i].linearAttenuation + gl_LightSource[i].quadraticAttenuation * d) * d), 0.0, 1.0);
            A  += gl_LightSource[i].ambient  * spot;
            D  += gl_LightSource[i].diffuse  * spot * Dk;
            S  += gl_LightSource[i].specular * spot * Sk;
        }
    }
}

// Note : it would be interesting to try to merge the above three function into one and use gl_LightSource[i].position.w and gl_LightSource[i].spotCosCutoff
//        to detect the kind of light, so we could remove the need of Lt.
void ComputeLight(in int i, in vec3 N, in vec3 V, inout vec4 A, inout vec4 D, inout vec4 S)
{
#if 0
    switch (Ltype[i])
    {
    case 0: ApplyDirectionalLight(i, N, A, D, S); break; 
    case 1: ApplyPointLight(i, N, V, A, D, S);    break;
    case 2: ApplySpotlight(i, N, V, A, D, S);     break;
    }
#else
    float w     = gl_LightSource[i].position.w;
    vec3  L     = normalize(gl_LightSource[i].position.xyz - w * V);
    vec3  H     = gl_LightSource[i].halfVector.xyz;
    float NdotL = max(dot(N, L), 0.0);
    float NdotH = max(dot(N, H), 0.0);
    if (NdotH > 0.0)
    {
        float k   = gl_FrontMaterial.shininess;
        float Dk  = (Lcomp[i] == 2) ? max(pow(NdotL, k), 0.0) : NdotL;
        float Sk  = (Lcomp[i] != 0) ? max(pow(NdotH, k), 0.0) : 0.0;
        float att = 1.0;
        
        if (w == 1.0)
        {       
            float spot = gl_LightSource[i].spotCosCutoff == 180.0 ? 0.0 : dot(normalize(gl_LightSource[i].spotDirection), -L);
            if (spot > gl_LightSource[i].spotCosCutoff)
            {
                att = spot;
            }
            float d = length(L);
            att = clamp(att / (gl_LightSource[i].constantAttenuation + (gl_LightSource[i].linearAttenuation + gl_LightSource[i].quadraticAttenuation * d) * d), 0.0, 1.0);
        }        
        A  += gl_LightSource[i].ambient  * att;
        D  += gl_LightSource[i].diffuse  * att * Dk;
        S  += gl_LightSource[i].specular * att * Sk;
    }
#endif   
}

void ApplyLighting(inout vec4 Cp, inout vec4 Cs, in vec3 V, in vec3 N)
{
    vec4 Ac  = gl_LightModel.ambient;
    vec4 Ecm = gl_FrontMaterial.emission;
    vec4 Acm = Lads[0] ? Cp.rgba : vec4(gl_FrontMaterial.ambient.rgb,  Ac.w);
    vec4 Dcm = Lads[1] ? Cp.rgba : vec4(gl_FrontMaterial.diffuse.rgb,  Ac.w);
    vec4 Scm = Lads[2] ? Cp.rgba : vec4(gl_FrontMaterial.specular.rgb, Ac.w);

    vec4 LAc = vec4(0.0);
    vec4 LDc = vec4(0.0);
    vec4 LSc = vec4(0.0);
    
    if (Le[0]) ComputeLight(0, N, V, LAc, LDc, LSc);
    if (Le[1]) ComputeLight(1, N, V, LAc, LDc, LSc);
    if (Le[2]) ComputeLight(2, N, V, LAc, LDc, LSc);
    if (Le[3]) ComputeLight(3, N, V, LAc, LDc, LSc);
    
    if (Lmode)
    {
        Cp = clamp(Ecm + Ac * Acm + LDc * Dcm, 0.0, 1.0);
        Cs = clamp(LSc * Scm                 , 0.0, 1.0);
    }
    else
    {
        Cp = Ecm + Ac * Acm + LDc * Dcm + LSc *Scm;
    }
}
  
void main(void)
{
    vec4 V = gl_Vertex;
    vec3 N = gl_Normal;
    
    if (Wn > 0) ApplySkinning(V.xyz, N);

    vec4 Vl = gl_ModelViewMatrix * V;
    vec3 Nl = gl_NormalMatrix    * N;

    vec4 Cp = gl_Color;
    vec4 Cs = vec4(0.0, 0.0, 0.0, 0.0);
    vec4 UV = gl_TextureMatrix[0] * gl_MultiTexCoord0;
    
    // we need firt to change rasterizezr_shader so it sets the light uniforms correctly or it will compute as a mad
    //if (Lte) ApplyLighting(Cp, Cs, Vl.xyz, Nl);
    
    gl_TexCoord[0]         = UV;
    gl_FrontColor          = Cp;
    gl_FrontSecondaryColor = Cs;
    gl_Position            = gl_ModelViewProjectionMatrix * V;	
}