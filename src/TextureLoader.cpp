#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include "TextureLoader.hpp"
#include "Utilities.hpp"

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
void TextureLoader::loadAll(){
    DIR*dir;
    struct dirent*ent;

    printf("Loading all images in res:\n");
    
    size_t i=0;
    if((dir = opendir("res")) != NULL){
	while((ent = readdir(dir)) != NULL){
	    if(!std::string(".") .compare(ent->d_name)) continue;
	    if(!std::string("..").compare(ent->d_name)) continue;

	    std::string name = std::string(ent->d_name);

	    if(!Utilities::stringEndsWith(name,".png") &&
	       !Utilities::stringEndsWith(name,".jpg"))
		continue;

	    sf::Texture*texture = new sf::Texture();
	    
	    std::string filename=std::string("res/")+std::string(ent->d_name);
	    if(!texture->loadFromFile(filename)){
		printf("Error: could not load file `%s'\n", name.c_str());
		continue;
	    }

	    _textures[name] = texture;
	    
	    printf("  loaded %s\n", filename.c_str());
	    i++;
	}
	closedir(dir);
    }else return;
    
    printf("Loaded %lu image%s\n", i, i==1?"":"s");
}

sf::Texture*TextureLoader::get(std::string name){
    if(_textures.find(name) != _textures.end())
	return _textures.at(name); // woot, operator overloading
    else
	return _textures.at("trollface.jpg"); // to notify the user of an error
}
