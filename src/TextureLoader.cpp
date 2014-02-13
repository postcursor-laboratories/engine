#include <stdlib.h>
#include "TextureLoader.h"

TextureLoader*TextureLoader::_instance;
TextureLoader::TextureLoader(){}

TextureLoader*TextureLoader::getInstance(){
    if(_instance == NULL)
	_instance = new TextureLoader();
    return _instance;
}

