#include "Test3DPlayer.hpp"
#include <SFML/OpenGL.hpp>

Test3DPlayer::Test3DPlayer(double x, double y, double z, double phi, double theta):
    _x(x), _y(y), _z(z), _phi(phi), _theta(theta)
{}

Test3DPlayer::~Test3DPlayer(){}

void Test3DPlayer::performGLTransformations(){
    glRotatef(-_theta, 0,0,1);
    glRotatef(180+_phi,1,-1,0);
    glTranslatef(_x, _y, _z);
}
