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
    glRotatef(clock.getElapsedTime().asSeconds()*50, 1, 0, 0);
    glRotatef(clock.getElapsedTime().asSeconds()*30, 0, 1, 0);
    glRotatef(clock.getElapsedTime().asSeconds()*90, 0, 0, 1);

    glBegin(GL_QUADS);
    {
	float size = 50;

	// BLUE
	glColor3f(0,0,1);
	glVertex3f(-size,-size,-size);
	glVertex3f(-size, size,-size);
	glVertex3f( size, size,-size);
	glVertex3f( size,-size,-size);

	// GREEN
	glColor3f(0,1,0);
	glVertex3f( size,-size, size);
	glVertex3f( size, size, size);
	glVertex3f(-size, size, size);
	glVertex3f(-size,-size, size);

	// BLUE-GREEN
	glColor3f(0,1,1);
	glVertex3f(-size,-size, size);
	glVertex3f(-size, size, size);
	glVertex3f(-size, size,-size);
	glVertex3f(-size,-size,-size);

	// RED
	glColor3f(1,0,0);
	glVertex3f( size,-size,-size);
	glVertex3f( size, size,-size);
	glVertex3f( size, size, size);
	glVertex3f( size,-size, size);

	// PURPLE
	glColor3f(1,0,1);
	glVertex3f(-size,-size, size);
	glVertex3f(-size,-size,-size);
	glVertex3f( size,-size,-size);
	glVertex3f( size,-size, size);

	// YELLOW
	glColor3f(1,1,0);
	glVertex3f( size, size, size);
	glVertex3f( size, size,-size);
	glVertex3f(-size, size,-size);
	glVertex3f(-size, size, size);
    }
    glEnd();
}

void Test3DView::pause(){}
void Test3DView::unpause(){}
