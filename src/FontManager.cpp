#include "FontManager.hpp"
#include "Utilities.hpp"

#include <stdio.h>

FontManager*FontManager::_instance = NULL;

FontManager::FontManager(){}

FontManager*FontManager::getInstance(){
    if(!_instance)
	_instance = new FontManager();
    return _instance;
}

sf::Font*FontManager::get(const char*name){
    std::string sname = std::string(name);

    // if it's already loaded, return that
    if(_fonts[sname])
	return _fonts[sname];

    // otherwise, load the font from file
    printf("FontManager: Loading font `%s' from disk\n", name);
    sf::Font*ret = new sf::Font();
    if(!ret->loadFromFile(name)){
	printf("FontManager: WARNING: Couldn't load font `%s'!\n", name);
	delete ret;
	return NULL;
    }

    _fonts[sname] = ret;
    return ret;
}
