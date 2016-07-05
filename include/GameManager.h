#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <vector>
#include <SFML/Graphics.hpp>
#include <time.h>
#include "Meteoro.hpp"
#include "Nave.hpp"
#include "Misil.hpp"
#include "ObjetoExplocion.hpp"
#include "MenuInicial.hpp"
class GameManager
{
    public:
		MenuInicial *menuInicial;
		int estado; //0 si esta normal, -1 si la nave perdio las vidas, 2 si esta pausado, 3 si esta en el menu inicial
		int numAsteroides=3;
		int cantNavesEnemigas;
		void inicializarNaves();
		int inicializarNavePrincipal();
		void moverNaves(float deltaTime); //mueve, elimina y lanza los misiles de las nave enemigas y detecta colisiones con los misiles
		void dibujarNaves();
		double direccionPuntoPunto(sf::Vector2f a, sf::Vector2f b); //retorna el angulo de la direccion qeu deberia seguir a para apuntar a b
        GameManager(sf::RenderWindow & appWindow);
        virtual ~GameManager();
        bool inicializarAsteroides(int cantAsteroides);
        bool posicionSinChocar(sf::FloatRect elemento);//busca si el elemento  colisiona con alguna nave o meteoro
        bool Initialize();
        void FreeResources();
        void teclasAccion(sf::Event event ,float deltaTime);
        void UpdateGame(float deltaTime,  sf::Event event);
        void DrawGame(float deltaTime);
        void DibujarAsteroides();
        void moverAsteroides();//mueve los asteroides, los remueve si estan en una misma posicion que otro asteroide
        sf::Vector2f colisionAsteroides();
        void crearMisil(Nave& nave, int duracion, int tipoNaveLanza, double aceleracion, int direccion, sf::Vector2f posicionInicial, float deltaTime);
        void dibujarMisiles();
        void dibujarExplociones(float deltatime);
        void moverMisiles(); //mueve y elimina los misiles
        void colisionMisilMeteoro(float deltaTime);//remueve con explocion los meteoros que ya n
        void moverNave(Nave& nave);
        bool colisionNaveMeteoro(float deltaTime, Nave& nave);
        bool colisionNaveNave(float deltaTime);
        /* este metodo devuelve un entero si el meteoro se sale de la pantalla
         * en caso de que aun este en la pantalla retorna 0
         * si ha exedido el limite superior retorna 1
         * si ha exedido el limite derecho retorna 2
         * si ha exedido el liminte inferior retorna 3
         * si ha exedido el limite izquierdo retorna 4*/
        int  limitePantalla(sf::FloatRect rectangulo); //retorna la dimencion en la que se encuentra
		void colisionMisilesNave(float deltaTime, Nave& nave);
		bool colisionMeteoroMeteoro();//chequea las colisiones entre todos los meteoros
        float deltaTime;
        sf::Vector2f teletransportarDimencion1(sf::Vector2f poscionActual, int dimencion);//retorna a los objetos a la primera dimencion con su misma direccion
    protected:
    
    private:

		int puntosAsteroide;
		sf::Font font;
		sf::Text text;
		Nave* navePrincipal;
        sf::RenderWindow & renderWindow;
        std::vector <Meteoro*> meteoritosSprites;
        std::vector <Misil*> misiles;
        std::vector <Nave*> naves;
        sf::Texture backgroundImg;
        sf::Texture proyectilImg;
        sf::Texture proyectilEnemigoImg;
        sf::Texture naveEnemigaImg;
        sf::Sprite backgroundSprite;
        std::vector <ObjetoExplocion*> explociones;
        /*rectangulo que representa la pantalla*/
		sf::FloatRect pantalla;
		sf::FloatRect* dimencion2;
		sf::FloatRect* dimencion3;
		sf::FloatRect* dimencion4;
		sf::FloatRect* dimencion5;
		sf::Texture planetoideImg;
		sf::Sprite planetoideSprite;
};

#endif // GAMEMANAGER_H
