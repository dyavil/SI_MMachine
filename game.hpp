#ifndef _MMACHINE_GAME_HPP_
#define _MMACHINE_GAME_HPP_

#include "player.hpp"

class Game{

public:
    //Game(){};
    Game(Player& p1, Player& p2, int nbLap);
    ~Game(){};

    void winRound(int idPlayer);

private:
    Player player1;
    Player player2;
    std::pair<int, int> score;
    int nbRound;
    int currentRound;
};

#endif