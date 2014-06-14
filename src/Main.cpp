#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <stdio.h>

#include "Main.hpp"
#include "TextureLoader.hpp"
#include "Utilities.hpp"

#include "View.hpp"
#include "SplashView.hpp"
#include "FontManager.hpp"
#include "Test3D/Test3DView.hpp"

const size_t Main::kWindowWidth  = 1000;
const size_t Main::kWindowHeight = 800;
const std::string Main::kName    = std::string("Test!");
Main*Main::_instance = NULL;

View*_views[] = {
    NULL,
    new Test3DView(),
    new SplashView()
};

Main::Main():
    _viewMode(SPLASH)
{
    printf("Initializing Main. Starting with view %d.\n", _viewMode);
    _instance = this;

    // Initialize all singletons
    FontManager::getInstance();
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

    // --------------------------------------------- initialize OpenGL
    glClearDepth(1.f);		// set color and depth clear value
    glClearColor(0.f,0.f,0.f,0.f);

    glEnable(GL_DEPTH_TEST);	// set up Z-buffer read/write
    glEnable(GL_CULL_FACE);
    glDepthFunc(GL_LEQUAL);
    glDepthMask(GL_TRUE);
    
    glMatrixMode(GL_PROJECTION); // set up a perspective projection
    glLoadIdentity();
    gluPerspective(90.f, 1.f, 1.f, 500.f);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    // ---------------------------------------------------------------

    if(_views[_viewMode])
	_views[_viewMode]->unpause();
    
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

	case SPLASH:
	case TEST3D:
	    _views[view]->draw(&window);
	    break;
	}
	
	window.display();
    }
}

void Main::setView(ViewMode v){
    if(_views[_viewMode])
	_views[_viewMode]->pause();
    
    _viewMode = v;
    printf("Set view mode to %d\n", _viewMode);
    
    if(_views[_viewMode])
	_views[_viewMode]->unpause();
}

Main*Main::getInstance(){ return _instance; }

int main(int argc, char*argv[]){
    Main m = Main();
    m.main();
    return 0;
}
