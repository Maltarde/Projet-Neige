#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <SFML/Graphics.hpp>

#include "Input.h"
#include "Map.h"

class Player
{
    public:

        Player();
        int getX();
        int getY();
        sf::Vector2f getViewCentre();
        void initialise();
        void checkPoint(int playerX, int playerY, int viewX, int viewY);
        void loadFrame(const std::string &frame); //chargement de l'image d'animation du personnage
        void drawPlayer(sf::RenderWindow &window); //gere l'animation et dessine le personnage
        void movePlayer(Input &etat); //gere le mouvement du personnage
        void collisionPlayer(Map& maps, const std::string &file); //Gere la collision avec la map
        void activeScroling(sf::RenderWindow &window); //Active la camera
        void scroling(Map& maps); //Gere muvement de la camera
        void loadAttack(const std::string &attack);
        void attack(sf::RenderWindow &window, Input &etat);

    private:

        //Coordonnée
        int m_initX; //Position initiale de personnage
        int m_initY;
        int m_x;  //Position personnage
        int m_y;

        //Direction
        bool m_rigth ;
        bool m_lelft;

        //Vitesse de déplacement
        int playerSpeed;

        //Etat du personnage
        enum m_etat {idle, walk, jump};
        m_etat m_etatPlayer = idle;

        //Taille du personnage
        int m_sizeX;
        int m_sizeY;

        //saut
        int m_initHeightJump;
        int m_heightJump;
        bool m_jump;

        //Animation du personnage
        int m_frame; //Numero de la frame en cour
        int m_frameMax; //Nombre de frame max
        int m_timeFrameNext; //Delai entre 2 frame
        int m_timerFrame; //Timer

        //Gere la camera
        int m_sizeViewX;
        int m_sizeViewY;
        int m_IntViewX;
        int m_IntViewY;
        int m_viewX;
        int m_viewY;
        sf::View m_view;

        //Gravité
        int m_gratitySpeed;
        int m_gratitySpeedMax;
        int m_initGratitySpeed;

        //Caractéristique du personnage
        int m_life; //Vie du personnage

        //Colision
        int m_collisionNumber;
        bool m_collitionTop;
        bool m_collitionBottom;
        bool m_collitionLeft;
        bool m_collitionRight;
        int m_adjustBottom;

        //Sprite du personnage
        sf::Texture m_playerTexture;
        sf::Sprite m_playerSprite;

        //attack
        bool m_attack;
        int m_attackSpeed;
        int m_attackAdjustX;
        int m_attackAdjustY;
        sf::Texture m_attackTexture;
        sf::Sprite m_attackSprite;
};

#endif // PLAYER_H
