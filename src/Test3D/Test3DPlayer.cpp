#include "Test3DPlayer.hpp"
#include <SFML/OpenGL.hpp>

#include "../Utilities.hpp"
#include "GLM.hpp"

Test3DPlayer::Test3DPlayer(double x, double y, double z,
			   double xrot, double yrot, double zrot)
{
    _translation = Vec3(x,y,z);
    _rotation = new Mat4();

    *_rotation = glm::rotate(*_rotation, M_PI/180*xrot, Vec3(1,0,0));
    *_rotation = glm::rotate(*_rotation, M_PI/180*yrot, Vec3(0,1,0));
    *_rotation = glm::rotate(*_rotation, M_PI/180*zrot, Vec3(0,0,1));
}

Test3DPlayer::~Test3DPlayer(){}

void Test3DPlayer::performGLTransformations(){
    // glRotatef(_xrot, 1,0,0);
    // glRotatef(_yrot, 0,1,0);
    // glRotatef(_zrot, 0,0,1);
    
    double rot[] = {
	(*_rotation)[0][0],
	(*_rotation)[0][1],
	(*_rotation)[0][2],
	(*_rotation)[0][3],
	(*_rotation)[1][0],
	(*_rotation)[1][1],
	(*_rotation)[1][2],
	(*_rotation)[1][3],
	(*_rotation)[2][0],
	(*_rotation)[2][1],
	(*_rotation)[2][2],
	(*_rotation)[2][3],
	(*_rotation)[3][0],
	(*_rotation)[3][1],
	(*_rotation)[3][2],
	(*_rotation)[3][3]
    };
    
    glMultMatrixd(rot);

    glTranslated(_translation[0],
		 _translation[1],
		 _translation[2]);
}

void Test3DPlayer::move(double dx, double dy, double dz,
			double dxrot, double dyrot, double dzrot)
{
    _translation += Vec3(dx,dy,dz);

    dxrot = dxrot*M_PI/180;
    dyrot = dyrot*M_PI/180;
    dzrot = dzrot*M_PI/180;
    
    *_rotation = glm::rotate(*_rotation, dxrot, Vec3(1,0,0));
    *_rotation = glm::rotate(*_rotation, dyrot, Vec3(0,1,0));
    *_rotation = glm::rotate(*_rotation, dzrot, Vec3(0,0,1));
}

void Test3DPlayer::moveRel(double dright, double dforward, double dup,
			   double dpitch, double droll, double dyaw)
{
    //_translation += Vec4(dforward,-dright,dup,0)**_rotation;
    
    Vec3 localX = Vec3(Vec4(1,0,0,0)**_rotation);
    Vec3 localY = Vec3(Vec4(0,1,0,0)**_rotation);
    Vec3 localZ = Vec3(Vec4(0,0,1,0)**_rotation);

    _translation -= dright   * localX;
    _translation += dforward * localZ;
    _translation -= dup	     * localY;

    *_rotation = glm::rotate(*_rotation, M_PI/180*dpitch, localX);
    *_rotation = glm::rotate(*_rotation, M_PI/180*droll,  localZ);
    *_rotation = glm::rotate(*_rotation, M_PI/180*dyaw,   localY);
}

void Test3DPlayer::dumpState(){
    printf("Translation vector : <%f,%f,%f>\n",
	   _translation[0],
	   _translation[1],
	   _translation[2]);
    printf("Rotation matrix :\n");

    for(int i=0; i<4; i++)
	printf("%f\t%f\t%f\t%f\n",
	       (*_rotation)[i][0],
	       (*_rotation)[i][1],
	       (*_rotation)[i][2],
	       (*_rotation)[i][3]);
}
