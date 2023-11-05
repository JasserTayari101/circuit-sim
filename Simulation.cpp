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
    
    if(!this->font.loadFromFile("assets/BrickSans-Bold.otf"))
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

//---- Input Definitions ----

Input::Input(bool val){
    this->value = val;
}

bool Input::link(Gate* gate){
    this->links.push_back(gate);
    return true;
}



//--- Gate Definitions ----
Gate::Gate(GateType type){
    this->type = type;

    switch(type){
    case NOT:
        this->texture.loadFromFile("assets/not-gate.png");
        break;
    case AND:
        this->texture.loadFromFile("assets/and-gate.png");
        break;
    case OR:
        this->texture.loadFromFile("assets/or-gate.png");
        break;
    case XOR:
        this->texture.loadFromFile("assets/xor-gate.png");
        break;
    }
    
    this->sprite.setTexture(this->texture);

}

//process input through gate
bool Gate::operate(bool in1, bool in2=false){
    switch(this->type){
        case NOT:
            return !in1;
        case AND:
            return in1&&in2;
        case OR:
            return in1 || in2;
        case XOR:
            return in1!=in2;
        default:
            return false;
    }
}

// link two gates
bool Gate::link(Gate* otherGate){
    if(this == otherGate)
        return false;
    else{
        this->links.push_back(otherGate);
        return true;
    }
}


sf::Sprite* Gate::getSprite(){
    return &(this->sprite);
}

Gate::GateType Gate::getType(){
    return this->type;
}





//  Simulation Definition

void print(int a){
    std::cout << a << std::endl;
}

void addPrint(int a, int b){
    std::cout<< a+b << std::endl;
}

void printText(Button* btn){
    std::cout << btn->getText() << std::endl;
}


void Simulation::initBtns(){
    this->fileBtn->init("File", printText,this->fileBtn);
    this->fileBtn->setPos(sf::Vector2f(50,10));

    this->editBtn->init("Edit", printText, this->editBtn);
    this->editBtn->setPos(sf::Vector2f(150,10));
}

void Simulation::initVars(){
    this->navigationLevel = 0;

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

//Simulation Logic functions

void Simulation::addInput(Input* input){
    this->inputs.push_back(input);
}

void Simulation::addGate(Gate* gate, unsigned short level){
    if(level>=1)
        this->gates[level-1].push_back(gate);
}

bool Simulation::isRunning(){
    return this->window->isOpen();
}






void Simulation::pollEvents(){
    while(this->window->pollEvent(this->event)){
        switch(this->event.type){
            // Close Event
            case sf::Event::Closed:
                this->window->close();
                break;
            // Keypress Event
            case sf::Event::KeyPressed :
                if(this->event.key.code == sf::Keyboard::Escape){
                    this->window->close();
                    break;
                }else if(this->event.key.code == sf::Keyboard::Add){
                    std::cout << "Add" << std::endl;
                    this->navigationLevel++;
                    std::cout << this->gates.size() << std::endl;
                    if(this->navigationLevel > this->gates.size())
                        gates.push_back(std::vector<Gate*>());
                    break;
                }
                else if(this->event.key.code == sf::Keyboard::A){
                    std::cout << "and gate" << std::endl;
                    Gate* gate = new Gate(Gate::AND);
                    this->addGate(gate,this->navigationLevel);
                    break;
                }
                break;
                // MouseClick Event
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

    this->window->clear(sf::Color(34, 34, 34));
    this->window->draw(*(this->toolbar) );

    // Draw Gates
    for(unsigned short lvl=0; lvl<(this->gates.size()); ++lvl){
        unsigned short counter = 1;
        for(Gate* gate: this->gates[lvl]){
            std::cout << lvl+1 << ": " << gate->getType() << std::endl;
            sf::Sprite* sprite = gate->getSprite();
            sprite->setPosition(100*lvl, 50*counter);
            this->window->draw(*sprite);
            
            ++counter;
        }
    }


    this->window->draw(this->fileBtn->getButtonArea());
    this->window->draw(this->fileBtn->getTextObj());

    this->window->draw(this->editBtn->getButtonArea());
    this->window->draw(this->editBtn->getTextObj());

    this->window->display();
}
