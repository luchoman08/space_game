#pragma once
#include <SFML/Graphics.hpp>


class BarraProgreso{

public:
	BarraProgreso();
	BarraProgreso( sf::Color color100_50, sf::Color color49_25, sf::Color color24_0, sf::Color colorBorde,  sf::Vector2f tamanioInicial,  sf::Vector2f posicionInicial, float valorInicial);

	void setTamanoInicial(sf::Vector2f nTamanioInicial);
	void setColorFondo(sf::Color nColor);
	void setColorBorde(sf::Color nColor);
	void setPosicion(sf::Vector2f nPosicion);
	void setPorcentaje(float nPorcentaje);
	void draw(sf::RenderWindow &window);
	sf::Vector2f getTamanoInicial();
	float getPorcentaje();
	void update(float nValor);
	void cambiarTamanioObjetoPorcentaje();//dependiendo del porcentaje cambia el tamaño de la barra
	void cambiarColorObjetoPorcentaje(); //cambia el color de la barra dependiendo el porcentaje que tenga

private:
	sf::Color color100_50; //el color de la barra entre 100% de vida y 50;
	sf::Color color49_25;
	sf::Color color24_0;
	sf::RectangleShape objeto;
	sf::Vector2f tamanioInicial;	
	float porcentaje;
	float valorInicial;

};
