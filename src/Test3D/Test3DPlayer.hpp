#ifndef TEST3DPLAYER_H
#define TEST3DPLAYER_H

#include "../Player.hpp"

class Test3DPlayer : public Player{
    double _x, _y, _z;		// translation
    double _phi, _theta; 	// rotation, in degrees.
    // phi is measured from the +Z axis ("up"), and theta from +X CCW.
    
public:
    ~Test3DPlayer();
    Test3DPlayer(double x, double y, double z, double phi, double theta);
 
    void performGLTransformations();
    void move(double dx, double dy, double dz, double dphi, double dtheta);
};

#endif
