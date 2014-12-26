#pragma once
#include <string>
#include "CubeData.hpp"

class Game;
class GameUtilities{
    private:
        Game& m_game;
    public:
        GameUtilities(Game & game);
        void loadCubes(std::string const& filePath);
        void saveCubes(std::string const& filePath);
        void initVoxels();
        void configureVoxels();
        void configureVboVaoCubeData();
        void configureVboVaoCubeLight();
        void deleteVboVaoCubeData();
        void deleteVboVaoCubeCubeLight();
};
