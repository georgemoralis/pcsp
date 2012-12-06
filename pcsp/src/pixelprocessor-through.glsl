#version 120
#extension GL_EXT_gpu_shader4 : enable

uniform int pflags;

/// TEXTURE MAPPING
uniform sampler2D Tdata;
uniform ivec3     Tfunc;
uniform vec3      Trgb;
uniform vec2      Tsize;

void ApplyTextureMapping(inout vec4 Cp, in vec4 Ct)
{
    if (Tfunc[1] == 0) Ct.a = 1.0;
    
    switch (Tfunc[0])
    {
    case 0: // MODULATE
        Cp *= Ct;
        break;
    case 1: // DECAL
        Cp.rgb = mix(Cp.rgb, Ct.rgb, Ct.a);
        break;
    case 2: // BLEND
        Cp.rgb = mix(Cp.rgb, Trgb, Ct.rgb);
        Cp.a   = Cp.a * Ct.a;
        break;
    case 3: // REPLACE
        Cp.rgb = Ct.rgb;
        if (Tfunc[1] != 0) Cp.a = Ct.a;
        break;
    case 4: // ADD
        Cp.rgb = Cp.rgb + Ct.rgb;
        Cp.a   = Cp.a   * Ct.a;
        break;
    default:
        break;
    }
    Cp = clamp(Cp, 0.0, 1.0);        
}

/// SCISSORING
void ApplyScissoring()
{
}

/// COLOR/ALPHA TEST
uniform ivec2 Cfnc;
uniform ivec4 Cref;
uniform ivec4 Cmsk;

bool DiscardAfterColorTest(in ivec4 C)
{
    bool discarded;
    switch (Cfnc[0])
    {
    case 0:     // NEVER
        discarded = true;
        break;
    case 1:     // ALWAYS
        discarded = false;
        break;
    case 2:     // EQUAL
        discarded = ((C.rgb & Cmsk.rgb) != (Cref.rgb & Cmsk.rgb));
        break;
    case 3:     // NOTEQUAL
        discarded = ((C.rgb & Cmsk.rgb) == (Cref.rgb & Cmsk.rgb));
        break;
    default:    // ALWAYS
        discarded = false;
        break;
    }
    return discarded;
}

bool DiscardAfterAlphaTest(in ivec4 C)
{
    bool discarded;
    switch (Cfnc[1])
    {
    case 0:     // NEVER
        discarded = true;
        break;
    case 1:    // ALWAYS
        discarded = false;
        break;
    case 2:     // EQUAL
        discarded = ((C.a & Cmsk.a) != (Cref.a & Cmsk.a));
        break;
    case 3:     // NOTEQUAL
        discarded = ((C.a & Cmsk.a) == (Cref.a & Cmsk.a));
        break;
    case 4:     // LESS
        discarded = ((C.a & Cmsk.a) >= (Cref.a & Cmsk.a));
        break;
    case 5:     // LEQUAL
        discarded = ((C.a & Cmsk.a) >  (Cref.a & Cmsk.a));
        break;
    case 6:     // GREATER
        discarded = ((C.a & Cmsk.a) <= (Cref.a & Cmsk.a));
        break;
    case 7:     // GEQUAL
        discarded = ((C.a & Cmsk.a) <  (Cref.a & Cmsk.a));
        break;
    default:    // ALWAYS
        discarded = false;
        break;
    }
    return discarded;
}

/// STENCIL TEST (done by glStencilFunc/Op indeed)
void ApplyStencilTest()
{
}

/// DEPTH TEST (done by glDepthFunc indeed)
void ApplyDepthTest()
{
}

/// ALPHA BLENDING
uniform ivec3 Ablend;
uniform ivec3  Afixa;
uniform ivec3  Afixb;

void ApplyAlphaBlending(inout vec4 Cs, in vec4 Cd)
{
	vec3 a = vec3(Afixa / 255.0);
    vec3 b = vec3(Afixb / 255.0);
	
	switch (Ablend[2])
	{
	case  0: b = Cs.rgb;               break;
	case  1: b = vec3(1.0) - Cs.rgb;   break;
	case  2: b = vec3(Cs.a);           break;
	case  3: b = vec3(1.0 - Cs.a);     break;
	case  4: b = vec3(Cd.a);           break;
	case  5: b = vec3(1.0 - Cd.a);     break;
	case  6: b = vec3(2.0*Cs.a);       break;
	case  7: b = vec3(1.0 - 2*Cs.a);   break;
	case  8: b = vec3(2.0*Cd.a);       break;
	case  9: b = vec3(1.0 - 2.0*Cd.a); break;
	default:                           break;
	}

	switch (Ablend[1])
	{
	case  0: a = Cd.rgb;               break;
	case  1: a = vec3(1.0) - Cd.rgb;   break;
	case  2: a = vec3(Cs.a);           break;
	case  3: a = vec3(1.0 - Cs.a);     break;
	case  4: a = vec3(Cd.a);           break;
	case  5: a = vec3(1.0 - Cd.a);     break;
	case  6: a = vec3(2.0*Cs.a);       break;
	case  7: a = vec3(1.0 - 2*Cs.a);   break;
	case  8: a = vec3(2.0*Cd.a);       break;
	case  9: a = vec3(1.0 - 2.0*Cd.a); break;
	default:                           break;
	}
	
	switch (Ablend[0])
	{
	case 0: Cs.rgb = (Cs.rgb * a + Cd.rgb * b); break;
	case 1: Cs.rgb = (Cs.rgb * a - Cd.rgb * b); break;
	case 2: Cs.rgb = (Cd.rgb * b - Cs.rgb * a); break;
	case 3: Cs.rgb = min(Cs.rgb, Cd.rgb);       break;
	case 4: Cs.rgb = max(Cs.rgb, Cd.rgb);       break;
	case 5: Cs.rgb = abs(Cs.rgb - Cd.rgb);      break;
	default:                                    break;
	}
	
	Cs = clamp(Cs, 0.0, 1.0);
}

/// DITHERING
void ApplyDithering()
{
}

/// LOGICAL OPERATIONS
void ApplyLogicalOperations()
{
}

varying vec4 Cp;
varying vec4 Cs;

void main(void)
{
    vec4 Ct = texture2D(Tdata, gl_TexCoord[0].st * Tsize).rgba;
    vec4 Cf = Cp;

    if (bool(pflags & 1)) ApplyTextureMapping(Cf, Ct);  

    // Colour Doubling and Addition
    Cf.xyz = clamp(float(Tfunc[2] + 1) * (Cf.rgb + Cs.rgb), 0.0, 1.0);    
    
	//if (pflags &    8) ApplyScissoring();

    ivec4 RGBA8888 = ivec4(Cf * 255.0);
    
    if (bool(pflags & 16))
    { 
	    if (DiscardAfterColorTest(RGBA8888)) discard;
	}
    if (bool(pflags & 32))
    { 
	    if (DiscardAfterAlphaTest(RGBA8888)) discard;
	}
	
	//if (pflags &  128) ApplyStencilTest(); // done by glStencilFunc/Op indeed
	//if (pflags &  256) ApplyDepthTest(); // done by glDepthFunc indeed

    // those operations requires reading access to destination frame buffer
	//if (pflags &  512) ApplyAlphaBlending(Cp, Cd);
	//if (pflags & 1024) ApplyDithering();
	//if (pflags & 2048) ApplyLogicalOperations();
	//if (pflags & 4096) ApplyMasking();
	
	gl_FragColor = Cf; 	
}

