#include "../include/MenuInicial.hpp"


MenuInicial::MenuInicial(float width, float height)
{
	if (!font.loadFromFile("fonts/arial.ttf"))
	{
		// handle error
	}

	this->width=width;
	this->height=height;
	selectedItemIndex = 0;
	
}
void MenuInicial::inicializar()
{
	if (!font.loadFromFile("fonts/arial.ttf"))
	{
		// handle error
	}
	for(int i = 0; i < textos.size();i++){
	sf::Text* tmp=new sf::Text;
	tmp->setFont(font);
	tmp->setColor(sf::Color::White);
	tmp->setString(textos.at(i));
	tmp->setPosition(sf::Vector2f(width / 2, height / ((textos.size() + 1) * (i+1))));
	menuVector.push_back(tmp);
	}
	selectedItemIndex = 0;
}


MenuInicial::~MenuInicial()
{
}

void MenuInicial::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < menuVector.size(); i++)
	{
		window.draw(*menuVector.at(i));
	}
}

void MenuInicial::MoveUp()
{

		menuVector.at(selectedItemIndex)->setColor(sf::Color::White);
		selectedItemIndex=(selectedItemIndex-1);
		if(selectedItemIndex<0)
		selectedItemIndex=1;
		menuVector.at(selectedItemIndex)->setColor(sf::Color::Red);
	
}

void MenuInicial::MoveDown()
{
	
		menuVector.at(selectedItemIndex)->setColor(sf::Color::White);
		selectedItemIndex=(selectedItemIndex+1)%(menuVector.size());
		menuVector.at(selectedItemIndex)->setColor(sf::Color::Red);
	
}

void MenuInicial::adicionarTexto(std::string texto){
	this->textos.push_back(texto);
}
