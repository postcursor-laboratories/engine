#include <SFML/Graphics.hpp>
#include <stdio.h>
#include "Main.h"
#include "TextureLoader.h"
#include "Utilities.h"

const size_t Main::kWindowWidth  = 400;
const size_t Main::kWindowHeight = 400;
const std::string Main::kName = std::string("Test!");

int main(){
    sf::RenderWindow window(sf::VideoMode(Main::kWindowWidth,Main::kWindowHeight),Main::kName);

    // Syncs framerate with monitor; should be ~60f/s.
    // This helps avoid frame tearing.
    window.setVerticalSyncEnabled(true);

    sf::CircleShape shape(Main::kWindowWidth/2);
    shape.setFillColor(sf::Color::Green);

    bool green=true;

    TextureLoader*tl = TextureLoader::getInstance();    
    tl->loadAll();

    // MAIN LOOP.
    while(window.isOpen()){
	//================================
	// Handle events
	sf::Event event;
	while(window.pollEvent(event)){
	    if(event.type == sf::Event::Closed)
		window.close();
	    
	    if (event.type == sf::Event::LostFocus)
		green = false;

	    if (event.type == sf::Event::GainedFocus)
		green = true;
	}

	//================================
	// Set things up to be drawn
	shape.setFillColor(green ? sf::Color::Green : sf::Color::Blue);

	sf::Sprite sprite;
	sprite.setTexture(*tl->get(0));
	
	//================================
	// Draw everything
	window.clear();

	window.draw(shape);
	window.draw(sprite);
	
	window.display();
    }

    return 0;
}
