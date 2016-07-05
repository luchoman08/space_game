#include "Misil.hpp"
Misil::Misil(){
	
	this->hora_creacion=clock();
	
};

Misil::Misil(Nave* naveCreadora, int tipo, float duracion, double aceleracion, float hora_creacion){
	this-> naveCreadora = naveCreadora;
	this->duracion = duracion;
	this->hora_creacion=hora_creacion;
	this->aceleracion=aceleracion; 
	this->tipo = tipo;
	};


