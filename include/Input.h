#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Input.h"

class Input
{
    public:

        Input(); //Constructeur
        bool getLeft();
        bool getRight();
        bool getJump();
        bool getAttack();
        bool getStart();
        bool getLow();
        bool getTop();
        bool getValid();
        bool getFocus();
        bool getJystick();
        void setLeft(bool etat);
        void setRight(bool etat);
        void setJump(bool etat);
        void setAttack(bool etat);
        void setStart(bool etat);
        void setLow(bool etat);
        void setTop(bool etat);
        void setValid(bool etat);
        void etatJoystick();
        void inputController(sf::RenderWindow &window); //Boucle d'évenement clavier
        void inputKeyboard(sf::RenderWindow &window); //Boucle d'évenement clavier


    private:

        bool m_left, m_right, m_jump, m_attack, m_start;
        bool m_low, m_top, m_valid, m_focus;
        bool m_jystick;
};

#endif // INPUT_H
