#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <string>
#include <functional>


class Button{
    private:
        static unsigned short width;
        static unsigned short height;

        sf::RectangleShape* buttonArea;
        std::string text;
        int x,y;
        
        //std::function<void()> callback;

    public:
        //Constructors and Destructors
        template <typename ...Args>
        Button(std::string text,std::function<void()> callback ,Args... args);

        /*template<typename ...Args>
        Button(std::string, sf::Font& font, Args... args);*/
        
        ~Button();
        // State functions
        bool setPos(sf::Vector2i pos);

        sf::Vector2i getPos();

        bool isClicked(sf::Vector2i pos);

        void onClick();

};



class Toolbar{
    private:
        Button buttons[12];
        sf::RectangleShape toolbarArea;

    public:
        //Constructors and Destructors
        Toolbar();
        ~Toolbar();

        

};




class Program{
    private:
        sf::RenderWindow* window;
        sf::VideoMode VideoMode;
        
        sf::Event event;

        Toolbar toolbar;
        

    public:
        void initVars();

        void initWindow();


};