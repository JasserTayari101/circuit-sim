#include "Program.hpp"


//---- Button Definitions ----

//Button constructor that takes a string and a function with its arguments
template <typename ...Args>
Button::Button(std::string text, std::function<void()> callback, Args... args){
    width = 10;
    height = 10;

    this->text = text;

    this->buttonArea = new sf::RectangleShape(sf::Vector2f(width,height));

    this->callback = callback;

};

Button::~Button(){
    delete this->buttonArea;
};

bool Button::setPos(sf::Vector2i pos){
    this->x = pos.x;
    this->y = pos.y;

    //indicate success
    return true;
};

sf::Vector2i Button::getPos(){
    return sf::Vector2i(this->x,this->y);
}

bool Button::isClicked(sf::Vector2i pos){
    return ( (pos.x == this->x) && (pos.y == this->y) );
}


void onClick(){
    if(this->callback)
        callback();
}

//Toolbar Definitions

Toolbar::Toolbar(){
    
}