#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Tile.h"

class Map
{
    public:

        Map();
        int getTileSize();
        int getMapSizeX();
        int getMapSizeY();
        Tile getTileMap(int numeroTile);
        void loadBackground(const std::string &background); //Chargement de la background
        void drawBackground(sf::RenderWindow &window); //Affiche de la background
        void newTile(const std::string &tileset, const std::string &file); //création de la tile map
        void drawTile(sf::RenderWindow &window, int nbtileset); //Affiche de la map tile
        void upgradeTile(const std::string &tileset, const std::string &file, int numeroTileSet); //upgrade de la map tile
        void deleteTile(); //supprime de la map tile

    private:

        int m_tileSize;
        int m_mapSizeX;
        int m_mapSizeY;
        int m_nbTileset;
        sf::Texture m_backgroundTexture;  //texture de fond
        sf::Sprite m_background; //Sprite de fond
        std::vector<Tile> m_mapTile;
};

#endif // MAP_H
