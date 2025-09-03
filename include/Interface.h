#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <SFML/Graphics.hpp>

#include "Input.h"
#include "Map.h"
#include "Player.h"

class Interface
{
    public:

        Interface();
        bool getHomePageActive();
        bool getSavePageActive();
        void loadHomePage(const std::string &homePage);
        void drawHomePage(sf::RenderWindow &window);
        void LoadSave(const std::string &homePage);
        void drawSave(sf::RenderWindow &window);
        void LoadStart(const std::string &homePage);
        void drawStart(sf::RenderWindow &window);
        void LoadSelector(const std::string &homePage);
        void drawSelector(sf::RenderWindow &window);
        void managesMenu(sf::RenderWindow &window, Input &input, Map &maps, Player &player);

    private:

        //Savoir quelle page est active
        bool m_homePageActive;  //Page d'acceuil actif
        bool m_savePageActive; //Page des sauvegarde actif

        //Coordonnée que doit prendre le selecteur
        int m_selectorX;
        int m_selectorY0;
        int m_selectorY1;
        int m_selectorY2;
        int m_selectorStartX;
        int m_selectorStartY0;
        int m_selectorStartY1;
        int m_selectorStartY2;
        int m_selectorStartY3;
        int m_pictureStartX;
        int m_pictureStartY;

        //Position du selecteur dans le menu
        int m_selectorPosition;
        int m_moduloMenu; //Pour revenir au debout du menu
        int m_moduloMenuStart;
        int m_moduloMenuSave;


        //Timer pour éviter que le selecteur ne bouche trop vite
        int m_selectorTimer;
        int m_nbPictureMax;
        bool m_selectorNoSpead; //pour pas que le selecteur change trop rapideme

        //Chargement des texture
        sf::Texture m_homePageTexture;  //texture page d'acceuil
        sf::Sprite m_homePage; //Sprite page d'acceuil
        sf::Texture m_saveTexture;  //texture page de
        sf::Sprite m_save; //Sprite page d'acceuil
        sf::Texture m_startTexture;  //texture menu start
        sf::Sprite m_start; //Sprite page menu start
        sf::Texture m_selectorTexture;  //texture menu selecteur
        sf::Sprite m_selector; //Sprite page menu selecteur
};

#endif // INTERFACE_H
