#include "Tile.h"

Tile::Tile() {}

void Tile::loadTileMap(std::string tileMap, sf::Vector2u tileSize, const int* tile, int width, int height)
{
    //Chargement de l'image des tuile
    if(!m_tileMapTexture.loadFromFile(tileMap))
    {
        std::cout << "Erreur chargement de l'image tile" << std::endl;
    }

    //Mise en forme de tableau de vertex
    m_tileMap.setPrimitiveType(sf::Quads);
    m_tileMap.resize(width*height*4);

    //Creation de la map tile
    for(int i=0;i<width;i++)
    {
        for(int j=0;j<height;j++)
        {
            int tileNumber=tile[i+j*width]; //Recuperation numero tuile

            int tu=tileNumber % (m_tileMapTexture.getSize().x / tileSize.x); //détermination de la position de la tuile
            int tv=tileNumber / (m_tileMapTexture.getSize().x / tileSize.x); //détermination de la position de la tuile

            sf::Vertex* quad= &m_tileMap[(i+j*width)*4]; //Pointeur vers le Quad

            //calcul position du Quad
            quad[0].position= sf::Vector2f(i*tileSize.x , j*tileSize.y);
            quad[1].position= sf::Vector2f((i+1)*tileSize.x , j*tileSize.y);
            quad[2].position= sf::Vector2f((i+1)*tileSize.x ,(j+1)*tileSize.y);
            quad[3].position= sf::Vector2f(i*tileSize.x ,(j+1)*tileSize.y);

            //applique la texture au Quad
            quad[0].texCoords= sf::Vector2f(tu*tileSize.x , tv*tileSize.y);
            quad[1].texCoords= sf::Vector2f((tu+1)*tileSize.x , tv*tileSize.y);
            quad[2].texCoords= sf::Vector2f((tu+1)*tileSize.x ,(tv+1)*tileSize.y);
            quad[3].texCoords= sf::Vector2f(tu*tileSize.x ,(tv+1)*tileSize.y);
        }
    }
}
