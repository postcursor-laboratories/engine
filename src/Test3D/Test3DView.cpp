#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include <stdio.h>

#include "Test3DView.hpp"
#include "Test3DPlayer.hpp"
#include "../FontManager.hpp"
#include "../Main.hpp"

Test3DView::Test3DView(){
    _player = new Test3DPlayer(0,0,-200,180,0);
}

// Calls to glColor3f no longer do anything when lighting is enabled.
// You have to set material properties. This does BOTH, for MAXIMUM
// COLORNESS and EXTREME FABULOSITY
#define COLOR_LIGHTING(r,g,b) {				\
	float color[] = { r, g, b, 1 };			\
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);	\
	glColor3f(r,g,b);				\
    }

void Test3DView::update(){
    // update player's coordinates
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	_player->move(1,0,0,0,0);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	_player->move(-1,0,0,0,0);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	_player->move(0,1,0,0,0);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	_player->move(0,-1,0,0,0);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	_player->move(0,0,1,0,0);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	_player->move(0,0,-1,0,0);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	_player->move(0,0,0,1,0);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
	_player->move(0,0,0,-1,0);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::T))
	_player->move(0,0,0,0,1);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::G))
	_player->move(0,0,0,0,-1);
}

void Test3DView::draw(sf::RenderTarget*rt){
    static sf::Clock clock;
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Translate the world (so, position the camera)
    _player->performGLTransformations();

    // rotate world by 90 degrees widdershins about k hat
    //glRotatef(90,0,0,1);

    //glRotatef(-45,1,0,0);
    //glRotatef(-135,0,0,1);

    float pos[] = { 100, 100, 100, 1 };
    glLightfv(GL_LIGHT0, GL_POSITION, pos);

    // OpenGL seems to do spotlight cutoffs on a per-polygon basis, so having a narrow spotlight will
    // not have a circle of light on the cube; it'll make the triangles in the cube light up and go
    // black in a weird ugly manner. I think this may only be useful and pretty for things with very
    // high polygon counts.
    //float cutoff[] = { 30 };
    //glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, cutoff);

    // Draw axes.
    glBegin(GL_LINES);
    {
	COLOR_LIGHTING(1,0,0);
	glVertex3f(0,   0,   0);
	glVertex3f(100, 0,   0);

    	COLOR_LIGHTING(0,1,0);
	glVertex3f(0,   0,   0);
	glVertex3f(0, 100,   0);

    	COLOR_LIGHTING(0,0,1);
	glVertex3f(0,   0,   0);
	glVertex3f(0,   0, 100);
    }
    glEnd();
    
    // ----------------------------------------------------------------
    // Enter box coordinates
    glPushMatrix();    
    glRotatef(clock.getElapsedTime().asSeconds()*50, 1, 0, 0);
    glRotatef(clock.getElapsedTime().asSeconds()*30, 0, 1, 0);
    glRotatef(clock.getElapsedTime().asSeconds()*90, 0, 0, 1);
    
    glBegin(GL_QUADS);
    {
	float size = 50;
	
	// BLUE
	COLOR_LIGHTING(0,0,1);
	glNormal3f(0,0,-1);
	glVertex3f(-size,-size,-size);
	glVertex3f(-size, size,-size);
	glVertex3f( size, size,-size);
	glVertex3f( size,-size,-size);

	// GREEN
	COLOR_LIGHTING(0,1,0);
	glNormal3f(0,0,1);
	glVertex3f( size,-size, size);
	glVertex3f( size, size, size);
	glVertex3f(-size, size, size);
	glVertex3f(-size,-size, size);

	// BLUE-GREEN
	COLOR_LIGHTING(0,1,1);
	glNormal3d(-1,0,0);
	glVertex3f(-size,-size, size);
	glVertex3f(-size, size, size);
	glVertex3f(-size, size,-size);
	glVertex3f(-size,-size,-size);

	// RED
	COLOR_LIGHTING(1,0,0);
	glNormal3d(1,0,0);
	glVertex3f( size,-size,-size);
	glVertex3f( size, size,-size);
	glVertex3f( size, size, size);
	glVertex3f( size,-size, size);

	// PURPLE
	COLOR_LIGHTING(1,0,1);
	glNormal3d(0,-1,0);
	glVertex3f(-size,-size, size);
	glVertex3f(-size,-size,-size);
	glVertex3f( size,-size,-size);
	glVertex3f( size,-size, size);

	// YELLOW
	COLOR_LIGHTING(1,1,0);
	glNormal3d(0,1,0);
	glVertex3f( size, size, size);
	glVertex3f( size, size,-size);
	glVertex3f(-size, size,-size);
	glVertex3f(-size, size, size);
    }
    glEnd();

    // Leave box coordinates
    glPopMatrix();
    
    // ---------------------------------------------------------------------
    // We here draw debugging information on the screen.

    // Calculate FPS
    static sf::Time lastTime = clock.getElapsedTime();
    sf::Time dtime = clock.getElapsedTime()-lastTime;
    lastTime = clock.getElapsedTime();
    float fps = 1/dtime.asSeconds(); // 1/(seconds/frame) = frame/second

    // Draw fps graph
    {
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
    }
    
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
    // -------------------------
}

void Test3DView::pause(){}
void Test3DView::unpause(){}
