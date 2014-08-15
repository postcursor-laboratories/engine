#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>

#include "GL.hpp"

class Utilities{
public:
    static GLuint loadShader(std::string fname, int type);
    static bool stringEndsWith(std::string s, std::string suffix);
};

#endif
