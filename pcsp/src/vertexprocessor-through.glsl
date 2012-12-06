#version 120
#extension GL_EXT_gpu_shader4 : enable

attribute vec3 Pv;
attribute vec2 Tv;
attribute vec4 Cv;

uniform int vflags;

const mat4 M = mat4
(
     2.0/480.0,  0.0      ,  0.0        ,  0.0,
     0.0      , -2.0/272.0,  0.0        ,  0.0,
     0.0      ,  0.0      ,  2.0/65535.0,  0.0,
    -1.0      ,  1.0      , -1.0        ,  1.0
);

/* idealistically :

480   =  2 * Sx
272   = -2 * Sy
65535 = -2 * Sz

const mat4 M = mat4
(
     1.0/Sx,  0.0   ,  0.0   ,  0.0,
     0.0   ,  1.0/Sy,  0.0   ,  0.0,
     0.0   ,  0.0   , -1.0/Sz,  0.0,
    -Tx    , -Ty    , -Tz    ,  1.0
);
*/

varying vec4 Cp;
varying vec4 Cs;

void main()
{
    gl_Position = gl_ProjectionMatrix * vec4(Pv, 1.0);
    //gl_Position = M * vec4(Pv, 1.0);
    
    if (bool(vflags & 4))
    {
        gl_TexCoord[0] = vec4(Tv, 0.0, 1.0);
    }

    Cp = Cv;
    Cs = vec4(0.0);
}
