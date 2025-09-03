#include "Interface.h"

Interface::Interface()
{

    //Savoir quelle page est active
    m_homePageActive=true;
    m_savePageActive=false;

    ////Position du selecteur dans le menu
    m_selectorPosition=0;
    m_moduloMenu=3;
    m_moduloMenuStart=4;
    m_moduloMenuSave=2;

    //Coordonnée que doit prendre le selecteur
    m_selectorX=12;
    m_selectorY0=142;
    m_selectorY1=201;
    m_selectorY2=259;
    m_selectorStartX=135;
    m_selectorStartY0=114;
    m_selectorStartY1=164;
    m_selectorStartY2=211;
    m_selectorStartY3=261;
    m_pictureStartX=150;
    m_pictureStartY=90;
    m_selectorNoSpead=true;

    //Timer pour éviter que le selecteur ne bouche trop vite
    m_selectorTimer=0;
    m_nbPictureMax=10;
}

bool Interface::getHomePageActive()
{
    return m_homePageActive;
}

bool Interface::getSavePageActive()
{
    return m_savePageActive;
}

void Interface::loadHomePage(const std::string &homePage)
{
    if(!m_homePageTexture.loadFromFile(homePage))
    {
        std::cout << "Erreur chargement de la page d'acceuil" << std::endl;
    }
    else
    {
       m_homePage.setTexture(m_homePageTexture);
    }
}

void Interface::drawHomePage(sf::RenderWindow &window)
{
    window.draw(m_homePage);
}

void Interface::LoadStart(const std::string &start)
{
    if(!m_startTexture.loadFromFile(start))
    {
        std::cout << "Erreur chargement image de start" << std::endl;
    }
    else
    {
       m_start.setTexture(m_startTexture);
    }
}

void Interface::drawSave(sf::RenderWindow &window)
{
    window.draw(m_save);
}

void Interface::LoadSave(const std::string &save)
{
    if(!m_saveTexture.loadFromFile(save))
    {
        std::cout << "Erreur chargement image de save" << std::endl;
    }
    else
    {
       m_save.setTexture(m_saveTexture);
    }
}

void Interface::drawStart(sf::RenderWindow &window)
{
    window.draw(m_start);
}

void Interface::LoadSelector(const std::string &selector)
{
    if(!m_selectorTexture.loadFromFile(selector))
    {
        std::cout << "Erreur chargement du selecteur" << std::endl;
    }
    else
    {
       m_selector.setTexture(m_selectorTexture);
    }
}

void Interface::drawSelector(sf::RenderWindow &window)
{
    window.draw(m_selector);
}

void Interface::managesMenu(sf::RenderWindow &window, Input &input, Map &maps, Player &player)
{
    sf::Vector2f positionView=player.getViewCentre();

    if(input.getValid()) //SI il y a un appui sur une touche de validatuin
    {
        input.setValid(false);

        if(m_homePageActive)
        {
            switch(m_selectorPosition)
            {
                case 0:
                    m_homePageActive=false;
                    m_selectorPosition=0;
                    input.setStart(false);
                    input.setAttack(false);
                    player.initialise();
                    break;
                case 1:
                    m_savePageActive=true;
                    m_homePageActive=false;
                    m_selectorPosition=0;
                    break;
                case 2:
                    window.close();
                    break;
                default:
                    break;
            }
        }
        else if(m_savePageActive)
        {
            switch(m_selectorPosition)
            {
                case 0:
                    m_homePageActive=true;
                    m_savePageActive=false;
                    break;
                case 1:
                    {
                        std::ifstream save("save/save.txt");

                        if(save)
                        {
                            int potisionX, positionY, viewX, viewY;

                            save >> potisionX;
                            save >> positionY;
                            save >> viewX;
                            save >> viewY;

                            player.checkPoint(potisionX, positionY, viewX, viewY);

                            m_savePageActive=false;
                            m_selectorPosition=0;
                            input.setStart(false);
                            input.setAttack(false);
                        }
                        else
                        {
                            std::cout << "ERREUR: Impossible d'ouvrir le fichier save." << std::endl;
                        }
                    }
                    break;
                default:
                    break;
            }
        }
        else
        {
            switch(m_selectorPosition)
            {
                case 0:
                    input.setStart(false);
                    break;
                case 1:
                    {
                        std::ofstream saveGame("save/save.txt");

                        if(saveGame)
                        {
                            saveGame << player.getX() << " " << player.getY() << " " << positionView.x << " " << positionView.y;
                        }
                        else
                        {
                            std::cout << "ERREUR: Impossible d'ouvrir le save." << std::endl;
                        }
                    }
                    break;
                case 2:
                    player.initialise();
                    m_homePageActive=true;
                    m_selectorPosition=0;
                    break;
                case 3:
                    window.close();
                    break;
                default:
                    break;
            }
        }
    }
    else
    {
        if(m_selectorNoSpead)
        {
            //Si appui du un bouton pour déplacer le curseur
            if(m_homePageActive)
            {
                if(input.getLow())
                {
                    m_selectorPosition=(m_selectorPosition+1)%m_moduloMenu;
                    m_selectorNoSpead=false;
                }
                else if(input.getTop())
                {
                    m_selectorPosition=(m_selectorPosition-1)%m_moduloMenu;
                    if(m_selectorPosition < 0)
                        m_selectorPosition=m_moduloMenu-1;
                    m_selectorNoSpead=false;
                }

                switch(m_selectorPosition)
                {
                    case 0:
                        m_selector.setPosition(sf::Vector2f(m_selectorX, m_selectorY0));
                        break;
                    case 1:
                        m_selector.setPosition(sf::Vector2f(m_selectorX, m_selectorY1));
                        break;
                    case 2:
                        m_selector.setPosition(sf::Vector2f(m_selectorX, m_selectorY2));
                        break;
                    default:
                        break;
                }
            }
            else if(m_savePageActive)
            {
                 if(input.getLow())
                {
                    m_selectorPosition=(m_selectorPosition+1)%m_moduloMenuSave;
                    m_selectorNoSpead=false;
                }
                else if(input.getTop())
                {
                    m_selectorPosition=(m_selectorPosition-1)%m_moduloMenuSave;
                    if(m_selectorPosition < 0)
                        m_selectorPosition=m_moduloMenuSave-1;
                    m_selectorNoSpead=false;
                }

                switch(m_selectorPosition)
                {
                    case 0:
                        m_selector.setPosition(sf::Vector2f(m_selectorX, m_selectorY0));
                        break;
                    case 1:
                        m_selector.setPosition(sf::Vector2f(m_selectorX, m_selectorY1));
                        break;
                    default:
                        break;
                }
            }
            else
            {
                if(input.getLow())
                {
                    m_selectorPosition=(m_selectorPosition+1)%m_moduloMenuStart;
                    m_selectorNoSpead=false;
                }
                else if(input.getTop())
                {
                    m_selectorPosition=(m_selectorPosition-1)%m_moduloMenuStart;
                    if(m_selectorPosition < 0)
                        m_selectorPosition=m_moduloMenuStart-1;
                    m_selectorNoSpead=false;
                }

                switch(m_selectorPosition)
                {
                    case 0:
                        m_selector.setPosition(sf::Vector2f(positionView.x-m_selectorStartX, m_selectorStartY0));
                        break;
                    case 1:
                        m_selector.setPosition(sf::Vector2f(positionView.x-m_selectorStartX, m_selectorStartY1));
                        break;
                    case 2:
                        m_selector.setPosition(sf::Vector2f(positionView.x-m_selectorStartX, m_selectorStartY2));
                        break;
                    case 3:
                        m_selector.setPosition(sf::Vector2f(positionView.x-m_selectorStartX, m_selectorStartY3));
                        break;
                    default:
                        break;
                }

                m_start.setPosition(sf::Vector2f(positionView.x-m_pictureStartX,m_pictureStartY));
            }
        }
        else  //Permet d'attendre un petit moment avant de pouvoir redeplacer le curseur de selection
        {
            if(m_selectorTimer < m_nbPictureMax)
            {
                m_selectorTimer++;
            }
            else
            {
                m_selectorTimer=0;
                m_selectorNoSpead=true;
            }
        }
    }
}
