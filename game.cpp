#include "game.hpp"


Game::Game(Player& p1, Player& p2, int nbLap){
    player1 = p1;
    player2 = p2;
    currentRound = 0;
    nbRound = nbLap;
    score.first = 0;
    score.second = 0;
    winMesh = read_mesh("proj/projet/data/case111.obj");
}


bool Game::winRound(const int idPlayer){
    if(idPlayer == 1){
        score.first++;
    }
    else{
        score.second++;
    }
    
    if(currentRound + 1 < nbRound){
        currentRound++;
    }
    else{
        std::cout << "C'était le dernier tour FDP" << std::endl;
        return true;
    }
    return false;
}