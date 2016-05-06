#ifndef METEORO_H
#define METEORO_H
#include <vector>
#include <SFML/Graphics.hpp>

class Meteoro{
	public:
	Meteoro(){tamanio = 1; puntos_vida = 2;};
	sf::Sprite Sprite;
	int tamanio;
	int puntos_vida;
};

#endif
