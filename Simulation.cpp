#include "Simulation.hpp"

using namespace sm;

//---- Button Definitions ----

//Button constructor that takes a string and a function with its arguments


Button::Button(){
    this->callback = nullptr;
    width = 50;
    height = 20;
    this->buttonArea = new sf::RectangleShape(sf::Vector2f(width,height));
    this->buttonArea->setFillColor(sf::Color::Red);
}

template<typename... Args>
void Button::init(std::string text, void(*cb)(Args...), Args... args){
    this->text = text;
    this->callback = std::bind(cb,args...);
}

Button::~Button(){
    delete this->buttonArea;
};

bool Button::setPos(sf::Vector2f pos){
    this->x = pos.x;
    this->y = pos.y;

    this->buttonArea->setPosition(pos);

    //indicate success
    return true;
};

sf::Vector2i Button::getPos(){
    return sf::Vector2i(this->x,this->y);
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
//Toolbar Definitions












//  Simulation Definition

void print(int a){
    std::cout << a << std::endl;
}

void addPrint(int a, int b){
    std::cout<< a+b << std::endl;
}

void Simulation::initVars(){
    this->window = nullptr;
    this->button.init("Hello world", print, 3);
    this->button.setPos(sf::Vector2f(250,0));
    
    //this->button2.init("Second",addPrint, 10 , 5);
    //this->button2.setPos(sf::Vector2f(100,0));
}

void Simulation::initWindow(){
    this->VideoMode.width = 500;
    this->VideoMode.height = 500;

    this->window = new sf::RenderWindow(this->VideoMode, "Test", sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(120);
}



Simulation::Simulation(){
    this->initVars();

    this->initWindow();
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
                };
                break;
            case sf::Event::MouseButtonReleased:
                //catch the mouseButton event
                sf::Event::MouseButtonEvent mouseEvent = this->event.mouseButton;
                //get the Button of the event
                sf::Mouse::Button btn = mouseEvent.button;
                //if left button clicked and window button clicked
                if( (btn == sf::Mouse::Button::Left) ){
                    if(this->button.isClicked(sf::Vector2f(mouseEvent.x, mouseEvent.y) ))
                        this->button.Click();
                    //else if(this->button2.isClicked(sf::Vector2f(mouseEvent.x, mouseEvent.y) ))
                       // this->button2.Click();
                }
        }

    }

}

void Simulation::update(){
    this->pollEvents();
}

void Simulation::render(){
    this->window->clear(sf::Color::Blue);

    this->button.setPos(sf::Vector2f(0,30));
    this->window->draw(this->button.getButtonArea());

    //this->window->draw(this->button2.getButtonArea());

    this->window->display();
}