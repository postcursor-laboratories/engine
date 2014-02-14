#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include <SFML/Graphics.hpp>

class TextureLoader{
    static TextureLoader*_instance;
    
    sf::Texture**_textures;
    size_t _numTextures;

    TextureLoader();

public:
    static TextureLoader*getInstance();

    void load();
    sf::Texture getByName(std::string name);
};

#endif
