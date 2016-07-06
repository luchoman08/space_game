#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP
#include <SFML/Graphics.hpp>
#include <math.h>
#include <stdio.h>
class GameObject{
	
	public:
	sf::Texture imagen;
	sf::Sprite sprite;
	int Draw(sf::RenderWindow & renderWindow);
	sf::Vector2f posicionInicial;
	int Update(float hora_actual);//actualiza la velocidad y la posicion
	int ancho;
	int alto;
	int direccion; //rotacion de la nave en grados
	double aceleracion; //en decametros por segundo
	float velocidad; //en pixeles por tick de pantalla
	double peso;//cada pixel es un kilogramo
	float hora_creacion;
	void actualizarPeso(); //n
	void actualizarVelocidad(float hora_actual);
	void actualizarPosicion(float hora_actual);
	void mover(int cantPixeles, int direccion);
	void recibirImpulso(float pesoObjeto, float velocidadObjeto);
	private:
		
};
#endif
