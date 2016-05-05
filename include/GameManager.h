#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <SFML/Graphics.hpp>

class GameManager
{
    public:

        GameManager(sf::RenderWindow & appWindow);
        virtual ~GameManager();

        bool Initialize();
        void FreeResources();

        void UpdateGame(float deltaTime);
        void DrawGame();

    protected:
    private:

        sf::RenderWindow & renderWindow;

        sf::Texture backgroundImg;
        sf::Sprite backgroundSprite;
};

#endif // GAMEMANAGER_H
