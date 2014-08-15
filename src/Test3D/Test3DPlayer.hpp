#ifndef TEST3DPLAYER_H
#define TEST3DPLAYER_H

#include "../Player.hpp"
#include "../Utilities.hpp"

class Test3DPlayer : public Player{
    Vec3 _translation;
    Mat4*_rotation;
    
public:
    ~Test3DPlayer();
    Test3DPlayer(double x, double y, double z,
		 double xrot, double yrot, double zrot);
 
    void performGLTransformations();
    
    void move(double dx, double dy, double dz,
	      double dxrot, double dyrot, double dzrot);
    
    void moveRel(double dright, double dforward, double dup,
		 double dpitch, double droll, double dyaw);

    void dumpState();
};

#endif
