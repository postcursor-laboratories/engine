#ifndef MAIN_H
#define MAIN_H

#include <SFML/System.hpp>

enum ViewMode{ TEST, TEST3D, SPLASH }; // add views here as needed

class Main{
    static Main*_instance;
    ViewMode _viewMode;
    sf::Clock _clock;

    void displayDebuggingInformation(sf::RenderTarget*rt);
    bool _displayDebuggingInformation;

    Main();
    
public:
    static const size_t kWindowWidth;
    static const size_t kWindowHeight;
    static const std::string kName;

    static Main*getInstance();
    
    void main();
    void setView(ViewMode v);
};

#endif
