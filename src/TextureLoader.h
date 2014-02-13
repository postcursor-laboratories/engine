#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include <SFML/Graphics.hpp>

class TextureLoader{
    static TextureLoader*_instance;
    sf::Texture*_textures;

    TextureLoader();

public:
    static TextureLoader*getInstance();
};

#endif
