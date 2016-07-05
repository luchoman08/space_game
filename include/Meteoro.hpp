#ifndef METEORO_H
#define METEORO_H
#include <vector>
#include <SFML/Graphics.hpp>
#include "GameObject.hpp"
#include <time.h>


class Meteoro : public GameObject{
	
	public:
	Meteoro();
	~Meteoro();
	int tamanio;
	int puntos_vida;
	clock_t horaInicioExplocion = 0;
};

#endif

