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
	std::cout<<(hora_actual - this->hora_creacion)<<std::endl;
	this->sprite.move(this->velocidad * cos((this->direccion*M_PI)/180),
					  this->velocidad * sin((this->direccion*M_PI)/180)); // newPosition, oldPosition, velocity como vectores
}
//~ void GameObject::actualizarPosicion(float hora_actual){
	//~ this->sprite.move(this->velocidad * ((hora_actual - this->hora_creacion)/1000) * cos(this->direccion),
					  //~ this->velocidad * ((hora_actual - this->hora_creacion)/1000) * sin(this->direccion)); // newPosition, oldPosition, velocity como vectores
//~ }


//~ void GameObject::actualizarPosicion(float hora_actual){
	//~ this->sprite.setPosition(this->posicionInicial.x + ((this->velocidad * (hora_actual - hora_creacion))*(double)fabs(cos((this->direccion)*M_PI)/180)) ,
					         //~ this->posicionInicial.y + ((this->velocidad * (hora_actual - hora_creacion))*(double)fabs(sin((this->direccion)*M_PI)/180))); // newPosition, oldPosition, velocity como vectores
					         
					         
					         
					        //~ std::cout << "resultado x: " << this->posicionInicial.x + ((this->velocidad * (hora_actual - hora_creacion))*(double)fabs(cos((this->direccion)*M_PI)/180))<<std::endl;
					        //~ std::cout << "resultado x: " << this->posicionInicial.x + ((this->velocidad * (hora_actual - hora_creacion))*(double)fabs(sin((this->direccion)*M_PI)/180))<<std::endl;
					       //~ //  std::cout << "resultado fabs: " <<  this->posicionInicial.y + (float)((this->velocidad * (hora_actual - hora_creacion))*(double)fabs(sin((this->sprite.getRotation())*M_PI)/180)) <<std::endl;
//~ }
