#include <cmath>
#include <stdio.h>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "SplashView.hpp"
#include "TextureLoader.hpp"
#include "FontManager.hpp"
#include "Main.hpp"

SplashView::SplashView():
    _milliseconds(0)
{
    std::vector<std::string> slogans;
    std::ifstream in("res/slogans.txt");

    std::string line;
    while(std::getline(in,line))
	if(!line.empty())
	    slogans.push_back(line);

    std::string sloganChoice = slogans.size() ?
	slogans.at(rand()%slogans.size()) : "Filesystem? More like Failsystem!";
    
    _slogan.setString(sloganChoice);
    _slogan.setFont(*FontManager::getInstance()->get("res/lucida-console.ttf"));
    _slogan.setCharacterSize(20);
    _slogan.setColor(sf::Color::Black);
    _slogan.setPosition(Main::kWindowWidth/2-_slogan.getGlobalBounds().width/2,
			Main::kWindowHeight*.75);
    _slogan.setStyle(sf::Text::Italic);
}

void SplashView::init(){}

void SplashView::pause(){}

void SplashView::unpause(){
    _milliseconds = 0;
    _clock.restart();
}

void SplashView::update(){}

void SplashView::draw(sf::RenderTarget*rt){
    rt->pushGLStates();
    _milliseconds += _clock.restart().asMilliseconds();    

    //================================
    // Deal with logo
    double alpha;
    if(_milliseconds<50)
	alpha = 0;
    else if(_milliseconds<1050)
	alpha = sqrt((_milliseconds-50)/1000.);
    else if(_milliseconds<3000)
	alpha = 1;
    else if(_milliseconds<4000)
	alpha = sqrt((4000-_milliseconds)/1000.);
    else if(_milliseconds<4200)
	alpha = 0;
    else{
	alpha = 0;
	Main::getInstance()->setView(TEST3D);
    }

    sf::Texture*texture = TextureLoader::getInstance()
	->get((_milliseconds%1000/500) ? "pl-logoframe2.png" : "pl-logoframe1.png");

    sf::Sprite sprite;
    sprite.setTexture(*texture);
    sprite.setColor(sf::Color(255,255,255,(int)(alpha*255)));

    sprite.setPosition(sf::Vector2f(Main::kWindowWidth/2 -texture->getSize().x/2,
				    Main::kWindowHeight/2-texture->getSize().y/2));
    
    rt->clear(sf::Color((int)(alpha*255),(int)(alpha*255),(int)(alpha*255)));
    rt->draw(sprite);
    rt->draw(_slogan);
    rt->popGLStates();
}
