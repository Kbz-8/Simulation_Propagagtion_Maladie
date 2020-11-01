 #version 130

out vec4 fragPos;
out vec2 texCoords;
out vec4 Color;


void main(void)
{
  fragPos = gl_Vertex;
  texCoords = gl_MultiTexCoord0.xy;
  Color = gl_Color;

  gl_Position = ftransform();
}
