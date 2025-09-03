#include "Map.h"

Map::Map()
{
    m_tileSize=32;
    m_nbTileset=0;
}

int Map::getTileSize()
{
    return m_tileSize;
}

int Map::getMapSizeX()
{
    return m_mapSizeX;
}

int Map::getMapSizeY()
{
    return m_mapSizeY;
}

Tile Map::getTileMap(int numeroTile)
{
    if(numeroTile <= m_nbTileset)
    {
        return m_mapTile[numeroTile];
    }
}

void Map::loadBackground(const std::string &background)
{
    if(!m_backgroundTexture.loadFromFile(background))
    {
        std::cout << "Erreur chargement de la background" << std::endl;
    }
    else
    {
       m_background.setTexture(m_backgroundTexture);
    }
}

void Map::drawBackground(sf::RenderWindow &window)
{
    window.draw(m_background);
}

void Map::newTile(const std::string &tileset, const std::string &file)
{
    std::ifstream fileTile(file.c_str());

    if(fileTile)
    {
        fileTile >> m_mapSizeX;
        fileTile >> m_mapSizeY;

        int level[m_mapSizeX*m_mapSizeY];

        for(int i=0;i<m_mapSizeX*m_mapSizeY;i++)
        {
            fileTile >> level[i];
        }

         Tile tile;
         tile.loadTileMap(tileset, sf::Vector2u(m_tileSize,m_tileSize), level, m_mapSizeX, m_mapSizeY);
         m_mapTile.push_back(tile);
         m_nbTileset++;
    }
    else
    {
        std::cout << "Erreur ouverture fichier de la tuile map" << std::endl;
    }
}

void Map::drawTile(sf::RenderWindow &window, int nbtileset)
{
    if(nbtileset <= m_nbTileset)
    {
        window.draw(m_mapTile[nbtileset]);
    }
}

void Map::upgradeTile(const std::string &tileset, const std::string &file, int numeroTileSet)
{
    std::ifstream fileTile(file.c_str());

    if(fileTile)
    {
        fileTile >> m_mapSizeX;
        fileTile >> m_mapSizeY;

        int level[m_mapSizeX*m_mapSizeY];

        for(int i=0;i<m_mapSizeX*m_mapSizeY;i++)
        {
            fileTile >> level[i];
        }

         Tile tile;
         tile.loadTileMap(tileset, sf::Vector2u(m_tileSize,m_tileSize), level, m_mapSizeX, m_mapSizeY);
         m_mapTile[numeroTileSet]=tile;
    }
    else
    {
        std::cout << "Erreur ouverture fichier de la tuile map" << std::endl;
    }
}

void Map::deleteTile()
{
     m_mapTile.pop_back();
}
