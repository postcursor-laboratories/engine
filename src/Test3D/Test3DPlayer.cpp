#include "Test3DPlayer.hpp"
#include <SFML/OpenGL.hpp>

Test3DPlayer::Test3DPlayer(double x, double y, double z, double xrot, double yrot, double zrot):
    _x(x), _y(y), _z(z), _xrot(xrot), _yrot(yrot), _zrot(zrot)
{}

Test3DPlayer::~Test3DPlayer(){}

void Test3DPlayer::performGLTransformations(){
    glRotatef(_xrot, 1,0,0);
    glRotatef(_yrot, 0,1,0);
    glRotatef(_zrot, 0,0,1);
    glTranslatef(_x, _y, _z);
}

void Test3DPlayer::move(double dx, double dy, double dz, double dxrot, double dyrot, double dzrot){
    _x+=dx;
    _y+=dy;
    _z+=dz;
    _xrot+=dxrot;
    _yrot+=dyrot;
    _zrot+=dzrot;
}
