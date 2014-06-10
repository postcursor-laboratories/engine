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

    glColor3f(0,0,1);
    glBegin(GL_QUADS);
    {
	glVertex3f(-50,-50,-50);
	glVertex3f(-50, 50,-50);
	glVertex3f( 50, 50,-50);
	glVertex3f( 50,-50,-50);

	glVertex3f(-50,-50, 50);
	glVertex3f(-50, 50, 50);
	glVertex3f( 50, 50, 50);
	glVertex3f( 50,-50, 50);

	glVertex3f(-50,-50,-50);
	glVertex3f(-50, 50,-50);
	glVertex3f(-50, 50, 50);
	glVertex3f(-50,-50, 50);

	glVertex3f( 50,-50,-50);
	glVertex3f( 50, 50,-50);
	glVertex3f( 50, 50, 50);
	glVertex3f( 50,-50, 50);

	glVertex3f(-50,-50, 50);
	glVertex3f(-50,-50,-50);
	glVertex3f( 50,-50,-50);
	glVertex3f( 50,-50, 50);

	glVertex3f(-50, 50, 50);
	glVertex3f(-50, 50,-50);
	glVertex3f( 50, 50,-50);
	glVertex3f( 50, 50, 50);
    }
    glEnd();
}

void Test3DView::pause(){}
void Test3DView::unpause(){}
