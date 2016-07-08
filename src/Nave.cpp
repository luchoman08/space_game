#include "Nave.hpp"

Nave::Nave(){
	this->aceleracion=0;
	this->direccion=180;
	this->peso=0;
	this->propulsion=new GameObject();
	this->tiempoCargaMisil=0;
	propulsion->imagen.loadFromFile("graphics/JetTrail.png");
	propulsion->sprite.setTexture(propulsion->imagen, true);

	};
Nave::Nave(int cantVidas,int velocidadRecargaMetralla){
	this->aceleracion=0;
	this->propulsion=new GameObject();
	this->velocidadRecargaMetralla=velocidadRecargaMetralla;
	this->vidas = cantVidas;
	this->direccion=180;
	this->peso=0;
	this->tiempoCargaMisil=0;
	};
Nave::~Nave(){};
int Nave::Update(float hora_actual){

	this->propulsion->sprite.setPosition(this->sprite.getPosition());
    this->propulsion->sprite.setOrigin(this->sprite.getOrigin().x +35, this->sprite.getOrigin().y-22 );
    this->propulsion->sprite.setRotation(this->sprite.getRotation());
    this->actualizarVelocidad(hora_actual);
	this->actualizarPosicion(hora_actual);
}
void Nave::rotar(double valor){
	
	this->direccion=(this->direccion%360) + valor;
	
	if(this->direccion <0)
	this->direccion=360;
	
}
void Nave::Draw(sf::RenderWindow& renderWindow){
	
	if(this->aceleracion>0){
	this->propulsion->Draw(renderWindow);
	}
	renderWindow.draw(this->sprite);
}
