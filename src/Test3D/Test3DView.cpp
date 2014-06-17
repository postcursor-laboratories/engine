#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include <stdio.h>

#include "Test3DView.hpp"
#include "Test3DPlayer.hpp"
#include "../FontManager.hpp"
#include "../Main.hpp"

static void box(float x, float y, float z, float size);

Test3DView::Test3DView(){
    _player = new Test3DPlayer(0,0,-200,0,0,0);
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
	_player->move(1,0,0,0,0,0);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	_player->move(-1,0,0,0,0,0);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	_player->move(0,1,0,0,0,0);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	_player->move(0,-1,0,0,0,0);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	_player->move(0,0,1,0,0,0);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	_player->move(0,0,-1,0,0,0);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	_player->move(0,0,0,1,0,0);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
	_player->move(0,0,0,-1,0,0);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::T))
	_player->move(0,0,0,0,1,0);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::G))
	_player->move(0,0,0,0,-1,0);
}

static void box(float x, float y, float z, float size){
    glPushMatrix();
    glTranslatef(x,y,z);
    COLOR_LIGHTING(0,1,0);

    glBegin(GL_QUADS);
    {
    	glNormal3f(0,0,-1);
	glVertex3f(-size,-size,-size);
	glVertex3f(-size, size,-size);
	glVertex3f( size, size,-size);
	glVertex3f( size,-size,-size);

	glNormal3f(0,0,1);
	glVertex3f( size,-size, size);
	glVertex3f( size, size, size);
	glVertex3f(-size, size, size);
	glVertex3f(-size,-size, size);

	glNormal3d(-1,0,0);
	glVertex3f(-size,-size, size);
	glVertex3f(-size, size, size);
	glVertex3f(-size, size,-size);
	glVertex3f(-size,-size,-size);

	glNormal3d(1,0,0);
	glVertex3f( size,-size,-size);
	glVertex3f( size, size,-size);
	glVertex3f( size, size, size);
	glVertex3f( size,-size, size);

	glNormal3d(0,-1,0);
	glVertex3f(-size,-size, size);
	glVertex3f(-size,-size,-size);
	glVertex3f( size,-size,-size);
	glVertex3f( size,-size, size);

	glNormal3d(0,1,0);
	glVertex3f( size, size, size);
	glVertex3f( size, size,-size);
	glVertex3f(-size, size,-size);
	glVertex3f(-size, size, size);
    }
    glEnd();

    glPopMatrix();
}

void Test3DView::draw(sf::RenderTarget*rt){
    static sf::Clock clock;
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Transform the world (so, position the camera)
    _player->performGLTransformations();

    // Set up light0; this will be the sun!
    float pos[] = { 0, 0, 1, 0 };
    glLightfv(GL_LIGHT0, GL_POSITION, pos);

    float amb[] = { .2, .2, .2, 1 };
    glLightfv(GL_LIGHT0, GL_AMBIENT, amb);

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
    /*
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
    */
    
    // ---------------------------------------------------------------------
    // Draw the ground.
    for(int i=-100; i<=100; i++)
	for(int j=-100; j<=100; j++){
	    // moving around the matrix push/pops doesn't seem to significantly boost performance
	    glPushMatrix();
	    glTranslatef(i,j,-40);
	    COLOR_LIGHTING(0,1,0);
	    glBegin(GL_QUADS);
	    glNormal3f(0,0,1);
	    glVertex3f( 1,-1, 1);
	    glVertex3f( 1, 1, 1);
	    glVertex3f(-1, 1, 1);
	    glVertex3f(-1,-1, 1);
	    glEnd();
	    glPopMatrix();
	    //box(i,j,-40,1);
	}
        
    glFlush();
}

void Test3DView::pause(){}
void Test3DView::unpause(){}
