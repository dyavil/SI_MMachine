#ifndef _MMACHINE_GAME_HPP_
#define _MMACHINE_GAME_HPP_

#include "player.hpp"

class Game{

public:
    //Game(){};
    Game(Player& p1, Player& p2, const int nbLap);
    ~Game(){};

    bool winRound(const int idPlayer);
    Mesh & getTourMesh(){return tourMesh;};
    Mesh & getWinMesh(){return winMesh;};

private:
    Player player1;
    Player player2;
    std::pair<int, int> score;
    int nbRound;
    int currentRound;
    Mesh winMesh;
    Mesh tourMesh;
    Mesh number;
};

#endif