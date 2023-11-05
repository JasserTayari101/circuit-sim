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
        int x,y;

        std::function<void()> callback;

    public:
        //Constructors and Destructors
        Button();

        ~Button();
        // State functions
        void init(std::string text, void(*cb)(int),int a);

        bool setPos(sf::Vector2f pos);

        sf::Vector2i getPos();

        bool isClicked(sf::Vector2f pos);

        void onClick();

        
        void Click();

        sf::RectangleShape getButtonArea();

        std::string getText();

};



/*class Toolbar{
    private:
        Button buttons[12];
        sf::RectangleShape toolbarArea;

    public:
        //Constructors and Destructors
        Toolbar();
        ~Toolbar();

        

};*/




class Simulation{
    private:
        sf::RenderWindow* window;
        sf::VideoMode VideoMode;

        sf::Event event;

        //Toolbar toolbar;
        Button button;

    public:
        //Constructors and Destructors
        Simulation();

        ~Simulation();


        void initVars();

        void initWindow();

        bool isRunning();

        void pollEvents();

        void update();

        void render();
};
}