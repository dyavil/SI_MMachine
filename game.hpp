#ifndef _MMACHINE_GAME_HPP_
#define _MMACHINE_GAME_HPP_

#include "player.hpp"
#include "texture.h"

class Game{

public:
    //Game(){};
    Game(Player& p1, Player& p2, const int nbLap);
    ~Game(){};

    bool winRound(const int idPlayer);
    Mesh & getTourMesh(){return tourMesh;};
    Mesh & getWinMesh(){return winMesh;};
    Mesh & getCurrentTourMesh(){return currentTourMesh;};
    Mesh & getMaxTourMesh(){return maxTourMesh;};
    std::vector<Mesh> & getScoreMeshes(){return scoreMeshes;};
    GLuint getScoreTexture1(){return textScore1;};
    GLuint getScoreTexture2(){return textScore2;};
    GLuint getScoreTextureM(){return textScoreMid;};
    GLuint getScoreTextureTour(){return textTour;};
    GLuint getTextureTourMax(){return textTourMax;};
    GLuint getTextureTourCurrent(){return textTourCurrent;};

private:
    Player player1;
    Player player2;
    std::pair<int, int> score;
    int nbRound;
    int currentRound;
    Mesh winMesh;
    Mesh tourMesh;
    Mesh currentTourMesh;
    Mesh maxTourMesh;
    std::vector<Mesh> scoreMeshes;
    GLuint textScore1;
    GLuint textScore2;
    GLuint textScoreMid;
    GLuint textTour;
    GLuint textTourMax;
    GLuint textTourCurrent;
    int winner;

    void reloadScoreMesh();
};

#endif