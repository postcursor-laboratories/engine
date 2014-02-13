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
    
    while(window.isOpen()){
	sf::Event event;
	while(window.pollEvent(event)){
	    if(event.type == sf::Event::Closed)
		window.close();
	    
	    if (event.type == sf::Event::LostFocus)
		green = false;

	    if (event.type == sf::Event::GainedFocus)
		green = true;
	}

	shape.setFillColor(green ? sf::Color::Green : sf::Color::Blue);
	
	window.clear();
	window.draw(shape);
	window.display();
    }

    return 0;
}
