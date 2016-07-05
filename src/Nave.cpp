#include "Nave.hpp"

Nave::Nave(){
	this->aceleracion=0;
	this->direccion=180;
	this->peso=0;
	};
Nave::Nave(int cantVidas,int velocidadRecargaMetralla){
	this->aceleracion=0;
	this->velocidadRecargaMetralla=velocidadRecargaMetralla;
	this->vidas = cantVidas;
	this->direccion=180;
	this->peso=0;
	};
Nave::~Nave(){};

void Nave::rotar(double valor){
	
	this->direccion=(this->direccion%360) + valor;
	
	if(this->direccion <0)
	this->direccion=360;
	
}

