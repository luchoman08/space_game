#ifndef Nave_hpp
#define Nave_hpp
#include <SFML/Graphics.hpp>
#include "GameObject.hpp"
class Nave: public GameObject{
	
	public:
	Nave();
	Nave(int cantVidas, int velocidadRecargaMetralla);
	~Nave();
	int vidas;
	float tiempoUltimoMisilLanzado;
	void rotar(double valor);
	int tipo;// 1 si es la principal, 2 si es nave enemiga
	int velocidadRecargaMetralla; //tiempo en milisegundos que tarda para cargar la ametralladora
	private:
	
};

#endif
