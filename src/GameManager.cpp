#include "GameManager.h"
#include <math.h>
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
void GameManager::colisionMisilMeteoro(){
	int numeroMisiles=misilSprites.size();
	int numeroMeteoros=meteoritosSprites.size();
	for(int m =0; m<numeroMisiles; m++)
	{
		for(int c =0; c<numeroMeteoros; c++)
	{
		if (misilSprites.at(m)->getGlobalBounds().intersects(meteoritosSprites.at(c)->getGlobalBounds())){
			explociones.push_back(meteoritosSprites.at(c));		
		
			meteoritosSprites.erase(meteoritosSprites.begin()+c);
			misilSprites.erase(misilSprites.begin()+m);
			numeroMisiles = misilSprites.size();
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
    tiempoUltimoMisilLanzado+=1000;
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
		renderWindow.draw(*meteoritosSprites.at(i));

	}
}
sf::Vector2f GameManager::colisionAsteroides(){
	
	sf::Vector2f posicionAdecuada;
	return posicionAdecuada;
	
}
//~ sf::Vector2f GameManager::colisionAsteroides()
//~ {
	//~ bool tmp = true;
	//~ int numeroMeteoros=meteoritosSprites.size();
	//~ while(tmp){
	//~ 
		//~ for(int i =0; i<numeroMeteoros; i++)
		//~ {
			//~ if (boundingBox.intersects(otherBox))
		//~ }
	//~ }
//~ }
void GameManager::moverAsteroides()
{	
	int numeroMeteoros=meteoritosSprites.size();
	for(int i =0; i<numeroMeteoros; i++)
	{
	    if(i%3==0)
		meteoritosSprites.at(i)->move(0.3,0.3);
		else
		meteoritosSprites.at(i)->move(0.1,0.1);
		if(i%2==0)
		meteoritosSprites.at(i)->rotate(0.1);
		else
		meteoritosSprites.at(i)->rotate(-0.1);
	}
}

bool GameManager::inicializarAsteroides(int numAsteroides)
{
	
	sf::Sprite* spriteTemporal;
    
	for(int i=0; i< numAsteroides; i++)
	{
		 srand (time(NULL));
		 
		 if(i>0)
		 srand ((int)meteoritosSprites.at(i-1)->getPosition().x * 100 * time(NULL));
		 
	     spriteTemporal = new sf::Sprite();
		 spriteTemporal->setTexture(this->meteoritoImg,true);
		 spriteTemporal->setScale(0.3,0.3);
		 sf::FloatRect boundingBox = spriteTemporal->getGlobalBounds();
		 spriteTemporal->setOrigin(rand() % 600 + (1+100*i), rand() % 400 + (1+100*i));
		 spriteTemporal->setPosition(spriteTemporal->getOrigin());
		 meteoritosSprites.push_back(spriteTemporal);	
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
     
    inicializarAsteroides(5);
    tiempoUltimoMisilLanzado=(float)0;
    backgroundSprite.setTexture(backgroundImg, true);
    navePrincipalSprite.setTexture(navePrincipalImg, true);
    backgroundSprite.setScale(0.5f, 0.5f);
    
    navePrincipalSprite.setScale(0.7f,0.7f);
    navePrincipalSprite.setOrigin(52,45);
	navePrincipalSprite.setPosition(700,520);
    return true;
}

void GameManager::FreeResources()
{

}

void GameManager::UpdateGame(float deltaTime, sf::Event event)
{
moverAsteroides();
moverMisiles();
	
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

    colisionMisilMeteoro();
    renderWindow.draw(backgroundSprite);
    renderWindow.draw(navePrincipalSprite);
    DibujarAsteroides();
    dibujarMisiles();
    renderWindow.display();
}
