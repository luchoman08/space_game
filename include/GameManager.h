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
#include "BarraProgreso.hpp"
class GameManager
{
    public:
		MenuInicial *menuPausa;
		MenuInicial *menuInicial;
		MenuInicial *menuFinal;
		MenuInicial *opciones;
		MenuInicial *cantMeteoros;
		MenuInicial *cantNaves;
		void actualizarBarraVidaPrincipal();
		int estado; //0 si esta normal, -2 si se salio de la app, -1 si la nave perdio las vidas, 3 si esta pausado, 2 si esta en el menu inicial, 4 menu de opciones, 5 cantidad naves, 6 cantidad de meteoros
		int numAsteroides=1;
		int cantNavesEnemigas=1;
		void inicializarNaves(float deltaTime);
		int inicializarNavePrincipal(float deltaTime);
		void moverNaves(float deltaTime); //mueve, elimina y lanza los misiles de las nave enemigas y detecta colisiones con los misiles
		void dibujarNaves();
		double direccionPuntoPunto(sf::Vector2f a, sf::Vector2f b); //retorna el angulo de la direccion qeu deberia seguir a para apuntar a b
        GameManager(sf::RenderWindow & appWindow);
        virtual ~GameManager();
        bool inicializarAsteroides(int cantAsteroides, float deltaTime);
        bool posicionSinChocar(sf::FloatRect elemento);//busca si el elemento  colisiona con alguna nave o meteoro
        bool Initialize(float deltaTime);
        /*eventos necesarios para eliminar los objetos  y reiniciar la partida*/
        void eliminarNaves();
        void eliminarMeteoros();
        void eliminarMisiles();
        void eliminarExplociones();
        void FreeResources();
        void teclasAccion(sf::Event event ,float deltaTime);
        int UpdateGame(float deltaTime,  sf::Event event);
        void DrawGame(float deltaTime);
        void DibujarAsteroides();
        void moverAsteroides(float deltaTime);//mueve los asteroides, los remueve si estan en una misma posicion que otro asteroide
        sf::Vector2f colisionAsteroides();
        void crearMisil(Nave& nave, int duracion, int tipoNaveLanza, double aceleracion, int direccion, sf::Vector2f posicionInicial, float deltaTime);
        void dibujarMisiles();
        void dibujarExplociones(float deltatime);
        void moverMisiles(float deltaTime); //mueve y elimina los misiles
        void colisionMisilMeteoro(float deltaTime);//remueve con explocion los meteoros que ya n
        void moverNave(Nave& nave, float deltaTime);
        void nuevaExplocion(float currentTime, int tipo, sf::Sprite sprite);
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
		void dibujarBarra();//dibuja la barra de vidas de la nave principal
		bool colisionMeteoroMeteoro();//chequea las colisiones entre todos los meteoros
        float deltaTime;
        void inicializarMenuPausa();
        void inicializarMenuInicial();
        void inicializarMenuOpciones();
        void inicializarMenuCantMeteoros();
        void inicializarMenuCantNavesEnemigas();
        sf::Vector2f teletransportarDimencion1(sf::Vector2f poscionActual, int dimencion);//retorna a los objetos a la primera dimencion con su misma direccion
    protected:
    
    private:

		int puntosAsteroide;
		int puntosNaves;//la cantidad de naves exterminadas
		sf::Font font;
		sf::Text text;
		sf::Text text2;
		Nave* navePrincipal;
		GameObject* propulsion;
        sf::RenderWindow & renderWindow;
        std::vector <Meteoro*> meteoritosSprites;
        std::vector <Misil*> misiles;
        std::vector <Nave*> naves;
        sf::Texture backgroundImg;
        sf::Texture proyectilImg;
        sf::Texture proyectilRecargado;
        sf::Texture proyectilEnemigoImg;
        sf::Texture naveEnemigaImg;
        sf::Texture navePrincipalAcelerate;
        sf::Texture navePrincipalImg;
        sf::Sprite backgroundSprite;
        std::vector <ObjetoExplocion*> explociones;
        /*rectangulo que representa la pantalla*/
		sf::FloatRect pantalla;
		BarraProgreso* barraVidaNavePrincipal;
		sf::FloatRect* dimencion2;
		sf::FloatRect* dimencion3;
		sf::FloatRect* dimencion4;
		sf::FloatRect* dimencion5;
		sf::Texture planetoideImg;
		sf::Sprite planetoideSprite;
		
};

#endif // GAMEMANAGER_H
