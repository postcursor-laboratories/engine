#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include "TextureLoader.h"

TextureLoader*TextureLoader::_instance;
TextureLoader::TextureLoader(){}

TextureLoader*TextureLoader::getInstance(){
    if(_instance == NULL)
	_instance = new TextureLoader();
    return _instance;
}

// Loads all files in res as images.
void TextureLoader::load(){
    DIR*dir;
    struct dirent*ent;
    _numTextures = 0;

    // count the number of images
    if((dir = opendir("res")) != NULL){
	while((ent = readdir(dir)) != NULL){
	    if(!std::string(".") .compare(ent->d_name)) continue;
	    if(!std::string("..").compare(ent->d_name)) continue;
	    _numTextures++;
	}
	closedir(dir);
    }else return;

    printf("Loading %lu texture(s)....\n", _numTextures);
    
    _textures = new sf::Texture*[_numTextures];

    size_t i=0;
    if((dir = opendir("res")) != NULL){
	while((ent = readdir(dir)) != NULL){
	    if(!std::string(".") .compare(ent->d_name)) continue;
	    if(!std::string("..").compare(ent->d_name)) continue;

	    std::string filename=std::string("res/")+std::string(ent->d_name);

	    printf("Filename %s\n", filename.c_str());
	    sf::Texture*texture = new sf::Texture();
	    
	    texture->loadFromFile(filename);
	    printf("Created texture for %s", filename.c_str());

	    _textures[i++] = texture;
	}
	closedir(dir);
    }else return;
}

sf::Texture TextureLoader::getByName(std::string name){
    return *_textures[0];
}
