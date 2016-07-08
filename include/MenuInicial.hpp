
#pragma once
#include <SFML/Graphics.hpp>

//#define MAX_NUMBER_OF_ITEMS 2
#include <vector>
#include <string>
class MenuInicial
{
public:
	MenuInicial(float width, float height);
	~MenuInicial();
	void inicializar();
	void draw(sf::RenderWindow &window);
	void MoveUp(float deltaTime);
	void MoveDown(float deltaTime);
	float hora_activacion=0;
	float tiempoActivacion = 400;
	int GetPressedItem(float deltaTime) {
		if(deltaTime-hora_activacion>tiempoActivacion)
		 return selectedItemIndex;
		 
		 else
		 return -50; }
	void adicionarTexto(std::string texto);
private:
	int selectedItemIndex;
	sf::Font font;
	std::vector<sf::Text*> menuVector;
	std::vector<std::string> textos;
	float width; 
	float height;
};
