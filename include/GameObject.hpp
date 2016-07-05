#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP
#include <SFML/Graphics.hpp>
class GameObject{
	
	public:
	sf::Texture imagen;
	sf::Sprite sprite;
	int Draw(sf::RenderWindow & renderWindow);
	int ancho;
	int alto;
	int direccion; //rotacion de la nave en grados
	double aceleracion; 
	double peso;//cada pixel es un kilogramo
	
	void actualizarPeso(); //n
	void mover();
	private:
		
};
#endif
