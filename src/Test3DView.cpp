#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "Test3DView.hpp"
#include "Main.hpp"

Test3DView::Test3DView(){}

// Calls to glColor3f no longer do anything when lighting is enabled.
// You have to set material properties. This does BOTH, for MAXIMUM
// COLORNESS and EXTREME FABULOSITY
#define COLOR_LIGHTING(r,g,b) {				\
	float color[] = { r, g, b, 1 };			\
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);	\
	glColor3f(r,g,b);				\
    }

void Test3DView::draw(sf::RenderTarget*rt){
    static sf::Clock clock;
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.f, 0.f, -200.f);

    // rotate world by 90 degrees widdershins about k hat
    //glRotatef(90,0,0,1);

    glRotatef(-45,1,0,0);
    glRotatef(-135,0,0,1);

    float pos[] = { 100, 100, 100, 1 };
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    //float cutoff[] = { 45 };
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
    
    glFlush();
}

void Test3DView::pause(){}
void Test3DView::unpause(){}
