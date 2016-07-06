#include "BarraProgreso.hpp"

BarraProgreso::BarraProgreso(){};
BarraProgreso::BarraProgreso(sf::Color color100_50, sf::Color color49_25, sf::Color color24_0, sf::Color colorBorde,  sf::Vector2f tamanioInicial, sf::Vector2f posicionInicial,float valorInicial){
	this->color100_50=color100_50;
	this->color49_25=color49_25;
	this->color24_0=color24_0;
	this->tamanioInicial=tamanioInicial;
	this->objeto.setSize(tamanioInicial);
	this->objeto.setPosition(posicionInicial);
	this->objeto.setFillColor(color100_50);
	this->objeto.setOutlineColor(colorBorde);
	this->valorInicial=valorInicial;
	this->porcentaje=100;
	
}

void BarraProgreso::setTamanoInicial(sf::Vector2f nTamanioInicial){
	this->tamanioInicial= nTamanioInicial;
}
void BarraProgreso::setColorFondo(sf::Color nColor){
	this->objeto.setFillColor(nColor);
}
void BarraProgreso::setColorBorde(sf::Color nColor){
	this->objeto.setOutlineColor(nColor);
}
void BarraProgreso::setPosicion(sf::Vector2f nPosicion){
	this->objeto.setPosition(nPosicion);
}
void BarraProgreso::setPorcentaje(float nPorcentaje){
	this->porcentaje=nPorcentaje;
	
}
void BarraProgreso::draw(sf::RenderWindow &window){
	window.draw(this->objeto);
}
sf::Vector2f BarraProgreso::getTamanoInicial(){
	return this->tamanioInicial;
}
void BarraProgreso::cambiarTamanioObjetoPorcentaje(){	
	this->objeto.setSize(sf::Vector2f(this->tamanioInicial.x*(this->porcentaje/100), this->getTamanoInicial().y));	
}
void BarraProgreso::cambiarColorObjetoPorcentaje(){
	if(this->porcentaje>=0&&this->porcentaje<25){
		this->objeto.setFillColor(this->color24_0);
	}
	if(this->porcentaje>=25&&this->porcentaje<50){
		this->objeto.setFillColor(this->color49_25);
	}
	if(this->porcentaje>=50&&this->porcentaje<=100){
		this->objeto.setFillColor(this->color100_50);
	}
}
void BarraProgreso::update(float nValor)
{
	
	this->porcentaje=(nValor*100)/valorInicial;
	this->cambiarTamanioObjetoPorcentaje();
	this->cambiarColorObjetoPorcentaje();
}


