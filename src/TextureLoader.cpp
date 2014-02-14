#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include "TextureLoader.h"

TextureLoader*TextureLoader::_instance;
TextureLoader::TextureLoader(){}

TextureLoader::~TextureLoader(){
    delete &_textures;
}

TextureLoader*TextureLoader::getInstance(){
    if(_instance == NULL)
	_instance = new TextureLoader();
    return _instance;
}

// Loads all files in res as images.
void TextureLoader::load(){
    DIR*dir;
    struct dirent*ent;

    size_t i=0;
    if((dir = opendir("res")) != NULL){
	while((ent = readdir(dir)) != NULL){
	    if(!std::string(".") .compare(ent->d_name)) continue;
	    if(!std::string("..").compare(ent->d_name)) continue;

	    std::string name = std::string(ent->d_name);
	    if(name.length()<4 || name.substr(name.length()-4).compare(std::string(".png")))
		continue;

	    std::string filename=std::string("res/")+std::string(ent->d_name);

	    printf("Filename %s\n", filename.c_str());
	    //_textures[i] = new sf::Texture();
	    
	    sf::Texture*texture = new sf::Texture();
	    _textures.push_back(texture);
	    
	    texture->loadFromFile(filename);
	    printf("Created texture for %s\n", filename.c_str());

	    //_textures[i++] = texture;
	    i++;
	}
	closedir(dir);
    }else return;
    printf("Done loading!\n");
}

sf::Texture TextureLoader::getByName(std::string name){
    return *_textures[0];
}

sf::Texture*TextureLoader::get(size_t i){
    return _textures.at(i);
}
