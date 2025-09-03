#include "Player.h"

Player::Player()
{
    //annimation
    m_frame=0;
    m_frameMax=3;
    m_timeFrameNext=8;
    m_timerFrame=0;

    m_rigth=false;
    m_lelft=true;

    //position
    m_initX=20;
    m_initY=15;
    m_x=m_initX;
    m_y=m_initY;

    //saut
    m_initHeightJump=18;
    m_heightJump=m_initHeightJump;
    m_jump=false;

    //attaque
    m_attack=false;
    m_attackSpeed=8;
    m_attackAdjustX=24;
    m_attackAdjustY=38;

    //Déplacement
    playerSpeed=4;

    //taille image personnage
    m_sizeX=48;
    m_sizeY=64;

    //camera
    m_sizeViewX=800;
    m_sizeViewY=480;
    m_IntViewX=0;
    m_IntViewY=0;
    m_viewX=m_IntViewX;
    m_viewY=m_IntViewY;

    //gravité
    m_gratitySpeed=0;
    m_gratitySpeedMax=7;
    m_initGratitySpeed=1;

    //collition
    m_collisionNumber=19;
    m_collitionTop=false;
    m_collitionBottom=false;
    m_collitionLeft=false;
    m_collitionRight=false;
    m_adjustBottom=15;

    //image personnage
    m_playerSprite.setPosition(m_initX,m_initY);
    m_view.reset(sf::FloatRect(m_IntViewX, m_IntViewY, m_sizeViewX, m_sizeViewY));

    //position origin du personnage
    m_playerSprite.setOrigin(sf::Vector2f(m_sizeX/2, m_sizeY));
}

int Player::getX()
{
    return m_x;
}

int Player::getY()
{
    return m_y;
}

sf::Vector2f Player::getViewCentre()
{
    return m_view.getCenter();
}

void Player::initialise()
{
    m_x=m_initX;
    m_y=m_initY;
    m_view.reset(sf::FloatRect(m_IntViewX, m_IntViewY, m_sizeViewX, m_sizeViewY));
}

void Player::checkPoint(int playerX, int playerY, int viewX, int viewY)
{
    m_x=playerX;
    m_y=playerY-5;
    m_playerSprite.setPosition(playerX,playerY);
    m_view.setCenter(viewX, viewY);
}

void Player::loadFrame(const std::string &frame)
{
    if(!m_playerTexture.loadFromFile(frame))
    {
        std::cout << "Erreur de la frame personnage" << std::endl;
    }
    else
    {
        m_playerSprite.setTexture(m_playerTexture);
    }
}

void Player::drawPlayer(sf::RenderWindow &window)
{
    //Comter le numero de frame
    if(m_timerFrame == m_timeFrameNext)
    {
        if(m_frame < m_frameMax)
        {
            m_frame++;
        }
        else
        {
            m_frame=0;
        }

        m_timerFrame=0;
    }
    else
    {
        m_timerFrame++;
    }

    //Gere les etats
    if(m_etatPlayer == idle)
    {
        if(m_rigth)
        {
            m_playerSprite.setTextureRect(sf::IntRect(0*m_sizeX, m_sizeY*1, m_sizeX, m_sizeY));
        }
        else if(m_lelft)
        {
            m_playerSprite.setTextureRect(sf::IntRect(0*m_sizeX, m_sizeY*2, m_sizeX, m_sizeY));
        }
    }
    else if(m_etatPlayer == walk)
    {
        if(m_rigth)
        {
            m_playerSprite.setTextureRect(sf::IntRect(m_frame*m_sizeX, m_sizeY*1, m_sizeX, m_sizeY));
        }
        else if(m_lelft)
        {
            m_playerSprite.setTextureRect(sf::IntRect(m_frame*m_sizeX, m_sizeY*2, m_sizeX, m_sizeY));
        }
    }

    window.draw(m_playerSprite);
}

void Player::movePlayer(Input &etat)
{
    //Gravité
    if(!m_collitionBottom)
    {
        if(m_gratitySpeed < m_gratitySpeedMax)
        {
            m_gratitySpeed++;
        }
        m_y+=m_gratitySpeed;
    }
    else
    {
        m_gratitySpeed=m_initGratitySpeed;
    }

    //Saut
    if(etat.getJump() && m_collitionBottom && !m_jump)
    {
        m_jump=true;
        m_etatPlayer=jump;
        m_heightJump=m_initHeightJump;
        etat.setJump(false);
    }
    else if(m_jump && !m_collitionTop)
    {
        m_heightJump-=m_initGratitySpeed;

        if(m_heightJump > 0)
        {
            m_y-=m_heightJump;
        }
        else
        {
            m_jump=false;
        }
    }
    else if(m_collitionTop)
    {
        m_heightJump=0;
        m_jump=false;
    }

    //Gerer les etats et le mouvement du personnage
    if(etat.getRight())
    {
        if(!m_collitionRight)
        {
             m_x+=playerSpeed;
             m_playerSprite.setPosition(m_x, m_y+m_adjustBottom);
        }

        m_lelft=true;
        m_rigth=false;
        m_etatPlayer=walk;
    }
    else if(etat.getLeft())
    {
        if(!m_collitionLeft)
        {
            m_x-=playerSpeed;
            m_playerSprite.setPosition(m_x, m_y+m_adjustBottom);
        }
        m_rigth=true;
        m_lelft=false;
        m_etatPlayer=walk;
    }
    else
    {
        if(!m_collitionBottom)
        {
            m_playerSprite.setPosition(m_x, m_y+m_adjustBottom);
        }
        m_etatPlayer=idle;
    }
}

void Player::collisionPlayer(Map& maps, const std::string& file)
{
    std::ifstream fileTile(file.c_str());
    if(fileTile)
    {
        //Recureration des information de la carte
        int to, ta;

        fileTile >> to;
        fileTile >> ta;

        int levelmaps[maps.getMapSizeX()*maps.getMapSizeY()];

        for(int i=0;i<250*15;i++)
        {
            fileTile >> levelmaps[i];
        }

        //Calcul des coordonnées du personnage
        int numberTileX = (float) m_x/maps.getTileSize();
        int numberTileY = (float) m_y/maps.getTileSize();
        int numberSizePlayer=m_sizeY/maps.getTileSize();

        //Collision vers le haut et ler bas
        if(levelmaps[numberTileX+numberTileY*maps.getMapSizeX()] <= m_collisionNumber)
        {
            m_collitionBottom=true;
        }
        else if(levelmaps[(numberTileX+numberTileY*maps.getMapSizeX())-maps.getMapSizeX()*numberSizePlayer] <= m_collisionNumber)
        {
            m_collitionTop=true;
        }
        else
        {
            m_collitionBottom=false;
            m_collitionTop=false;
        }

        //Collision sur les 2 cotés du personnage
        if(levelmaps[(numberTileX+numberTileY*maps.getMapSizeX())-maps.getMapSizeX()+1] <= m_collisionNumber)
        {
            m_collitionRight=true;
        }
        else if(levelmaps[(numberTileX+numberTileY*maps.getMapSizeX())-maps.getMapSizeX()-1] <= m_collisionNumber)
        {
            m_collitionLeft=true;
        }
        else
        {
            m_collitionRight=false;
            m_collitionLeft=false;
        }
    }
    else
    {
        std::cout << "Erreur ouverture fichier de la tuile map" << std::endl;
    }
}

void Player::activeScroling(sf::RenderWindow &window)
{
    //Active la camera
    window.setView(m_view);
}


void Player::scroling(Map& maps)
{
    int endMap = maps.getMapSizeX()*maps.getTileSize();

    //Gere le moivement de la camera
    if(m_x >= (m_sizeViewX/2) && m_x < endMap-(m_sizeViewX/2))
    {
        if(m_etatPlayer == walk)
        {
            if(m_rigth)
            {
                m_viewX-=playerSpeed;
                m_viewY=0;

                m_view.move(-playerSpeed, 0);
            }
            else
            {
                m_viewX-=playerSpeed;
                m_viewY=0;

                m_view.move(playerSpeed, 0);
            }
        }
    }
}

void Player::loadAttack(const std::string &attack)
{
    if(!m_attackTexture.loadFromFile(attack))
    {
        std::cout << "Erreur de la frame attaque" << std::endl;
    }
    else
    {
        m_attackSprite.setTexture(m_attackTexture);
    }
}

void Player::attack(sf::RenderWindow &window, Input &etat)
{
    //Attaque
    if(etat.getAttack())
    {
        m_attack=true;
    }

    if(m_attack)
    {
        m_attackSprite.setPosition(sf::Vector2f(m_x+m_attackAdjustX, m_y-m_attackAdjustY));
        m_attack=false;
    }
    m_attackSprite.move(sf::Vector2f(m_attackSpeed, 0));
    window.draw(m_attackSprite);
}
