#ifndef TEST3DVIEW_H
#define TEST3DVIEW_H

#include "View.hpp"

class Test3DView : public View{

public:
    Test3DView();

    void draw(sf::RenderTarget*rt);

    void unpause();
    void pause();
};

#endif
