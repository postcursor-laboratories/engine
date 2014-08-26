#ifndef SPLASHVIEW_H
#define SPLASHVIEW_H

#include "View.hpp"

class SplashView : public View{
    sf::Clock _clock;
    size_t _milliseconds;
    
    sf::Text _slogan;
    
public:
    SplashView();

    void init();
    
    void draw(sf::RenderTarget*rt);
    void update();
    
    void unpause();
    void pause();
};

#endif
