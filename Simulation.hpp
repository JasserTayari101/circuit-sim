#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <string>
#include <functional>
#include <iostream>


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

    public:
        //Constructors and Destructors
        Simulation();

        ~Simulation();


        void initBtns();

        void initVars();

        void initWindow();

        bool isRunning();

        void pollEvents();

        void update();

        void render();
};
}