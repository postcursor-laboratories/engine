#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include <SFML/Graphics.hpp>
#include <vector>

class TextureLoader{
    static TextureLoader*_instance;

    std::vector<sf::Texture*> _textures;

    TextureLoader();
    ~TextureLoader();

public:
    static TextureLoader*getInstance();

    void loadAll();
    sf::Texture*getByName(std::string name);
    sf::Texture*get(size_t i);
};

#endif
