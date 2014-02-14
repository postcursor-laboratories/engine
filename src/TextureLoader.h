#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include <SFML/Graphics.hpp>
#include <map>

class TextureLoader{
    static TextureLoader*_instance;
    std::map<std::string,sf::Texture*> _textures;

    TextureLoader();
    ~TextureLoader();

public:
    static TextureLoader*getInstance();

    void loadAll();    
    sf::Texture*get(std::string name);
};

#endif
