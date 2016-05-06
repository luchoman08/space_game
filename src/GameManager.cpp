#include "GameManager.h"
#include <math.h>
#include "Meteoro.hpp"
#include <string>
#include <iostream>
GameManager::GameManager(sf::RenderWindow & appWindow) :
    renderWindow(appWindow)
{
    //ctor
}

GameManager::~GameManager()
{
    //dtor
}
void GameManager::moverMisiles()
{
	int numeroMisiles=misilSprites.size();
	for(int i =0; i<numeroMisiles; i++)
	{
		misilSprites.at(i)->move(3*cos((misilSprites.at(i)->getRotation())*3.14159265/180),
								   3*sin((misilSprites.at(i)->getRotation())*3.14159265/180));

	}
}
bool GameManager::colisionNaveMeteoro()
{
	if(vidas == 0)
	return false;
	int numeroMeteoros=meteoritosSprites.size();
	for(int c =0; c<numeroMeteoros; c++)
	{
		if (navePrincipalSprite.getGlobalBounds().intersects(meteoritosSprites.at(c)->Sprite.getGlobalBounds())){
		vidas--;
		text.setString("Vidas: " + std::to_string(vidas));
		navePrincipalSprite.setPosition(700,520);
		
	}
	
	}
	return true;
}
void GameManager::colisionMisilMeteoro(){
	int numeroMisiles=misilSprites.size();
	int numeroMeteoros=meteoritosSprites.size();
	for(int m =0; m<numeroMisiles; m++)
	{
		for(int c =0; c<numeroMeteoros; c++)
	{
		if (misilSprites.at(m)->getGlobalBounds().intersects(meteoritosSprites.at(c)->Sprite.getGlobalBounds())){
			
		    meteoritosSprites.at(c)->puntos_vida--;
		   
			
			misilSprites.erase(misilSprites.begin()+m);
			numeroMisiles = misilSprites.size();
			if(meteoritosSprites.at(c)->puntos_vida==0){
			meteoritosSprites.erase(meteoritosSprites.begin()+c);
			puntos++;
			
		    }
		    numeroMeteoros=meteoritosSprites.size();
		    c = numeroMeteoros;
			m = numeroMisiles;
		}

	}

	}
}

void GameManager::crearMisil(int direccion, sf::Vector2f posicionInicial, float deltaTime){
	std::cout<<deltaTime<<std::endl;
	if(deltaTime ==0)
	tiempoUltimoMisilLanzado = deltaTime;
	if(tiempoUltimoMisilLanzado + 1000 < deltaTime)
	{
	sf::Sprite* misil = new sf::Sprite();
    misil->setTexture(proyectilImg,true);
    misil->setScale(0.5f, 0.5f);
    misil->setPosition(posicionInicial.x  , posicionInicial.y);
    misil->setRotation(direccion);
    misilSprites.push_back(misil);
    tiempoUltimoMisilLanzado = deltaTime;
	}
}

void GameManager::dibujarMisiles()
{
	int numeroMisiles=misilSprites.size();
	for(int i =0; i<numeroMisiles; i++)
	{
		renderWindow.draw(*misilSprites.at(i));

	}
}
void GameManager::DibujarAsteroides()
{
	int numeroMeteoros=meteoritosSprites.size();
	for(int i =0; i<numeroMeteoros; i++)
	{
		renderWindow.draw(meteoritosSprites.at(i)->Sprite);

	}
}
sf::Vector2f GameManager::colisionAsteroides(){
	
	sf::Vector2f posicionAdecuada;
	return posicionAdecuada;
	
}

void GameManager::moverAsteroides()
{	
	int numeroMeteoros=meteoritosSprites.size();
	for(int i =0; i<numeroMeteoros; i++)
	{
	    if(i%3==0)
		meteoritosSprites.at(i)->Sprite.move(0.3,0.3);
		else
		meteoritosSprites.at(i)->Sprite.move(0.1,0.1);
		if(i%2==0)
		meteoritosSprites.at(i)->Sprite.rotate(0.1);
		else
		meteoritosSprites.at(i)->Sprite.rotate(-0.1);
	}
}

bool GameManager::inicializarAsteroides(int numAsteroides)
{
	
	sf::Sprite* spriteTemporal;
    
	for(int i=0;  numAsteroides > meteoritosSprites.size() ; i++)
	{
		 srand (time(NULL));
		 
		 if(i>0)
		 srand ((int)meteoritosSprites.at(i-1)->Sprite.getPosition().x * 100 * time(NULL));
		 
	     Meteoro* meteoroTemporal = new Meteoro();
		 meteoroTemporal->Sprite.setTexture(this->meteoritoImg,true);
		 meteoroTemporal->Sprite.setScale((double)(rand() % 6 + 3)/10,(double)(rand() % 6 + 3)/10);
		 sf::FloatRect boundingBox = meteoroTemporal->Sprite.getGlobalBounds();
	     meteoroTemporal->Sprite.setOrigin(rand() % 800 + 100, rand() % 600 + 100);
		 meteoroTemporal->Sprite.setPosition(meteoroTemporal->Sprite.getOrigin());
		 meteoritosSprites.push_back(meteoroTemporal);	
	}
}
bool GameManager::Initialize()
{
	if (!proyectilImg.loadFromFile("graphics/Projectile01.png"))
        return false;
	if (!meteoritoImg.loadFromFile("graphics/Asteroid01.png"))
        return false;
    if (!navePrincipalImg.loadFromFile("graphics/Spaceship01.png"))
        return false;
    if (!backgroundImg.loadFromFile("graphics/Background.png"))
        return false;  
    puntos =0; 
    inicializarAsteroides(5);
    tiempoUltimoMisilLanzado=(float)0;
    backgroundSprite.setTexture(backgroundImg, true);
    navePrincipalSprite.setTexture(navePrincipalImg, true);
    backgroundSprite.setScale(0.5f, 0.5f);
    this->vidas = 3;
    navePrincipalSprite.setScale(0.7f,0.7f);
    navePrincipalSprite.setOrigin(52,45);
	navePrincipalSprite.setPosition(700,520);
	if(!font.loadFromFile("fonts/arial.ttf"))
	std::cout<<"holi shit"<<std::endl;
	// Create a text
	text.setFont(font); // font is a sf::Font
    text.setString("Vidas: " + std::to_string(vidas));
	text.setCharacterSize(30);
	text.setStyle(sf::Text::Bold);
	text.setColor(sf::Color::Blue);

    return true;
}

void GameManager::FreeResources()
{

}

void GameManager::UpdateGame(float deltaTime, sf::Event event)
{
moverAsteroides();
moverMisiles();
inicializarAsteroides(5);
colisionNaveMeteoro();
if (event.type == sf::Event::KeyPressed)
{
		teclasAccion(event, deltaTime);        
}
}
void GameManager::teclasAccion(sf::Event event, float deltatime)
{

		/* -1 block mayus
		 * 37 = ctrl
		 * 38 = shift
		 * 71 = flecha_izquierda
		 * 72 = flecha_derecha
		 * 73 = flecha_arriba
		 * 74 = flecha_abajo
		 * */

    if(event.key.code == 73)
    navePrincipalSprite.move(3*cos((navePrincipalSprite.getRotation())*3.14159265/180),3*sin((navePrincipalSprite.getRotation())*3.14159265/180));
	switch(event.key.code){
		case 72: navePrincipalSprite.rotate(7);break;
		case 71: navePrincipalSprite.rotate(-7);break;
		case 37: crearMisil(navePrincipalSprite.getRotation(), navePrincipalSprite.getPosition() , deltatime);break;
		default : break;
	}
}

void GameManager::DrawGame()
{
   if(colisionNaveMeteoro()){
    colisionMisilMeteoro();
    renderWindow.draw(backgroundSprite);
    renderWindow.draw(navePrincipalSprite);
    DibujarAsteroides();
    dibujarMisiles();
    renderWindow.draw(text);
    renderWindow.display();
}
else{
backgroundImg.loadFromFile("graphics/game_over1.bmp");
backgroundSprite.setPosition(sf::Vector2f(300, 300));
renderWindow.draw(backgroundSprite);
text.setPosition(sf::Vector2f(0, 0));
text.setString("Total puntos: " + std::to_string(puntos));
renderWindow.draw(text);
renderWindow.display();


}

}
