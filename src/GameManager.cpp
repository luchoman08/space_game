#include "GameManager.h"

GameManager::GameManager(sf::RenderWindow & appWindow) :
    renderWindow(appWindow)
{
    //ctor
}

GameManager::~GameManager()
{
    //dtor
}

bool GameManager::Initialize()
{
    if (!backgroundImg.loadFromFile("graphics/Background.jpg"))
        return false;

    backgroundSprite.setTexture(backgroundImg, true);
    backgroundSprite.setScale(0.5f, 0.5f);

    return true;
}

void GameManager::FreeResources()
{

}

void GameManager::UpdateGame(float deltaTime)
{

}

void GameManager::DrawGame()
{
    renderWindow.draw(backgroundSprite);
}
