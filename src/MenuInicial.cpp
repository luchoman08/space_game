#include "../include/MenuInicial.hpp"


MenuInicial::MenuInicial(float width, float height)
{
	if (!font.loadFromFile("fonts/arial.ttf"))
	{
		// handle error
	}

	menu[0].setFont(font);
	menu[0].setColor(sf::Color::Red);
	menu[0].setString("Continuar");
	menu[0].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));

	menu[1].setFont(font);
	menu[1].setColor(sf::Color::White);
	menu[1].setString("Terminar Partida");
	menu[1].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));


	selectedItemIndex = 0;
}


MenuInicial::~MenuInicial()
{
}

void MenuInicial::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
}

void MenuInicial::MoveUp()
{

		menu[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex=(selectedItemIndex-1);
		if(selectedItemIndex<0)
		selectedItemIndex=1;
		menu[selectedItemIndex].setColor(sf::Color::Red);
	
}

void MenuInicial::MoveDown()
{
	
		menu[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex=(selectedItemIndex+1)%(MAX_NUMBER_OF_ITEMS);
		menu[selectedItemIndex].setColor(sf::Color::Red);
	
}
