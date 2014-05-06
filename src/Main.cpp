#include <SFML/Graphics.hpp>
#include <stdio.h>

#include "Main.hpp"
#include "TextureLoader.hpp"
#include "Utilities.hpp"

#include "View.hpp"
#include "SplashView.hpp"

const size_t Main::kWindowWidth  = 800;
const size_t Main::kWindowHeight = 600;
const std::string Main::kName    = std::string("Test!");
Main*Main::_instance = NULL;

Main::Main():
    _viewMode(SPLASH)
{
    _instance = this;
}

void Main::main(){
    srand(time(NULL));
    
    sf::RenderWindow window(sf::VideoMode(kWindowWidth,kWindowHeight),kName);

    // Syncs framerate with monitor; should be ~60f/s.
    // This helps avoid frame tearing.
    window.setVerticalSyncEnabled(true);

    sf::CircleShape shape(kWindowWidth/2);
    shape.setFillColor(sf::Color::Green);

    TextureLoader*tl = TextureLoader::getInstance();    
    tl->loadAll();

    bool green=true;

    SplashView splash = SplashView();

    // MAIN LOOP.
    while(window.isOpen()){
	//================================
	// Handle events
	sf::Event event;
	while(window.pollEvent(event)){
	    switch(event.type){
	    case sf::Event::Closed:
		window.close();
		break;

	    case sf::Event::LostFocus:
		green = false;
		break;

	    case sf::Event::GainedFocus:
		green = true;
		break;

	    default:
		break;
	    }
	}

	//================================
	// Draw everything
	window.clear();

	// _viewMode may be changed; use view until window.display()
	ViewMode view = _viewMode;
	switch(view){
	case TEST:{
	    shape.setFillColor(green ? sf::Color::Green : sf::Color::Blue);
	    
	    sf::Sprite sprite;
	    sprite.setTexture(*tl->get("charlie80.png"));

	    window.draw(shape);
	    window.draw(sprite);
	    break;
	}

	case SPLASH:{
	    splash.draw(&window);
	    break;
	}
	}
	
	window.display();
    }
}

void Main::setView(ViewMode v){ _viewMode = v; }
Main*Main::getInstance(){ return _instance; }

int main(){
    Main m = Main();
    m.main();
}
