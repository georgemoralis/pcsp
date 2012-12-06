uniform bool EnableLight; 

vec4 getFrontColor() 
{
	if (!EnableLight) 
		return gl_Color;
}

vec4 getEyeCoordinatePosition() 
{
	return gl_ModelViewMatrix * gl_Vertex;
}

void main(void)
{
	gl_FrontColor = getFrontColor();
	gl_TexCoord[0]	= gl_TextureMatrix[0] * gl_MultiTexCoord0;
	gl_Position		= ftransform();
}