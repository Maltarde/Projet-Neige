#ifndef TILE_H
#define TILE_H

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

class Tile: public sf::Drawable, public sf::Transformable
{
    public:

        Tile();
        //Création de la tuile
        void loadTileMap(std::string tileMap, sf::Vector2u tileSize, const int* tile, int width, int height);

    private:

        //Pour pouvoir utiliser window.draw() avec la class
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            states.transform *= getTransform();

            states.texture = &m_tileMapTexture;

            target.draw(m_tileMap, states);
        }

        sf::VertexArray m_tileMap;  //tableau de vexter contenant les tuile
        sf::Texture m_tileMapTexture; //texture des tuiles
};

#endif // TILE_H
