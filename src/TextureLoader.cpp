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
	    
	    std::string filename=std::string("res/")+std::string(ent->d_name);

	    printf("  loading %s..", filename.c_str());
	    
	    sf::Texture*texture = new sf::Texture();
	    texture->loadFromFile(filename);

	    //_textures.insert({filename, texture});
	    _textures[name] = texture;
	    
	    i++;
	    printf("done\n");
	}
	closedir(dir);
    }else return;
    
    printf("Loaded %lu image%s\n", i, i==1?"":"s");
}

sf::Texture*TextureLoader::get(std::string name){
    return _textures.at(name);	// woot, operator overloading
}
