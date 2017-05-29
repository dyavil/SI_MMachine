#include "game.hpp"


Game::Game(Player& p1, Player& p2, int nbLap){
    player1 = p1;
    player2 = p2;
    currentRound = 0;
    nbRound = nbLap;
    score.first = 0;
    score.second = 0;
    winMesh = read_mesh("proj/projet/data/win.obj");
    winner = -1;
    std::string s1 = "proj/projet/data/t"+std::to_string(nbLap)+".png";
    textScore1 = read_texture(0, "proj/projet/data/s0.png");
    textScore2 = read_texture(0, "proj/projet/data/s0.png");
    textScoreMid = read_texture(0, "proj/projet/data/sm.png");
    textTour = read_texture(0, "proj/projet/data/tourC.png");
    textTourMax = read_texture(0, s1.c_str());
    textTourCurrent = read_texture(0, "proj/projet/data/t0.png");

    Mesh scoreMesh = Mesh(GL_TRIANGLES);
    scoreMesh.texcoord(0, 0);
    unsigned int a = scoreMesh.vertex(p1.getPos().x-5, p1.getPos().y-5, 4);
    scoreMesh.texcoord(1, 1);
    unsigned int b = scoreMesh.vertex(p1.getPos().x+5, p1.getPos().y+5, 4);
    scoreMesh.texcoord(1, 0);
    unsigned int c = scoreMesh.vertex(p1.getPos().x-5, p1.getPos().y+5, 4);
    scoreMesh.texcoord(0, 1);
    unsigned int d = scoreMesh.vertex(p1.getPos().x+5, p1.getPos().y-5, 4);
    scoreMesh.triangle(a, b, c);
    scoreMesh.triangle(a, d, b);

    Mesh scoreMesh1 = Mesh(GL_TRIANGLES);
    scoreMesh1.texcoord(0, 0);
    a = scoreMesh1.vertex(p1.getPos().x-5, p1.getPos().y-17, 4);
    scoreMesh1.texcoord(1, 1);
    b = scoreMesh1.vertex(p1.getPos().x+5, p1.getPos().y-7, 4);
    scoreMesh1.texcoord(1, 0);
    c = scoreMesh1.vertex(p1.getPos().x-5, p1.getPos().y-7, 4);
    scoreMesh1.texcoord(0, 1);
    d = scoreMesh1.vertex(p1.getPos().x+5, p1.getPos().y-17, 4);
    scoreMesh1.triangle(a, b, c);
    scoreMesh1.triangle(a, d, b);

    Mesh scoreMesh2 = Mesh(GL_TRIANGLES);
    scoreMesh2.texcoord(0, 0);
    a = scoreMesh2.vertex(p1.getPos().x-5, p1.getPos().y-7, 4);
    scoreMesh2.texcoord(1, 1);
    b = scoreMesh2.vertex(p1.getPos().x+5, p1.getPos().y-5, 4);
    scoreMesh2.texcoord(1, 0);
    c = scoreMesh2.vertex(p1.getPos().x-5, p1.getPos().y-5, 4);
    scoreMesh2.texcoord(0, 1);
    d = scoreMesh2.vertex(p1.getPos().x+5, p1.getPos().y-7, 4);
    scoreMesh2.triangle(a, b, c);
    scoreMesh2.triangle(a, d, b);

    scoreMeshes.push_back(scoreMesh);
    scoreMeshes.push_back(scoreMesh1);
    scoreMeshes.push_back(scoreMesh2);

    tourMesh = Mesh(GL_TRIANGLES);
    tourMesh.texcoord(0, 1);
    a = tourMesh.vertex(p1.getPos().x-5, p1.getPos().y-5, 4);
    tourMesh.texcoord(1, 0);
    b = tourMesh.vertex(p1.getPos().x+5, p1.getPos().y+15, 4);
    tourMesh.texcoord(1, 1);
    c = tourMesh.vertex(p1.getPos().x-5, p1.getPos().y+15, 4);
    tourMesh.texcoord(0, 0);
    d = tourMesh.vertex(p1.getPos().x+5, p1.getPos().y-5, 4);
    tourMesh.triangle(a, b, c);
    tourMesh.triangle(a, d, b);

    currentTourMesh = Mesh(GL_TRIANGLES);
    currentTourMesh.texcoord(0, 1);
    a = currentTourMesh.vertex(p1.getPos().x-5, p1.getPos().y-5, 4.1);
    currentTourMesh.texcoord(1, 0);
    b = currentTourMesh.vertex(p1.getPos().x+5, p1.getPos().y+5, 4.1);
    currentTourMesh.texcoord(1, 1);
    c = currentTourMesh.vertex(p1.getPos().x-5, p1.getPos().y+5, 4.1);
    currentTourMesh.texcoord(0, 0);
    d = currentTourMesh.vertex(p1.getPos().x+5, p1.getPos().y-5, 4.1);
    currentTourMesh.triangle(a, b, c);
    currentTourMesh.triangle(a, d, b);

    maxTourMesh = Mesh(GL_TRIANGLES);
    maxTourMesh.texcoord(0, 1);
    a = maxTourMesh.vertex(p1.getPos().x-5, p1.getPos().y-5, 4.1);
    maxTourMesh.texcoord(1, 0);
    b = maxTourMesh.vertex(p1.getPos().x+5, p1.getPos().y+5, 4.1);
    maxTourMesh.texcoord(1, 1);
    c = maxTourMesh.vertex(p1.getPos().x-5, p1.getPos().y+5, 4.1);
    maxTourMesh.texcoord(0, 0);
    d = maxTourMesh.vertex(p1.getPos().x+5, p1.getPos().y-5, 4.1);
    maxTourMesh.triangle(a, b, c);
    maxTourMesh.triangle(a, d, b);
}


bool Game::winRound(const int idPlayer){
    if(idPlayer == 1){
        score.first++;
    }
    else{
        score.second++;
    }
    reloadScoreMesh();
    if(currentRound + 1 < nbRound){
        currentRound++;
    }
    else{
        std::cout << "C'était le dernier tour FDP" << std::endl;
        if (score.first > score.second)
        {
            winner = 1;
        }
        else if (score.first < score.second)
        {
            winner = 2;
        }
        else winner = 0;
        return true;
    }
    return false;
}


void Game::reloadScoreMesh(){
    std::string s1 = "proj/projet/data/s"+std::to_string(score.first)+".png";
    std::string s2 = "proj/projet/data/s"+std::to_string(score.second)+".png";
    std::string s3 = "proj/projet/data/t"+std::to_string(currentRound+1)+".png";
    textScore1 = read_texture(0, s1.c_str());
    textScore2 = read_texture(0, s2.c_str());
    textTourCurrent = read_texture(0, s3.c_str());
}