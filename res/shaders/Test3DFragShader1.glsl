#version 120
uniform sampler2D texCMYK;
uniform sampler2D texRGB;
void main()
{
   gl_FragColor = -texture2D(texCMYK, gl_TexCoord[0].st) + texture2D(texRGB, gl_TexCoord[0].st);
}