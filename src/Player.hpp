#ifndef PLAYER_H
#define PLAYER_H

class Player{
public:
    ~Player(){}
    Player(){}


    // This function is responsible for moving the "camera" to prepare for each frame
    virtual void performGLTransformations(){};
};

#endif
