#include <SFML/Graphics.hpp>
#include "Main.h"
#include "TextureLoader.h"

int main(){
    sf::RenderWindow window(sf::VideoMode(MAIN_WINDOW_WIDTH,
					  MAIN_WINDOW_HEIGHT), MAIN_NAME);

    // Syncs framerate with monitor; should be ~60f/s.
    // This helps avoid frame tearing.
    window.setVerticalSyncEnabled(true);

    sf::CircleShape shape(MAIN_WINDOW_WIDTH/2);
    shape.setFillColor(sf::Color::Green);

    bool green=true;

    TextureLoader*tl = TextureLoader::getInstance();    
    tl->load();

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
	sprite.setTexture(TextureLoader::getInstance()->getByName(std::string("")));
	
	//================================
	// Draw everything
	window.clear();

	window.draw(shape);
	window.draw(sprite);
	
	window.display();
    }

    return 0;
}
