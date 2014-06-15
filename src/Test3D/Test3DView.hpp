#ifndef TEST3DVIEW_H
#define TEST3DVIEW_H

#include "../View.hpp"
#include "Test3DPlayer.hpp"

class Test3DView : public View{
    Test3DPlayer*_player;
    
public:
    Test3DView();

    void draw(sf::RenderTarget*rt);

    void unpause();
    void pause();
};

#endif
