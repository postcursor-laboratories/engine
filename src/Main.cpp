#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

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

void Main::displayDebuggingInformation(sf::RenderTarget*rt){
    // We here draw debugging information on the screen.

    // Calculate FPS
    static sf::Time lastTime = _clock.getElapsedTime();
    sf::Time dtime = _clock.getElapsedTime()-lastTime;
    lastTime = _clock.getElapsedTime();
    float fps = 1/dtime.asSeconds(); // 1/(seconds/frame) = frame/second

    // Draw fps graph
    rt->pushGLStates();
	
    // Enter 2D Mode
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0,Main::kWindowWidth,Main::kWindowHeight,0,-1,10);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glDisable(GL_CULL_FACE);
    glClear(GL_DEPTH_BUFFER_BIT);

    // ----------------------- do 2D drawing
    const int graphH = 100;
    const int graphW = 200;
    static int pastFPSs[graphW];
    static int pastFPSsIndex = 0;
    pastFPSsIndex = (pastFPSsIndex+1)%graphW;
    pastFPSs[pastFPSsIndex] = (int)fps;
	
    glTranslatef(Main::kWindowWidth-graphW,0,0);

    // draw background
    glColor4f(1,0,0,.4);
    glBegin(GL_QUADS);
    {
	glVertex2f(0,0);
	glVertex2f(graphW,0);
	glVertex2f(graphW,graphH);
	glVertex2f(0,graphH);
    }
    glEnd();

    // draw data
    glBegin(GL_LINES);
    glColor4f(0,0,1,.6);
    for(int i=0; i<graphW; i++){
	int index = (pastFPSsIndex+i+1)%graphW;
	glVertex2f(i,graphH);
	glVertex2f(i,graphH-pastFPSs[index]);
    }
    glEnd();	
    // ------------------------ done with 2D drawing
	
    // Bring back 3D Mode
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    rt->popGLStates();
    glFlush();

    // -------------------------
    // Enter SFML drawing mode
    rt->pushGLStates();
    rt->resetGLStates();
    
    // draw current fps
    char s[9];
    snprintf(s, 8, "%0.1ffps", fps);
    sf::Text text(s, *FontManager::getInstance()->get("res/lucida-console.ttf"), 12);
    text.setPosition(Main::kWindowWidth-50, 0);
    rt->draw(text);
    
    rt->popGLStates();
    // Exit SFML drawing mode
}

Main::Main():
    _viewMode(TEST3D), _displayDebuggingInformation(true)
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

    printf("OpenGL version is %s\n", glGetString(GL_VERSION));
    
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

	    case sf::Event::KeyPressed:
		if(event.key.code == sf::Keyboard::Key::F3)
		    _displayDebuggingInformation = !_displayDebuggingInformation;

		// TODO: handle keypress
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
	    _views[view]->update();
	    _views[view]->draw(&window);
	    break;
	}

	if(_displayDebuggingInformation)
	    displayDebuggingInformation(&window);
	
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
