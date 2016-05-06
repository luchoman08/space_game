#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <vector>
#include <SFML/Graphics.hpp>
#include <time.h>
#include "../src/Meteoro.hpp"
class GameManager
{
    public:

        GameManager(sf::RenderWindow & appWindow);
        virtual ~GameManager();
        bool inicializarAsteroides(int cantAsteroides);
        bool Initialize();
        void FreeResources();
        void teclasAccion(sf::Event event ,float deltaTime);
        void UpdateGame(float deltaTime,  sf::Event event);
        void DrawGame();
        void DibujarAsteroides();
        void moverAsteroides();
        sf::Vector2f colisionAsteroides();
        void crearMisil(int direccion, sf::Vector2f posicionInicial, float deltaTime);
        void dibujarMisiles();
        void moverMisiles();
        void colisionMisilMeteoro();
        bool colisionNaveMeteoro();
    protected:
    private:
		int vidas ;
		int puntos;
		sf::Font font;
		sf::Text text;

        sf::RenderWindow & renderWindow;
        std::vector <Meteoro*> meteoritosSprites;
        std::vector <sf::Sprite*> explociones;
        std::vector <sf::Sprite*> misilSprites;
        sf::Texture backgroundImg;
        float tiempoUltimoMisilLanzado;
        sf::Texture meteoritoImg;
        sf::Texture proyectilImg;
        sf::Texture navePrincipalImg;
        sf::Sprite backgroundSprite;
        sf::Sprite navePrincipalSprite;
};

#endif // GAMEMANAGER_H
