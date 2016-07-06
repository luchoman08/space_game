#include "../include/GameManager.h"
#include <math.h>
#include "Meteoro.hpp"
#include <string>
#include <iostream>
#include <time.h>
#include <unistd.h>

GameManager::GameManager(sf::RenderWindow & appWindow) :
    renderWindow(appWindow)
{
			
	this->estado=2;
}

GameManager::~GameManager()
{
    //dtor
}

void GameManager::actualizarBarraVidaPrincipal(){
	
}

void GameManager::moverMisiles(float deltaTime)
{
	int numeroMisiles=misiles.size();
	for(int i =0; i < numeroMisiles; i++)
	{
	int dimencion = limitePantalla(misiles.at(i)->sprite.getGlobalBounds());
	if(dimencion!=1)
	{
		misiles.at(i)->sprite.setPosition(this->teletransportarDimencion1(misiles.at(i)->sprite.getPosition(), dimencion));
	}
	/*
	 * 	misiles.at(i)->sprite.move(misiles.at(i)->aceleracion* cos((misiles.at(i)->sprite.getRotation())*3.14159265/180),
								  misiles.at(i)->aceleracion*sin((misiles.at(i)->sprite.getRotation())*3.14159265/180));
	 * */
		misiles.at(i)->Update(deltaTime);
	
	if(misiles.at(i)->duracion < (this->deltaTime - misiles.at(i)->hora_creacion)){
		misiles.erase(misiles.begin()+i);
		numeroMisiles=misiles.size();
	}
}
}

void GameManager::moverNaves(float deltaTime){
	
	
	
	int cantNavesEnemigas = naves.size();
	for(int i =0; i < this->naves.size(); i++){
		 colisionMisilesNave(deltaTime, *naves.at(i));
		 if(naves.at(i)->vidas<0)
		 {
			 naves.erase(naves.begin()+i);
			 break;
		 }
		 else{
			 if(1==limitePantalla(this->navePrincipal->sprite.getGlobalBounds())&& 1 == limitePantalla(naves.at(i)->sprite.getGlobalBounds())){
		 naves.at(i)->sprite.setRotation(direccionPuntoPunto(navePrincipal->sprite.getPosition(), naves.at(i)->sprite.getPosition()));
		}
		 moverNave(*naves.at(i), deltaTime);
		 colisionNaveMeteoro(deltaTime, *naves.at(i));
		 crearMisil(*(naves.at(i)), 5000, 2, 0.5, naves.at(i)->sprite.getRotation(), naves.at(i)->sprite.getPosition(), deltaTime);
		}
	}
	
	
}
double GameManager::direccionPuntoPunto(sf::Vector2f a, sf::Vector2f b){
	return (atan(
		 ((double) a.y - (double)b.y)
						/
					(a.x - (double)b.x)))*180/M_PI;
}
void GameManager::inicializarNaves(float deltaTime){
	
	
	
	/*inicializar resto de naves*/
	for(int i = naves.size(); i < this->cantNavesEnemigas; i++){
		 if(i>0)
		 srand ((int)naves.at(i-1)->sprite.getPosition().x * 100 * time(NULL));
		 
		Nave* tmp = new Nave(3,3000);
		tmp->aceleracion=0;
		tmp->ancho=41;
		tmp->alto=48;
		tmp->actualizarPeso();
		tmp->hora_creacion=deltaTime;
		tmp->velocidad=0.5;
		tmp->tipo = 2;
		tmp->direccion=rand() % 360 - 0 ;
		tmp->imagen=naveEnemigaImg;
		tmp->sprite.setTexture(tmp->imagen);
		do{
		tmp->sprite.setPosition((rand() % 900) + 0, (rand() % 600) + 0);
	}while(!posicionSinChocar(tmp->sprite.getGlobalBounds()));
	    tmp->posicionInicial=tmp->sprite.getPosition();
		tmp->sprite.setOrigin(sf::Vector2f(22,21));
		 tmp->sprite.setRotation(direccionPuntoPunto(navePrincipal->sprite.getPosition(), tmp->sprite.getPosition()));
		
		naves.push_back(tmp);
	}
	
}

void GameManager::dibujarNaves(){
	
	int size = naves.size();
	for(int i =0; i < size ; i++){
	naves.at(i)->Draw(this->renderWindow);
	}
	
}

bool GameManager::posicionSinChocar(sf::FloatRect elemento)
{
		bool posicionValida = true;
		for(int i =0; i < this->meteoritosSprites.size(); i++)
		{
			if(elemento.intersects(meteoritosSprites.at(i)->sprite.getGlobalBounds()))
			posicionValida=false;
		}
		for(int i =0; i < naves.size(); i++)
		{
			if(elemento.intersects(naves.at(i)->sprite.getGlobalBounds()))
			posicionValida=false;
		}
		if(elemento.intersects(navePrincipal->sprite.getGlobalBounds()))
		posicionValida = false;
		
		return posicionValida;
}
bool GameManager::colisionMeteoroMeteoro(){
	for(int m1 =0; m1<meteoritosSprites.size(); m1++)
	{
		for(int m2 =m1+1; m2<meteoritosSprites.size(); m2++)
		{
			if (meteoritosSprites.at(m1)!=meteoritosSprites.at(m2) && meteoritosSprites.at(m1)->sprite.getGlobalBounds().intersects(meteoritosSprites.at(m2)->sprite.getGlobalBounds())){
				meteoritosSprites.at(m1)->mover(5,meteoritosSprites.at(m2)->direccion);
				meteoritosSprites.at(m2)->mover(5,meteoritosSprites.at(m1)->direccion);
				meteoritosSprites.at(m1)->direccion=meteoritosSprites.at(m2)->direccion;
				meteoritosSprites.at(m1)->puntos_vida-=0.5;
				meteoritosSprites.at(m2)->direccion-=180;
				
				Meteoro tmp = *meteoritosSprites.at(m1);
				//meteoritosSprites.at(m1)->recibirImpulso(meteoritosSprites.at(m2)->peso, meteoritosSprites.at(m2)->velocidad);
				//meteoritosSprites.at(m2)->recibirImpulso(tmp.peso, tmp.velocidad);

			}
		}
	}	
}

void GameManager::nuevaExplocion(float deltaTime, int tipo, sf::Sprite sprite){
		ObjetoExplocion* objtmp = new ObjetoExplocion(deltaTime, tipo, sprite);
		explociones.push_back(objtmp);
}

bool GameManager::colisionNaveNave(float deltaTime)
{
	
	int numeroMeteoros=meteoritosSprites.size();
	for(int n1 =0; n1<naves.size(); n1++)
	{
		if(navePrincipal->sprite.getGlobalBounds().intersects(naves.at(n1)->sprite.getGlobalBounds())){
		naves.at(n1)->aceleracion=0;
		navePrincipal->vidas-=1;	
		nuevaExplocion(deltaTime, 0, naves.at(n1)->sprite);
		this->puntosNaves++;
		naves.erase(naves.begin()+n1);
		return false;
		
		}
		else{
			for(int n2 =n1+1; n2<naves.size(); n2++)
			{		
				if (naves.at(n1)->sprite.getGlobalBounds().intersects(naves.at(n2)->sprite.getGlobalBounds())){
				naves.at(n1)->direccion-=180;
				naves.at(n2)->direccion-=180;
				
				}
			}
		}

	
	}
	return true;
}

bool GameManager::colisionNaveMeteoro(float deltaTime, Nave& nave)
{
	if(nave.vidas == 0 && this->estado == 0){
	nuevaExplocion(deltaTime, 0, nave.sprite);
	nave.vidas=-1;
	nave.aceleracion=0;
	if(&nave == navePrincipal){
	this->estado = -1;
	}
	return false;
	}
	int numeroMeteoros=meteoritosSprites.size();
	for(int c =0; c<numeroMeteoros; c++)
	{
		if (nave.sprite.getGlobalBounds().intersects(meteoritosSprites.at(c)->sprite.getGlobalBounds())){
		nave.mover(10, meteoritosSprites.at(c)->direccion);	
		double tmp=meteoritosSprites.at(c)->direccion;
		meteoritosSprites.at(c)->direccion=nave.direccion;
		//nave.velocidad=meteoritosSprites.at(c)->velocidad;
		nave.recibirImpulso(meteoritosSprites.at(c)->peso, meteoritosSprites.at(c)->velocidad);
		nave.direccion-=180;
		
		/*nave.sprite.move(nave.aceleracion*10*cos(nave.direccion*3.14159265/180),nave.aceleracion*10*sin(nave.direccion*3.14159265/180));
		meteoritosSprites.at(c)->sprite.move(meteoritosSprites.at(c)->aceleracion*cos((meteoritosSprites.at(c)->direccion)*3.14159265/180),
		meteoritosSprites.at(c)->aceleracion*sin((meteoritosSprites.at(c)->direccion)*3.14159265/180));*/
		nave.vidas--;
		meteoritosSprites.at(c)->puntos_vida-=0.3;
		if(meteoritosSprites.at(c)->puntos_vida<=0){
			nuevaExplocion(deltaTime, 1, meteoritosSprites.at(c)->sprite);
			this->puntosAsteroide++;
		}
		if(&nave==this->navePrincipal)
		text.setString("Vidas: " + std::to_string(nave.vidas));
	
		
	}
	
	}
	return true;
}

void GameManager::colisionMisilesNave(float deltaTime, Nave& nave){
	int numeroMisiles=misiles.size();
	for(int m =0; m<numeroMisiles; m++)
	{
		if (misiles.at(m)->sprite.getGlobalBounds().intersects(nave.sprite.getGlobalBounds())
		&& (misiles.at(m)->tipo != nave.tipo))
		{			
		    nave.vidas--;
		    
		    if(&nave == this->navePrincipal){
		    text.setString("Vidas: " + std::to_string(navePrincipal->vidas));
			}
		    
		    sf::Vector2f temporal = nave.sprite.getPosition();
		    nave.direccion=misiles.at(m)->sprite.getRotation();		
		    nave.sprite.setPosition(temporal);	
			misiles.erase(misiles.begin()+m);
			numeroMisiles = misiles.size();
			if(nave.vidas<=0){
			
				if(&nave!=navePrincipal){
				nuevaExplocion(deltaTime, 0 , nave.sprite);	
				this->puntosNaves++;
				}
				else{
				nuevaExplocion(deltaTime, 1 , nave.sprite);	
				}
		    }
			m = numeroMisiles;
		}

	}

	}


void GameManager::colisionMisilMeteoro(float deltaTime){
	int numeroMisiles=misiles.size();
	int numeroMeteoros=meteoritosSprites.size();
	for(int m =0; m<numeroMisiles; m++)
	{
		for(int c =0; c<numeroMeteoros; c++)
	{
		if (misiles.at(m)->sprite.getGlobalBounds().intersects(meteoritosSprites.at(c)->sprite.getGlobalBounds())){			
		    meteoritosSprites.at(c)->puntos_vida--;
		   

			
			
			if(meteoritosSprites.at(c)->puntos_vida<=0){
			nuevaExplocion(deltaTime, 1, meteoritosSprites.at(c)->sprite);
			meteoritosSprites.erase(meteoritosSprites.begin()+c);	
			
			if(misiles.at(m)->tipo==1)		
			puntosAsteroide++;
						
		    }
		    else{
			sf::Vector2f temporal = meteoritosSprites.at(c)->sprite.getPosition();
		    meteoritosSprites.at(c)->direccion=misiles.at(m)->sprite.getRotation();		
		    meteoritosSprites.at(c)->sprite.setPosition(temporal);	
			}
			misiles.erase(misiles.begin()+m);
			numeroMisiles = misiles.size();
		    numeroMeteoros=meteoritosSprites.size();
		    c = numeroMeteoros;
			m = numeroMisiles;
		}

	}

	}
}
void GameManager::eliminarNaves(){
	for (int i =0; i<naves.size(); i++)
	{
		this->naves.erase(naves.begin()+i);
	}
}
void GameManager::eliminarMeteoros(){
	for (int i =0; i<meteoritosSprites.size(); i++)
	{
		this->meteoritosSprites.erase(meteoritosSprites.begin()+i);
	}
}
void GameManager::eliminarMisiles(){
	for (int i =0; i<misiles.size(); i++)
	{
		this->misiles.erase(misiles.begin()+i);
	}
}
void GameManager::eliminarExplociones(){
	for (int i =0; i<explociones.size(); i++)
	{
		this->explociones.erase(explociones.begin()+i);
	}
}
void GameManager::crearMisil(Nave& nave, int duracion, int tipoNaveLanza, double velocidad, int direccion, sf::Vector2f posicionInicial, float deltaTime){
	if(deltaTime ==0)
	nave.tiempoUltimoMisilLanzado = deltaTime;
	if(nave.tiempoUltimoMisilLanzado + nave.velocidadRecargaMetralla < deltaTime)
	{
	Misil* misil = new Misil(navePrincipal, tipoNaveLanza, duracion, velocidad+2, this->deltaTime); //arranca con minimo 2 de aceleracion, si ya se ha acelerado 
	misil->imagen=proyectilImg;
	switch(tipoNaveLanza){
		case 1: misil->sprite.setTexture(proyectilImg,true);break;
		case 2: misil->sprite.setTexture(proyectilEnemigoImg,true);break;
	}
	misil->hora_creacion = deltaTime;
    misil->sprite.setScale(0.5f, 0.5f);
    misil->sprite.setPosition(posicionInicial.x  , posicionInicial.y);
    misil->posicionInicial=sf::Vector2f(posicionInicial.x  , posicionInicial.y);
    misil->sprite.setRotation(direccion);
    misil->direccion=direccion;
    misiles.push_back(misil);
    nave.tiempoUltimoMisilLanzado = deltaTime;
	}
}
void GameManager::dibujarExplociones(float deltatime){
	
	int numeroExplociones=explociones.size();
	for(int i =0; i<numeroExplociones; i++)
	{
		
		auto f = explociones.at(i)->actualizarImagen(deltatime);
		if(!f){
		explociones.erase(explociones.begin()+i);
		numeroExplociones=explociones.size();
		}
		else
		renderWindow.draw(explociones.at(i)->sprite);

	}
}
void GameManager::dibujarMisiles()
{
	int numeroMisiles=misiles.size();
	for(int i =0; i<numeroMisiles; i++)
	{
		misiles.at(i)->Draw(this->renderWindow);

	}
}
void GameManager::DibujarAsteroides()
{
	int numeroMeteoros=meteoritosSprites.size();
	for(int i =0; i<numeroMeteoros; i++)
	{
		meteoritosSprites.at(i)->Draw(this->renderWindow);

	}
}
sf::Vector2f GameManager::colisionAsteroides(){
	
	sf::Vector2f posicionAdecuada;
	return posicionAdecuada;
	
}
int GameManager::limitePantalla(sf::FloatRect rectangulo){

	if(rectangulo.intersects(pantalla))
	{
		return 1;		
	}
	if(rectangulo.intersects(*dimencion2))
	{
		return 2;		
	}
	if(rectangulo.intersects(*dimencion3))
	{
		return 3;		
	}
	if(rectangulo.intersects(*dimencion4))
	{
		return 4;		
	}
	if(rectangulo.intersects(*dimencion5))
	{
		return 5;		
	}
	
}

sf::Vector2f GameManager::teletransportarDimencion1(sf::Vector2f posicionActual, int dimencion){
	
		if(dimencion!=1){
			switch(dimencion){
			case 2: 	return sf::Vector2f(sf::Vector2f(posicionActual.x, 
														 posicionActual.y+ 800));
			case 3: 	return sf::Vector2f(sf::Vector2f(posicionActual.x - 1000, 
											posicionActual.y));
			case 4: 	return sf::Vector2f(sf::Vector2f(posicionActual.x, 
											posicionActual.y-800));
			case 5: 	return sf::Vector2f(sf::Vector2f(posicionActual.x+1000, 
														posicionActual.y));	
			default:
			srand (time(NULL));
			return sf::Vector2f(rand() % 1100 + 900,rand() % -300 + -100);																																									
			}
		}
	
}
void GameManager::moverAsteroides(float deltaTime)
{	
	
	int numeroMeteoros=meteoritosSprites.size();
	for(int i =0; i<numeroMeteoros; i++)
	{
		
		int dimencion = this->limitePantalla(meteoritosSprites.at(i)->sprite.getGlobalBounds());
		
		if(dimencion!=1){
			meteoritosSprites.at(i)->sprite.setPosition(teletransportarDimencion1(meteoritosSprites.at(i)->sprite.getPosition(),dimencion));					
		}
		
		meteoritosSprites.at(i)->Update(deltaTime);						   
		//eliminar asteroides
		  if(meteoritosSprites.at(i)->puntos_vida<=0){	
		meteoritosSprites.erase(meteoritosSprites.begin()+i);
		numeroMeteoros=meteoritosSprites.size();
		
		}
	}
}

bool GameManager::inicializarAsteroides(int numAsteroides, float deltaTime)
{
	
	sf::Sprite* spriteTemporal;
    
	for(int i=0;  numAsteroides > meteoritosSprites.size() ; i++)
	{
		srand (time(NULL));
		 
		if(i>0)
		srand ((int)meteoritosSprites.at(i-1)->sprite.getPosition().x * 100 * time(NULL));
		 
	    Meteoro* meteoroTemporal = new Meteoro();
	    meteoroTemporal->aceleracion=0;
	    meteoroTemporal->velocidad=1;
	    meteoroTemporal->hora_creacion=deltaTime;
	    meteoroTemporal->imagen.loadFromFile("graphics/Asteroid01.png");
		meteoroTemporal->sprite.setTexture(meteoroTemporal->imagen,true);
		auto tmp = (double)(rand() % 6 + 3)/10;
		meteoroTemporal->sprite.setScale(tmp,tmp);
	    meteoroTemporal->actualizarPeso();
		sf::FloatRect boundingBox = meteoroTemporal->sprite.getGlobalBounds();
	    meteoroTemporal->sprite.setOrigin(meteoroTemporal->sprite.getScale().x*83,meteoroTemporal->sprite.getScale().y*80);
	    do{
		meteoroTemporal->sprite.setPosition(sf::Vector2f( (rand()%800)+1 , (rand()%800)+1 ));
		meteoroTemporal->posicionInicial= meteoroTemporal->sprite.getPosition();
		}
		while(!posicionSinChocar(meteoroTemporal->sprite.getGlobalBounds()));
		sf::Vector2f puntoEnPantalla = sf::Vector2f(400, 300);
		auto direccionFinal = (atan(
		meteoroTemporal->sprite.getPosition().y - puntoEnPantalla.x
		 /
		meteoroTemporal->sprite.getPosition().x - puntoEnPantalla.y)*180)/M_PI;
		meteoroTemporal->sprite.setRotation(direccionFinal);
		meteoroTemporal->direccion = direccionFinal;
		meteoroTemporal->ancho=167;
		meteoroTemporal->alto=160;
		meteoroTemporal->actualizarPeso();
	
		meteoritosSprites.push_back(meteoroTemporal);	
	}
}
int GameManager::inicializarNavePrincipal(float deltaTime){
	/*inicializar nave principal*/
	navePrincipal->hora_creacion= deltaTime;
    navePrincipal->tiempoUltimoMisilLanzado=(float)0;
    navePrincipal->tipo=1;
    navePrincipal->aceleracion=0;
    navePrincipal->velocidad=0;
    navePrincipal->sprite.setTexture(navePrincipal->imagen, true);
    navePrincipal->vidas = 48;
    navePrincipal->sprite.setScale(0.7f,0.7f);
    navePrincipal->alto=89;
    navePrincipal->ancho=114;
    navePrincipal->actualizarPeso();
    navePrincipal->velocidadRecargaMetralla=1000;
    navePrincipal->sprite.setOrigin(52,45);
	navePrincipal->sprite.setPosition(700,500);
	navePrincipal->posicionInicial=sf::Vector2f(700,500);
}
void GameManager::inicializarMenuPausa(){
	this->menuPausa=new MenuInicial((float)800,(float)600);
	this->menuPausa->adicionarTexto("Continuar");
	this->menuPausa->adicionarTexto("Reiniciar Partida");
	this->menuPausa->adicionarTexto("Terminar Partida");
	this->menuPausa->adicionarTexto("Salir");
	this->menuPausa->inicializar();
}
void GameManager::inicializarMenuInicial(){
	this->menuInicial=new MenuInicial((float)800,(float)600);
	this->menuInicial->adicionarTexto("Jugar");
	this->menuInicial->adicionarTexto("Opciones");
	this->menuInicial->adicionarTexto("Salir");
	this->menuInicial->inicializar();
}
bool GameManager::Initialize(float deltaTime)
{
	
	this->navePrincipal= new Nave();
	inicializarMenuPausa();
	inicializarMenuInicial();
	
	this->puntosNaves=0;
	this->cantNavesEnemigas=2;
	this->numAsteroides=5;
	this->pantalla.top=0;
	this->pantalla.left=0;
	this->pantalla.width=800;
	this->pantalla.height=600;
	this->dimencion2 = new sf::FloatRect(0,-600,800,600);
	this->dimencion3 = new sf::FloatRect(800,0,800,600);
	this->dimencion4 = new sf::FloatRect(0,600,800,600);
	this->dimencion5 = new sf::FloatRect(-800,0,800,600);
	if (!proyectilEnemigoImg.loadFromFile("graphics/Projectile04.png"))
        return false;
	if (!proyectilImg.loadFromFile("graphics/Projectile05.png"))
        return false;
    if (!navePrincipal->imagen.loadFromFile("graphics/Spaceship01.png"))
        return false;
    if (!backgroundImg.loadFromFile("graphics/Background.png"))
        return false;
    if (!planetoideImg.loadFromFile("graphics/Planetoid.png"))
        return false;    
    if (!naveEnemigaImg.loadFromFile("graphics/Spaceship03.png"))
        return false;   
    puntosAsteroide = 0; 
    puntosNaves = 0;
    planetoideSprite.setTexture(planetoideImg, true);
    planetoideSprite.setPosition(-100, 200);
    backgroundSprite.setTexture(backgroundImg, true);
    inicializarAsteroides(this->numAsteroides, deltaTime);
    inicializarNavePrincipal(deltaTime);
	backgroundSprite.setScale(0.5f, 0.5f);
	
	
	if(!font.loadFromFile("fonts/arial.ttf"))
	return false;
	// Create a text
	text.setFont(font); // font is a sf::Font
	text.setCharacterSize(30);
	text.setStyle(sf::Text::Bold);
	text.setColor(sf::Color::Red);
	text2.setFont(font); // font is a sf::Font
	text2.setCharacterSize(30);
	text2.setStyle(sf::Text::Bold);
	text2.setColor(sf::Color::Red);
	 inicializarNaves(deltaTime);
	 this->barraVidaNavePrincipal=new BarraProgreso(sf::Color::Blue,sf::Color(255,69,0),sf::Color::Red, sf::Color::Red, sf::Vector2f(100, 20), sf::Vector2f(20, 20), this->navePrincipal->vidas);
	/*iniciamos el rectangulo pantalla*/
	
    return true;
}

void GameManager::FreeResources()
{

}

void GameManager::UpdateGame(float deltaTime, sf::Event event)
{
	
	
if(this->estado==0	){
this->deltaTime=deltaTime;
moverAsteroides(deltaTime);
moverMisiles(deltaTime);
moverNave(*(this->navePrincipal), deltaTime);
moverNaves(deltaTime);
inicializarAsteroides(this->numAsteroides, deltaTime);
inicializarNaves(deltaTime);
colisionMisilesNave(deltaTime, *navePrincipal);
colisionNaveMeteoro(deltaTime, *navePrincipal);
colisionMisilMeteoro(deltaTime);
colisionMeteoroMeteoro();
colisionNaveNave(deltaTime);
this->barraVidaNavePrincipal->update(this->navePrincipal->vidas);
}



if (event.type == sf::Event::KeyPressed)
{
		teclasAccion(event, deltaTime);        
}
}

void GameManager::moverNave(Nave& nave, float deltaTime)
{
	int dimencion = limitePantalla(nave.sprite.getGlobalBounds());
	if(dimencion!=1)
	{
		nave.sprite.setPosition(this->teletransportarDimencion1(nave.sprite.getPosition(), dimencion));
	}
	
	nave.Update(deltaTime);

}

void GameManager::teclasAccion(sf::Event event, float deltatime)
{

		/* -1 block mayus
		 * 37 = ctrl
		 * 38 = shift
		 * 100 pause
		 * 71 = flecha_izquierda
		 * 72 = flecha_derecha
		 * 73 = flecha_arriba
		 * 74 = flecha_abajo
		 * */
	if(this->estado==0){
		if(event.key.code == 73){
		navePrincipal->velocidad += 0.03;
		navePrincipal->direccion=navePrincipal->sprite.getRotation();
		}
		if(event.key.code == 74)
		navePrincipal->velocidad = navePrincipal->velocidad - 0.03;
		
		switch(event.key.code){
			case 85: this->estado=3;break;
			case 72: navePrincipal->sprite.rotate(7); navePrincipal->rotar(7);break;
			case 71: navePrincipal->sprite.rotate(-7);navePrincipal->rotar(-7);break;
			case 37: crearMisil(*navePrincipal, 10000, 1, navePrincipal->velocidad, navePrincipal->sprite.getRotation(), navePrincipal->sprite.getPosition() , deltatime);break;
			default : break;
		}
	}
	if(this->estado==3){
		if(event.key.code==86){
		this->estado=0;
	}
		
				switch (event.key.code)
				{
				case 73:
					this->menuPausa->MoveUp();
					usleep(150000);
					break;

				case 74:
					this->menuPausa->MoveDown();
					usleep(150000);
					break;
	
				case 37:
					switch (this->menuPausa->GetPressedItem())
					{
					case 0:
						this->estado=0;
						break;
					case 1:
						eliminarNaves();
						eliminarMeteoros();
						eliminarMisiles();
						eliminarExplociones();
						this->Initialize(deltaTime);
						this->estado=0;
						break;
					case 2:
						this->estado=-1;
						break;
					default:break;
				}

			
	}
}
/*menu inicial*/
	if(this->estado==2){
		
				switch (event.key.code)
				{
				case 73:
					this->menuInicial->MoveUp();
					usleep(150000);
					break;

				case 74:
					this->menuInicial->MoveDown();
					usleep(150000);
					break;
	
				case 37:
					switch (this->menuInicial->GetPressedItem())
					{
					case 0:
						eliminarNaves();
						eliminarMeteoros();
						eliminarMisiles();
						eliminarExplociones();
						this->Initialize(deltaTime);
						this->estado=0;
						break;
					case 1:
						this->estado=4;
						break;
					case 2:
						this->estado=-1;
						break;
					default:break;
				}

			
	}
}


}
void GameManager::DrawGame(float deltaTime)
{
   if(this->estado==0){
    renderWindow.draw(backgroundSprite);
    navePrincipal->Draw(renderWindow);
    DibujarAsteroides();
    dibujarMisiles();
    dibujarNaves();
    dibujarExplociones(deltaTime);
    this->barraVidaNavePrincipal->draw(renderWindow);
    renderWindow.display();

}

  if(this->estado==3){
    renderWindow.draw(backgroundSprite);
	this->menuPausa->draw(renderWindow);
	renderWindow.draw(planetoideSprite);
    renderWindow.display();
}

  if(this->estado==2){
    renderWindow.draw(backgroundSprite);
	this->menuInicial->draw(renderWindow);
	renderWindow.draw(planetoideSprite);
    renderWindow.display();
}
	if(this->estado==-1){
	renderWindow.draw(backgroundSprite);
	dibujarExplociones(deltaTime);
	backgroundImg.loadFromFile("graphics/game_over1.bmp");
	backgroundSprite.setPosition(sf::Vector2f(300, 300));
	//renderWindow.draw(backgroundSprite);
	text.setPosition(sf::Vector2f(70, 100));
	text2.setPosition(sf::Vector2f(130, 200));
	text.setString("Total de puntos por asteroides destruidos: " + std::to_string(puntosAsteroide));
	text2.setString("Total de puntos por naves destruidas: " + std::to_string(puntosNaves));
	renderWindow.draw(text);
	renderWindow.draw(text2);
	//renderWindow.display();
	renderWindow.display();

}

}
