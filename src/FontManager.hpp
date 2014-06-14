#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include <SFML/Graphics.hpp>
#include <unordered_map>

class FontManager{
    static FontManager*_instance;
    FontManager();
    
    std::unordered_map<std::string,sf::Font*> _fonts;

public:
    static FontManager*getInstance();

    sf::Font*get(const char*name);
};

#endif
