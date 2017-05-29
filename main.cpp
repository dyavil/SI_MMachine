#include "terrain.hpp"
#include "controller.hpp"
#include "player.hpp"
#include "draw.h"
#include "orbiter.h"
#include "window.h"
#include "program.h"
#include "uniforms.h"
#include "wavefront.h"
#include "texture.h"
#include "mat.h"
#include "app.h" 
#include "game.hpp"
#include <stdio.h>
#include <ctime>



class Projet : public App
{
public:
    // constructeur
    Projet( ) : App(1024, 640),
    controller1(SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT),
    controller2('z', 's', 'q', 'd'),
    game(player1, player2, 3)
    {}
    int init( )
    {
        //on créer le terrain à partir d'un fichier
        //t = Terrain(1, Point(-48.f, -48.f, 0), Point(48.f, 48.f, 0));
        t = Terrain("field1.field");

        //création du background, "l'eau"
        grid= Mesh(GL_TRIANGLES);

        for(int z= -80; z < 72; z++)
        for(int x= -80; x < 80; x++)
        {
            //grid.normal(0, 0, 1);
            grid.vertex(x, z, -1);
            //grid.normal(0, 0, 1);
            grid.vertex(x+1, z, -1);
            //grid.normal(0, 0, 1);
            grid.vertex(x+1, z+1, -1);
           
            //grid.normal(0, 0, 1);
            grid.vertex(x, z, -1);
            //grid.normal(0, 0, 1);
            grid.vertex(x+1, z+1,-1);
            //grid.normal(0, 0, 1);
            grid.vertex(x, z+1, -1);
        }

        //initialisation des meshs
        std::vector<Brick> tb = t.getBricks();
        camera = Orbiter();
        mesh = t.getMesh();
        camera.lookat(t.getPmin(), t.getPmax());
        car1 = read_mesh("MMachine/mmachine.obj");
        car1.default_color(Color(1.0f, 0.f, 0.f));
        car2 = read_mesh("MMachine/mmachine.obj");
        car2.default_color(Color(0.0f, 0.f, 1.f));

        //on prépare les voitures sur le terrain
        car1.bounds(car1min, car1max);
        car2.bounds(car2min, car2max);
        player1.set_terrain(&t) ;
        player1.set_controller(&controller1) ;
        player1.spawn_at(Point(t.getSpawn().x, t.getSpawn().y-1, 0), Vector(1,0,0), car1min, car1max) ;
        player1.activate() ;

        player2.set_terrain(&t) ;
        player2.set_controller(&controller2) ;
        player2.spawn_at(Point(t.getSpawn().x, t.getSpawn().y+1, 0), Vector(1,0,0), car2min, car2max) ;
        player2.activate() ;


        mTexture0 = read_texture(0, "proj/projet/data/liege.jpg");
        shaderProgram= read_program("proj/projet/brick.glsl");
        program_print_errors(shaderProgram);

        glClearDepth(1.f);
        glDepthFunc(GL_LESS);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);
        return 0;   // renvoyer 0 ras, pas d'erreur, sinon renvoyer -1
    }

    // affichage
    int render( )
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        int mx, my;
        unsigned int mb= SDL_GetRelativeMouseState(&mx, &my);
        
        //draw(mesh, camera);
      
       // deplace la camera
        if(mb & SDL_BUTTON(1))              // le bouton gauche est enfonce
           // tourne autour de l'objet
            camera.rotation(mx, my);
        else if(mb & SDL_BUTTON(3))         // le bouton droit est enfonce
               // approche / eloigne l'objet
               camera.move(mx);

        glUseProgram(shaderProgram);


        Transform model= Identity();
        Transform view= camera.view();
        Transform projection= camera.projection(window_width(), window_height(), 45);
        Transform mvp= projection * view * model;

        //passge des parametres au shader
        program_uniform(shaderProgram, "mvpMatrix", mvp);
        program_uniform(shaderProgram, "modelMatrix", model);
        program_uniform(shaderProgram, "viewInvMatrix", view.inverse());
        float val = global_time();
        program_uniform(shaderProgram, "time", val);
        program_use_texture(shaderProgram, "texture0", 0, mTexture0);
        program_uniform(shaderProgram, "type", 2);
        grid.draw(shaderProgram);
        
        //application du shader sur chaque brick
        //le comportement du shader varie en fonction du ârametre type
        for (unsigned int i = 0; i < t.getBricks().size(); ++i)
        {
        	//draw(meshes[i], camera);
            program_uniform(shaderProgram, "type", 1);

            t.getBricks()[i].getMesh().draw(shaderProgram);
            program_uniform(shaderProgram, "type", 0);
            //*t.getBricks()[i].getBottomTransform()
            for (unsigned int j = 0; j < t.getBricks()[i].getBorders().size(); ++j)
            {
                program_uniform(shaderProgram, "transform", t.getBricks()[i].getTransforms()[j]);
                t.getBricks()[i].getBorders()[j].draw(shaderProgram);
            }
        }
        
        //on dessine les voitures à chaque frame
        Transform player1_pos = player1.transform(t.getBrickOn(player1.getPos()));

        Transform scoreTrans = Translation(player1.getPos().x-28, player1.getPos().y-17, 0)*RotationZ(90)*Scale(0.5, 0.5, 0.5);
        Transform tourTrans = Translation(player1.getPos().x+22, player1.getPos().y+15, 0)*RotationZ(-90)*Scale(0.4, 0.4, 0.4);
        Transform currentTourTrans = Translation(player1.getPos().x+22.5, player1.getPos().y+14, 0)*RotationZ(-90)*Scale(0.2, 0.2, 0.5);
        Transform maxTourTrans = Translation(player1.getPos().x+25, player1.getPos().y+14, 0)*RotationZ(-90)*Scale(0.2, 0.2, 0.5);

        program_uniform(shaderProgram, "type", 3);
        program_use_texture(shaderProgram, "texture0", 0, game.getScoreTexture1());
        

        //draw(car1, player1_pos, camera);
    	player1.collideOther(player2.getBox());
        Transform player2_pos = player2.transform(t.getBrickOn(player2.getPos()));
        //draw(car2, player2_pos, camera);
    	player2.collideOther(player1.getBox());
        
        



        //booleen vrai quand un joueur a gagné
        static bool victor = false;
        float distP = 0.0;
        

        if(!victor){
            //on test d'abord si les deux joueurs sont toujours sur le terrain
            if(t.getBrickOn(player2.getPos()).getPosition() == -1){
                victor = game.winRound(1);
                newturn();
            }
            if(t.getBrickOn(player1.getPos()).getPosition() == -1){
                victor = game.winRound(2);
                newturn();
            }

            //puis on regarde si le deuxieme est encore visible par la camera
            distP = distance(player1.getPos(), player2.getPos());
            if (t.whosAhead(player1.getPos(), player2.getPos()) == 1)
            {

                if (t.getBrickOn(player1.getPos()).getIsEnd())
                {
                    std::cout << "Player 1 win " << std::endl;
                    victor = game.winRound(1);
                    newturn();
                }
                camera.lookat(Point(player1.getPos().x-17.0, player1.getPos().y-17.0, 0) , Point(player1.getPos().x+17.0, player1.getPos().y+17.0, 0));
                if (distance(player1.getPos(), Point(player1.getPos().x-17.0, player1.getPos().y-17.0, 0))+4 < distP){
                    std::cout << "p2 out" << std::endl;
                    victor = game.winRound(1);
                    newturn();
                }
                
            }else{
                scoreTrans = Translation(player2.getPos().x-28, player2.getPos().y-17, 0)*RotationZ(90)*Scale(0.5, 0.5, 0.5);
                tourTrans = Translation(player2.getPos().x+22, player2.getPos().y+15, 0)*RotationZ(-90)*Scale(0.4, 0.4, 0.4);
                currentTourTrans = Translation(player2.getPos().x+22.5, player2.getPos().y+14, 0)*RotationZ(-90)*Scale(0.2, 0.2, 0.5);
                maxTourTrans = Translation(player2.getPos().x+25, player2.getPos().y+14, 0)*RotationZ(-90)*Scale(0.2, 0.2, 0.5);


                if (t.getBrickOn(player2.getPos()).getIsEnd())
                {
                    std::cout << "Player 2 win " << std::endl;
                    victor = game.winRound(2);
                    newturn();
                }
                camera.lookat(Point(player2.getPos().x-17.0, player2.getPos().y-17.0, 0) , Point(player2.getPos().x+17.0, player2.getPos().y+17.0, 0));
                if (distance(player2.getPos(), Point(player2.getPos().x-17.0, player2.getPos().y-17.0, 0))+4 < distP){
                    std::cout << "p1 out" << std::endl;
                    victor = game.winRound(2);
                    newturn();
                }
            }
            program_use_texture(shaderProgram, "texture0", 0, game.getScoreTexture1());
            program_uniform(shaderProgram, "transform", scoreTrans);
            game.getScoreMeshes()[0].draw(shaderProgram);
            program_use_texture(shaderProgram, "texture0", 0, game.getScoreTexture2());
            game.getScoreMeshes()[1].draw(shaderProgram);
            program_use_texture(shaderProgram, "texture0", 0, game.getScoreTextureM());
            game.getScoreMeshes()[2].draw(shaderProgram);
            program_uniform(shaderProgram, "transform", tourTrans);
            program_use_texture(shaderProgram, "texture0", 0, game.getScoreTextureTour());
            game.getTourMesh().draw(shaderProgram);
            program_uniform(shaderProgram, "transform", currentTourTrans);
            program_use_texture(shaderProgram, "texture0", 0, game.getTextureTourCurrent());
            game.getCurrentTourMesh().draw(shaderProgram);
            program_uniform(shaderProgram, "transform", maxTourTrans);
            program_use_texture(shaderProgram, "texture0", 0, game.getTextureTourMax());
            game.getMaxTourMesh().draw(shaderProgram);
        }
        //en cas de victoire
        else
        {
            camera.lookat(t.getPmin(), t.getPmax());
            program_uniform(shaderProgram, "transform", Scale(5, 2.5, 2));
            program_use_texture(shaderProgram, "texture0", 0, game.getTextWin());
            game.getWinMesh().draw(shaderProgram);
            if (key_state('n'))
            {
                game.reinit();
                victor = false;
            }
        }

        draw(car1, player1_pos, camera);
        draw(car2, player2_pos, camera);
        //std::cout << victor << std::endl;
        return 1;   // on continue, renvoyer 0 pour sortir de l'application
    }

    // destruction des objets openGL
    int quit( )
    {
       	//mesh.release();
       	car1.release();
       	car2.release();
        grid.release();
        release_program(shaderProgram);
        for (unsigned int i = 0; i < t.getBricks().size(); ++i)
        {
            //draw(meshes[i], camera);
            t.getBricks()[i].getMesh().release();
            for (unsigned int j = 0; j < t.getBricks()[i].getBorders().size(); ++j)
            {
                t.getBricks()[i].getBorders()[j].release();
            }
        }
        for (unsigned int i = 0; i < game.getScoreMeshes().size(); ++i)
        {
            game.getScoreMeshes()[i].release();
        }
        game.getMaxTourMesh().release();
        game.getCurrentTourMesh().release();
        game.getTourMesh().release();
        return 0;   // ras, pas d'erreur
    }

    //méthode qui remet les joueur a la position de départ
    void newturn(){
        player1.spawn_at(Point(t.getSpawn().x, t.getSpawn().y-1, 0), Vector(1,0,0), car1min, car1max) ;
        player1.activate() ;
        player2.spawn_at(Point(t.getSpawn().x, t.getSpawn().y+1, 0), Vector(1,0,0), car2min, car2max) ;
        player2.activate() ;
    }

protected:
    Orbiter camera;
    
    Mesh mesh;
    Mesh grid;
    Mesh car1;
    Mesh car2;
    Player player1;
    Player player2;
    Terrain t;
    Brick b1;
    Brick b2;
    GLuint mTexture0;
    GLuint shaderProgram;
    KeyboardController controller1;
    KeyboardController controller2;
    Game game;

    Point car1min, car1max, car2min, car2max;
};

int main( int argc, char **argv )
{
    Projet pr;
    pr.run();
    
    return 0;
}
