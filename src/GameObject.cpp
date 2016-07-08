#include "GameObject.hpp"
#include <iostream>
void GameObject::actualizarPeso(){
	
	this->peso=this->sprite.getScale().x * this->ancho * this->sprite.getScale().y * this->alto;
};

int GameObject::Draw(sf::RenderWindow& renderWindow){
	
	renderWindow.draw(this->sprite);
	
}

void GameObject::mover(int cantPixeles, int direccion){
	this->sprite.move(cantPixeles * cos((direccion*M_PI)/180),
					  cantPixeles * sin((direccion*M_PI)/180)); // newPosition, oldPosition, velocity como vectores
}

void GameObject::recibirImpulso(float pesoObjeto, float velocidadObjeto){
	this->velocidad+=0.1*((this->peso/pesoObjeto)*velocidadObjeto);
}
int GameObject::Update(float hora_actual){
	actualizarVelocidad(hora_actual);
	actualizarPosicion(hora_actual);
}

void GameObject::actualizarVelocidad(float hora_actual){
	this->velocidad = this->velocidad +  (this->aceleracion * (hora_actual - this->hora_creacion));

}
void GameObject::actualizarPosicion(float hora_actual){

	this->sprite.move(this->velocidad * cos((this->direccion*M_PI)/180),
					  this->velocidad * sin((this->direccion*M_PI)/180)); // newPosition, oldPosition, velocity como vectores
}

