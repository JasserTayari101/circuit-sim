#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <string>
#include <functional>
#include <iostream>


namespace sm{


//template <typename ...CallbackArgs>
//using Callback = void(*)(CallbackArgs...);


class Button{
    private:
        unsigned short width;
        unsigned short height;

        sf::RectangleShape* buttonArea;
        std::string text;
        int x,y;

        //Callback<> callback;
        using Callback = void(*)();
        Callback callback;

    public:
        //Constructors and Destructors
        Button();

        //template <typename ...CallbackArgs>
        Button(std::string text,Callback cb);

        /*template<typename ...Args>
        Button(std::string, sf::Font& font, Args... args);*/
        
        ~Button();
        // State functions
        bool setPos(sf::Vector2i pos);

        sf::Vector2i getPos();

        bool isClicked(sf::Vector2i pos);

        void onClick();

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