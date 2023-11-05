#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <string>
#include <functional>
#include <iostream>
#include <vector>

namespace sm{


class Button{
    private:
        unsigned short width;
        unsigned short height;

        sf::RectangleShape* buttonArea;
        
        std::string text;
        //Coordinates
        float x,y;
        //a Button's callback function
        std::function<void()> callback;
        sf::Text textobj;
        sf::Font font;

    public:

        //Constructors and Destructors
        Button();

        ~Button();
        // State functions
        template <typename... Args>
        void init(std::string text, void(*cb)(Args... args),Args... args);


        bool setPos(sf::Vector2f pos);
        sf::Vector2f getPos();


        bool isClicked(sf::Vector2f pos);
        void Click();

        

        sf::RectangleShape getButtonArea();

        std::string getText();

        sf::Text getTextObj();

};



//Gate class that represent all logic gates AND / OR / XOR / NOT


class Gate{
    
    public:
        enum GateType{
            NOT,
            AND,
            OR,
            XOR
        };
    

        Gate(GateType type);

        //operate on input
        bool operate(bool in1, bool in2);

        //link two gates
        bool link(Gate* otherGate);

        sf::Sprite* getSprite();

        GateType getType();
    private:
        GateType type;

        //depending on the type of the gate
        sf::Texture texture;
        sf::Sprite sprite;
        
        //links to all other gates except self
        std::vector<Gate*> links;

};



class Input{
    private:
        bool value;
        std::vector<Gate*> links;
    
        sf::Texture texture;
        sf::Sprite sprite;
    public:
        Input(bool val);

        bool link(Gate* gate);

        sf::Sprite* getSprite();
};


class Simulation{
    private:
        sf::RenderWindow* window;
        sf::VideoMode VideoMode;

        sf::Event event;

        //Toolbar and Buttons;
        sf::RectangleShape* toolbar;

        Button* fileBtn = new Button();
        Button* editBtn = new Button();
        Button* viewBtn = new Button();
        Button* helpBtn = new Button();

        //represent maximum depth of circuit
        unsigned short depth;

        //represent componnets default scale
        float scaleX;
        float scaleY;

        //represent the current depth level of the circuit
        unsigned short navigationLevel;

        
        //a vector of inputs (level 1 logic components)
        std::vector<Input*> inputs;
        //a vector of levels(of gates) ; each level represent a depth in the circuit
        std::vector<std::vector<Gate*>> gates;

    public:
        //Constructors and Destructors
        Simulation();

        ~Simulation();


        void initBtns();
        void initVars();
        void initWindow();
        //Logic functions
        void addInput(Input* input);
        void addGate(Gate* gate, unsigned short level);

        void scaleBy(float deltaX, float deltaY);

        bool isRunning();

        void pollEvents();

        void update();

        void render();

};
}