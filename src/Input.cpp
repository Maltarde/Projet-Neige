#include "Input.h"

Input::Input()
{
    m_left=false;
    m_right=false;
    m_jump=false;
    m_attack=false;
    m_start=false;
    m_low=false;
    m_top=false;
    m_valid=false;
    m_focus=false;
    m_jystick=false;
}

bool Input::getLeft()
{
    return m_left;
}

bool Input::getRight()
{
    return m_right;
}

bool Input::getJump()
{
    return m_jump;
}

bool Input::getAttack()
{
    return m_attack;
}

bool Input::getStart()
{
    return m_start;
}

bool Input::getLow()
{
    return m_low;
}

bool Input::getTop()
{
    return m_top;
}

bool Input::getValid()
{
    return m_valid;
}

bool Input::getFocus()
{
    return m_focus;
}

bool Input::getJystick()
{
    return m_jystick;
}

void Input::setLeft(bool etat)
{
    m_left=etat;
}

void Input::setRight(bool etat)
{
    m_right=etat;
}

void Input::setJump(bool etat)
{
    m_jump=etat;
}

void Input::setAttack(bool etat)
{
    m_attack=etat;
}

void Input::setStart(bool etat)
{
    m_start=etat;
}

void Input::setLow(bool etat)
{
    m_low=etat;
}

void Input::setTop(bool etat)
{
    m_top=etat;
}

void Input::setValid(bool etat)
{
    m_valid=etat;
}

void Input::etatJoystick()
{
    if (sf::Joystick::isConnected(0))
    {
        m_jystick=true;
    }
}

void Input::inputKeyboard(sf::RenderWindow &window)
{
    sf::Event event;
    while(window.pollEvent(event))
    {
        switch(event.type)
        {
            case sf::Event::Closed:
                window.close();
                break;
             case sf::Event::JoystickConnected:
                 m_jystick=true;
                std::cout << "Connection manette identifiant: " << event.joystickConnect.joystickId << std::endl;
                break;
            case sf::Event::JoystickDisconnected:
                std::cout << "Déconnection manette identifiant: " << event.joystickConnect.joystickId << std::endl;
                m_jystick=false;
                break;
            case sf::Event::KeyPressed:
                switch(event.key.code)
                {
                    case sf::Keyboard::Q:
                        m_left=true;
                        std::cout << "left " << m_left << std::endl;
                        break;
                     case sf::Keyboard::Left:
                        m_left=true;
                        std::cout << "left " << m_left << std::endl;
                        break;
                    case sf::Keyboard::D:
                        m_right=true;
                        std::cout << "right " << m_right << std::endl;
                        break;
                    case sf::Keyboard::Right:
                        m_right=true;
                        std::cout << "right " << m_right << std::endl;
                        break;
                    case sf::Keyboard::Z:
                        if(!m_jump)
                        {
                            m_jump=true;
                            m_top=true;
                            std::cout << "jump/top " << m_jump << std::endl;
                        }
                        break;
                    case sf::Keyboard::Up:
                        if(!m_jump)
                        {
                            m_jump=true;
                            m_top=true;
                            std::cout << "jump/top " << m_jump << std::endl;
                        }
                        break;
                    case sf::Keyboard::Space:
                        if(!m_attack)
                        {
                            m_attack=true;
                        std::cout << "attack " << m_attack << std::endl;
                        }
                        break;
                    case sf::Keyboard::Escape:
                        if(m_start)
                        {
                            m_start=false;
                        }
                        else
                        {
                            m_start=true;
                        }
                        std::cout << "start " << m_start << std::endl;
                        break;
                    case sf::Keyboard::P:
                        if(m_start)
                        {
                            m_start=false;
                        }
                        else
                        {
                            m_start=true;
                        }
                        std::cout << "start " << m_start << std::endl;
                        break;
                    case sf::Keyboard::S:
                        if(!m_low)
                        {
                            m_low=true;
                            std::cout << "low " << m_low << std::endl;
                        }
                        break;
                    case sf::Keyboard::Down:
                        if(!m_low)
                        {
                            m_low=true;
                            std::cout << "low " << m_low << std::endl;
                        }
                        break;
                    case sf::Keyboard::Return:
                        if(m_valid)
                        {
                            m_valid=false;
                        }
                        else
                        {
                            m_valid=true;
                        }
                        std::cout << "valid " << m_valid << std::endl;
                        break;
                    default:
                        break;
                }
                break;
            case sf::Event::KeyReleased:
                switch(event.key.code)
                {
                    case sf::Keyboard::Q:
                        m_left=false;
                        std::cout << "left " << m_left << std::endl;
                        break;
                     case sf::Keyboard::Left:
                        m_left=false;
                        std::cout << "left " << m_left << std::endl;
                        break;
                    case sf::Keyboard::D:
                        m_right=false;
                        std::cout << "right " << m_right << std::endl;
                        break;
                    case sf::Keyboard::Right:
                        m_right=false;
                        std::cout << "right " << m_right << std::endl;
                        break;
                    case sf::Keyboard::Z:
                        m_jump=false;
                        m_top=false;
                        std::cout << "jump/top " << m_jump << std::endl;
                        break;
                    case sf::Keyboard::Up:
                        m_jump=false;
                        m_top=false;
                        std::cout << "jump/top " << m_jump << std::endl;
                        break;
                    case sf::Keyboard::Space:
                        m_attack=false;
                        std::cout << "attack " << m_attack << std::endl;
                        break;
                    case sf::Keyboard::S:
                        m_low=false;
                        std::cout << "low " << m_low << std::endl;
                        break;
                    case sf::Keyboard::Down:
                        m_low=false;
                        std::cout << "low " << m_low << std::endl;
                        break;
                    default:
                        break;
                }
                break;
             case sf::Event::LostFocus:
                m_focus=true;
                std::cout << "focus: " << m_focus << std::endl;
                break;
            case sf::Event::GainedFocus:
                m_focus=false;
                std::cout << "focus: " << m_focus << std::endl;
                break;
            default:
                break;
        }
    }
}

void Input::inputController(sf::RenderWindow &window)
{
    sf::Event event;
    while(window.pollEvent(event))
    {
        switch(event.type)
        {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::JoystickConnected:
                m_jystick=true;
                std::cout << "Connection manette identifiant: " << event.joystickConnect.joystickId << std::endl;
                break;
            case sf::Event::JoystickDisconnected:
                m_jystick=false;
                std::cout << "Déconnection manette identifiant: " << event.joystickConnect.joystickId << std::endl;
                break;
            case sf::Event::JoystickButtonPressed:
                switch(event.joystickButton.button)
                {
                    case 0:
                        m_jump=true;

                         if(m_valid)
                        {
                            m_valid=false;
                        }
                        else
                        {
                            m_valid=true;
                        }
                        std::cout << "jump/valid " << m_jump <<" / " << m_valid << std::endl;
                        break;
                    case 2:
                        m_attack=true;
                        std::cout << "attack " << m_attack << std::endl;
                        break;
                    case 6:
                        if(m_start)
                        {
                            m_start=false;
                        }
                        else
                        {
                            m_start=true;
                        }
                        std::cout << "start " << m_start << std::endl;
                        break;
                    default:
                        break;
                }
                break;
            case sf::Event::JoystickButtonReleased:
                switch(event.joystickButton.button)
                {
                    case 0:
                        m_jump=false;
                        std::cout << "jump " << m_jump << std::endl;
                        break;
                    case 2:
                        m_attack=false;
                        std::cout << "attack " << m_attack << std::endl;
                        break;
                    default:
                        break;
                }
                break;
            case sf::Event::JoystickMoved:
               switch(event.joystickMove.axis)
               {
                    case sf::Joystick::Z:
                        if(event.joystickMove.position < -95)
                        {
                            m_right=true;
                        }
                        else if(event.joystickMove.position > 95)
                        {
                            m_left=true;
                        }
                        else
                        {
                            m_right=false;
                            m_left=false;
                        }
                        std::cout << "left: " << m_left << " right: " << m_right << std::endl;
                        break;
                    case sf::Joystick::PovX:
                        if(event.joystickMove.position == 100)
                        {
                            m_right=true;
                        }
                        else if(event.joystickMove.position == -100)
                        {
                             m_left=true;
                        }
                        else
                        {
                            m_right=false;
                            m_left=false;
                        }
                        std::cout << "left: " << m_left << " right: " << m_right << std::endl;
                        break;
                    case sf::Joystick::PovY:
                        if(event.joystickMove.position == 100)
                        {
                            m_top=true;
                        }
                        else if(event.joystickMove.position == -100)
                        {
                             m_low=true;
                        }
                        else
                        {
                            m_top=false;
                            m_low=false;
                        }
                        std::cout << "top: " << m_top << " low: " << m_low << std::endl;
                        break;
                    default:
                        break;
               }
                break;
             case sf::Event::LostFocus:
                m_focus=true;
                std::cout << "focus: " << m_focus << std::endl;
                break;
            case sf::Event::GainedFocus:
                m_focus=false;
                std::cout << "focus: " << m_focus << std::endl;
                break;
            default:
                break;
        }
    }
}
