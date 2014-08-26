#ifndef TEST3DVIEW_H
#define TEST3DVIEW_H

#include "../View.hpp"
#include "Test3DPlayer.hpp"

class Test3DView : public View{
    GLuint _shaderProgram;
    Test3DPlayer*_player;
    
public:
    Test3DView();

    void init();
    
    void update();
    void draw(sf::RenderTarget*rt);

    void unpause();
    void pause();
};

#endif
