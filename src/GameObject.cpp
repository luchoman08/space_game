#include "GameObject.hpp"

void GameObject::actualizarPeso(){
	
	this->peso=this->sprite.getScale().x * this->ancho * this->sprite.getScale().y * this->alto;
};

int GameObject::Draw(sf::RenderWindow& renderWindow){
	
	renderWindow.draw(this->sprite);
	
}
