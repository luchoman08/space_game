#ifndef OBJETOEXPLOCION_HPP
#define OBJETOEXPLOCION_HPP
#include <SFML/Graphics.hpp>
#include <time.h>
class ObjetoExplocion{
	
	
	public:
	
	ObjetoExplocion(float tiempoInicio){
		this->tiempoInicio = tiempoInicio;
		};
	

	sf::Texture imagen;
	sf::Sprite sprite;
	float tiempoInicio;
	bool actualizarImagen(float currentTime){
			float temporal= currentTime - tiempoInicio;
			if(temporal <100){
			imagen.loadFromFile("graphics/BigExp00.png");
			sprite.setTexture(imagen, true);
			return true;
			}
			if(temporal >100 && temporal < 200){
			imagen.loadFromFile("graphics/BigExp01.png");
			sprite.setTexture(imagen, true);
			return true;
			}
			if(temporal >200 && temporal < 300){
			imagen.loadFromFile("graphics/BigExp02.png");
			sprite.setTexture(imagen, true);
			return true;
			}	
			if(temporal >300 && temporal < 400){
			imagen.loadFromFile("graphics/BigExp03.png");
			sprite.setTexture(imagen, true);
			}
			if(temporal >400 && temporal < 500){
			imagen.loadFromFile("graphics/BigExp04.png");
			sprite.setTexture(imagen, true);
			}
			if(temporal >500 && temporal < 600){
			imagen.loadFromFile("graphics/BigExp05.png");
			sprite.setTexture(imagen, true);
			return true;
			}
			if(temporal >600 && temporal < 700){
			imagen.loadFromFile("graphics/BigExp06.png");
			sprite.setTexture(imagen, true);
			return true;
			}
			if(temporal >700 && temporal < 800){
			imagen.loadFromFile("graphics/BigExp07.png");
			sprite.setTexture(imagen, true);
			return true;
			}
			if(temporal >800 && temporal < 1200){
			imagen.loadFromFile("graphics/BigExp08.png");
			sprite.setTexture(imagen, true);
			return true;
			}
			if(temporal >1200 && temporal < 1700){
			imagen.loadFromFile("graphics/BigExp09.png");
			sprite.setTexture(imagen, true);
			return true;
			}
			else
			{
				return false;
			}
			
		};
	
	private:
	
	
	
};

#endif

