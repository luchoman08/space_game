#ifndef MISIL_HPP
#define MISIL_HPP
#include <SFML/Graphics.hpp>
#include "GameObject.hpp"
#include "time.h"
#include "Nave.hpp"
class Misil:public GameObject{
	
	public:
	Misil();
	Misil(Nave* naveCreadora, int tipo, float duracion, double velocidad, float hora_creacion);
	float hora_creacion;
	float duracion; //tiempo en milisegundos que durara el misil dando vueltas	
	int tipo;//1 si es de la nave principal, 2 si es de la nave enemiga
	Nave* naveCreadora;
	private:
		
};
#endif
