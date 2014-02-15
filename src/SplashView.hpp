#ifndef SPLASHVIEW_H
#define SPLASHVIEW_H

#include "View.hpp"

class SplashView : public View{
    sf::Clock _clock;
    size_t _milliseconds;
    
    sf::Text _slogan;
    sf::Font _slogFont;
    
public:
    SplashView();
    
    void draw(sf::RenderTarget*rt);
    void unpause();

    void pause();
};

#endif
