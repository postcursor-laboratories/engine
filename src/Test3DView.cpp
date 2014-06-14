#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "Test3DView.hpp"
#include "Main.hpp"

Test3DView::Test3DView(){}

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
	glColor3f (1,   0,   0);
	glVertex3f(0,   0,   0);
	glVertex3f(100, 0,   0);

    	glColor3f (0,   1,   0);
	glVertex3f(0,   0,   0);
	glVertex3f(0, 100,   0);

    	glColor3f (0,   0,   1);
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
	glColor3f(0,0,1);
	glNormal3f(0,0,-1);
	glVertex3f(-size,-size,-size);
	glVertex3f(-size, size,-size);
	glVertex3f( size, size,-size);
	glVertex3f( size,-size,-size);

	// GREEN
	glColor3f(0,1,0);
	glNormal3f(0,0,1);
	glVertex3f( size,-size, size);
	glVertex3f( size, size, size);
	glVertex3f(-size, size, size);
	glVertex3f(-size,-size, size);

	// BLUE-GREEN
	glColor3f(0,1,1);
	glNormal3d(-1,0,0);
	glVertex3f(-size,-size, size);
	glVertex3f(-size, size, size);
	glVertex3f(-size, size,-size);
	glVertex3f(-size,-size,-size);

	// RED
	glColor3f(1,0,0);
	glNormal3d(1,0,0);
	glVertex3f( size,-size,-size);
	glVertex3f( size, size,-size);
	glVertex3f( size, size, size);
	glVertex3f( size,-size, size);

	// PURPLE
	glColor3f(1,0,1);
	glNormal3d(0,-1,0);
	glVertex3f(-size,-size, size);
	glVertex3f(-size,-size,-size);
	glVertex3f( size,-size,-size);
	glVertex3f( size,-size, size);

	// YELLOW
	glColor3f(1,1,0);
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
