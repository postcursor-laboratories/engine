#ifndef VIEW_H
#define VIEW_H

#include <SFML/Graphics.hpp>

class View{
public:
    virtual ~View(){}
    
    virtual void draw(sf::RenderTarget*rt) = 0;
    virtual void update()  = 0;

    virtual void pause()   = 0;
    virtual void unpause() = 0;
};

#endif
