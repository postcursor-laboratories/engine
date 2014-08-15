#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sstream>
#include <fstream>

#include "Utilities.hpp"

#define SHADER_INFO_LOG_LEN 128	// for error reporting when loading shaders

GLuint Utilities::loadShader(std::string fname, int type){
    // -------------------------------------------- load source
    std::ifstream shaderFile("res/shaders/"+fname);
    std::ostringstream buffer;
    buffer << shaderFile.rdbuf();
    std::string bufferStr = buffer.str();
    const GLchar *src = bufferStr.c_str();

    // -------------------------------------------- create shader
    GLuint shaderID = glCreateShader(type);

    GLint l[] = { (GLint)strlen(src) };
    glShaderSource(shaderID, 1, &src, l);
    glCompileShader(shaderID);

    GLint compileStatus = 0;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileStatus);
    if (!compileStatus) {
	GLint len;
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &len);

	GLsizei infoLen = 0;
	GLchar  infoLog[SHADER_INFO_LOG_LEN];
	glGetShaderInfoLog(shaderID, sizeof(infoLog), &infoLen, infoLog);
	printf("SHADER LOAD ERROR: %s: %.*s\n", fname.c_str(), infoLen, infoLog);

	glDeleteShader(shaderID);
	return -1;
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    return shaderID;
}

bool Utilities::stringEndsWith(std::string s, std::string suffix){
    if(suffix.length() > s.length())
	return false;
    return 0==s.compare(s.length()-suffix.length(),suffix.length(),suffix);
}
