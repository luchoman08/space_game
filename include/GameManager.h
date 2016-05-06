#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <vector>
#include <SFML/Graphics.hpp>
#include <time.h>
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
    protected:
    private:

        sf::RenderWindow & renderWindow;
        std::vector <sf::Sprite*> meteoritosSprites;
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
