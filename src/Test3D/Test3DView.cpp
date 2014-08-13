#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include <stdio.h>

#include "Test3DView.hpp"
#include "Test3DPlayer.hpp"
#include "../FontManager.hpp"
#include "../Main.hpp"

#include <time.h>

static void box(float x, float y, float z, float size);

Test3DView::Test3DView(){
    _player = new Test3DPlayer(0,20,0,0,0,0);
}

// Calls to glColor3f no longer do anything when lighting is enabled.
// You have to set material properties. This does BOTH, for MAXIMUM
// COLORNESS and EXTREME FABULOSITY
#define COLOR_LIGHTING(r,g,b) {				\
	float color[] = { r, g, b, 1 };			\
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);	\
	glColor3f(r,g,b);				\
    }

//#define ENABLE_TDEBUG
#ifdef ENABLE_TDEBUG
// To help debug performance.
timespec _Ttime;
#define T() do{								\
	timespec t;							\
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&t);			\
	timespec diff = timespec_diff(_Ttime,t);			\
	if(diff.tv_nsec > 50000){					\
	    printf("T() : %d:\t%luns\n", __LINE__, diff.tv_nsec);	\
	}								\
	_Ttime = t;							\
    }while(0)

static timespec timespec_diff(timespec start, timespec end){
    timespec temp;
    if ((end.tv_nsec-start.tv_nsec)<0) {
	temp.tv_sec = end.tv_sec-start.tv_sec-1;
	temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
    } else {
	temp.tv_sec = end.tv_sec-start.tv_sec;
	temp.tv_nsec = end.tv_nsec-start.tv_nsec;
    }
    return temp;
}
#else
#define T() {}
#endif

void Test3DView::update(){
    T();
    
    // update player's coordinates
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	_player->moveRel(0,1,0,0,0,0);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	_player->moveRel(0,-1,0,0,0,0);
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	_player->moveRel(-1,0,0,0,0,0);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	_player->moveRel(1,0,0,0,0,0);
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	_player->moveRel(0,0,0,0,1,0);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	_player->moveRel(0,0,0,0,-1,0);
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	_player->moveRel(0,0,1,0,0,0);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
	_player->moveRel(0,0,-1,0,0,0);
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::T))
	_player->moveRel(0,0,0,1,0,0);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::G))
	_player->moveRel(0,0,0,-1,0,0);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
	_player->moveRel(0,0,0,0,0,1);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::H))
	_player->moveRel(0,0,0,0,0,-1);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)){
	_player->dumpState();
    }
    
    T();
}

#if 0
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
#endif

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

    /* // ~8fps
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
    */

    /*
    glPushMatrix();
    COLOR_LIGHTING(0,1,0);
    glBegin(GL_QUADS);

    for(int i=-100; i<=100; i++){
	for(int j=-100; j<=100; j++){
	    T();
	    glPushMatrix();
	    glTranslatef(i,j,-40);
	    glNormal3f(0,0,1);
	    glVertex3f( 1,-1, 1);
	    glVertex3f( 1, 1, 1);
	    glVertex3f(-1, 1, 1);
	    glVertex3f(-1,-1, 1);
	    glPopMatrix();
	    T();
	}
    }
    glEnd();
    glPopMatrix();
    */

    glPushMatrix();
    COLOR_LIGHTING(0,1,0);
    glTranslatef(0,0,-40);

    glBegin(GL_QUADS);
    for(int i=-100; i<=100; i++){
	for(int j=-100; j<=100; j++){
	    T();
	    glNormal3f(0,0,1);
	    glVertex3f( 1+i, -1+j, 1);
	    glVertex3f( 1+i,  1+j, 1);
	    glVertex3f(-1+i,  1+j, 1);
	    glVertex3f(-1+i, -1+j, 1);
	    T();
	}
    }
    glEnd();

    //glPushMatrix();
    
    COLOR_LIGHTING(1,0,0);
    glBegin(GL_QUADS);

    glNormal3f(0,0,1);
    glVertex3f( 1,-1, 1);
    glVertex3f( 1, 1, 1);
    glVertex3f(-1, 1, 1);
    glVertex3f(-1,-1, 1);

    glTranslatef(0,4,0);

    COLOR_LIGHTING(0,1,0);
    glNormal3f(0,0,1);
    glVertex3f( 1+5,-1, 1);
    glVertex3f( 1+5, 1, 1);
    glVertex3f(-1+5, 1, 1);
    glVertex3f(-1+5,-1, 1);
    
    glEnd();
    glPopMatrix();

    // ---------------- Draw axes.
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
    // ----------------
    
    glFlush();
}

void Test3DView::pause(){}
void Test3DView::unpause(){}
