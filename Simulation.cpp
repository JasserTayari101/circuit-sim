#include "Simulation.hpp"

using namespace sm;

//---- Button Definitions ----

//Button constructor that takes a string and a function with its arguments


Button::Button(){
    width = 100;
    height = 30;

    this->callback = nullptr;
    this->buttonArea = new sf::RectangleShape(sf::Vector2f(width,height));
    this->buttonArea->setFillColor(sf::Color::Black);


}

template<typename... Args>
void Button::init(std::string text, void(*cb)(Args...), Args... args){
    this->text = text;
    
    if(!this->font.loadFromFile("BrickSans-Bold.otf"))
        std::cout << "Unable to load font" << std::endl;
    this->textobj.setFont(font);
    this->textobj.setString(this->text);
    this->textobj.setCharacterSize(20);
    this->textobj.setPosition(this->getPos());
    this->textobj.setFillColor(sf::Color(126,217,87));


    this->callback = std::bind(cb,args...);
}

Button::~Button(){
    delete this->buttonArea;
};

bool Button::setPos(sf::Vector2f pos){
    this->x = pos.x;
    this->y = pos.y;

    this->buttonArea->setPosition(pos);

    this->textobj.setPosition(pos);

    //indicate success
    return true;
};

sf::Vector2f Button::getPos(){
    return sf::Vector2f(this->x,this->y);
}

bool Button::isClicked(sf::Vector2f pos){
    return ( (pos.x>=this->x) && (pos.x<=(this->x+this->width) ) && (pos.y>=this->y)&& (pos.y<=(this->y+this->height) ) );
}

void Button::Click(){
    if(this->callback)
        this->callback();
}


sf::RectangleShape Button::getButtonArea(){
    return *(this->buttonArea);
}


std::string Button::getText(){
    return this->text;
}

sf::Text Button::getTextObj(){
    return this->textobj;
}
//Toolbar Definitions












//  Simulation Definition

void print(int a){
    std::cout << a << std::endl;
}

void addPrint(int a, int b){
    std::cout<< a+b << std::endl;
}


void Simulation::initBtns(){
    this->fileBtn->init("File", print, 3);
    this->fileBtn->setPos(sf::Vector2f(50,10));

    this->editBtn->init("Edit", addPrint, 10 ,5);
    this->editBtn->setPos(sf::Vector2f(150,10));
}

void Simulation::initVars(){

    this->toolbar = new sf::RectangleShape(sf::Vector2f(this->VideoMode.width,0.08*this->VideoMode.height));
    this->toolbar->setFillColor(sf::Color::Black);
    this->toolbar->setPosition(sf::Vector2f(0,0));

    this->initBtns();
}

void Simulation::initWindow(){
    this->VideoMode.width = 1000;
    this->VideoMode.height = 750;

    this->window = new sf::RenderWindow(this->VideoMode, "Circuit Simulation", sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(120);
}



Simulation::Simulation(){
    this->initWindow();

    this->initVars();
}

Simulation::~Simulation(){
    delete this->window;
}


bool Simulation::isRunning(){
    return this->window->isOpen();
}

void Simulation::pollEvents(){
    while(this->window->pollEvent(this->event)){
        switch(this->event.type){
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed :
                if(this->event.key.code == sf::Keyboard::Escape){
                    this->window->close();
                    break;
                }
                break;
            case sf::Event::MouseButtonReleased:
                //catch the mouseButton event
                sf::Event::MouseButtonEvent mouseEvent = this->event.mouseButton;
                //get the Button of the event
                sf::Mouse::Button btn = mouseEvent.button;
                //if left button clicked and window button clicked
                if( (btn == sf::Mouse::Button::Left) ){
                    if(this->fileBtn->isClicked(sf::Vector2f(mouseEvent.x, mouseEvent.y) ))
                        this->fileBtn->Click();
                    else if(this->editBtn->isClicked(sf::Vector2f(mouseEvent.x, mouseEvent.y) ))
                        this->editBtn->Click();
                }
        }

    }

}

void Simulation::update(){
    this->pollEvents();
}

void Simulation::render(){
    this->window->clear(sf::Color(55,40,33));

    this->window->draw(*(this->toolbar) );

    this->window->draw(this->fileBtn->getButtonArea());
    this->window->draw(this->fileBtn->getTextObj());

    this->window->draw(this->editBtn->getButtonArea());
    this->window->draw(this->editBtn->getTextObj());

    this->window->display();
}