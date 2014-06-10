#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <stdio.h>

#include "Main.hpp"
#include "TextureLoader.hpp"
#include "Utilities.hpp"

#include "View.hpp"
#include "SplashView.hpp"
#include "Test3DView.hpp"

const size_t Main::kWindowWidth  = 800;
const size_t Main::kWindowHeight = 600;
const std::string Main::kName    = std::string("Test!");
Main*Main::_instance = NULL;

Main::Main():
    _viewMode(TEST3D)
{
    printf("Initializing Main. Starting with view %d.\n", _viewMode);
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

    // Initialize 3D stuff!
    Test3DView test3d = Test3DView();

    glClearDepth(1.f);		// set color and depth clear value
    glClearColor(0.f,0.f,0.f,0.f);

    glEnable(GL_DEPTH_TEST);	// set up Z-buffer read/write
    glEnable(GL_CULL_FACE);
    glDepthFunc(GL_LEQUAL);
    glDepthMask(GL_TRUE);

    glMatrixMode(GL_PROJECTION); // set up a perspective projection
    glLoadIdentity();
    gluPerspective(90.f, 1.f, 1.f, 500.f);

    //glShadeModel(GL_SMOOTH);
    
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

	    case sf::Event::Resized:
		glViewport(0,0,event.size.width,event.size.height);
		break;
		
	    default:
		break;
	    }
	}

	//================================
	// Draw everything
	window.clear();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

	case TEST3D:{
	    test3d.draw(&window);
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

void Main::setView(ViewMode v){
    _viewMode = v;
    printf("Set view mode to %d\n", v);
}

Main*Main::getInstance(){ return _instance; }

int main(int argc, char*argv[]){
    Main m = Main();
    m.main();
    return 0;
}
