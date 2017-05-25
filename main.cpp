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
#include <stdio.h>
#include <ctime>


/*Orbiter camera;
Mesh mesh;
Mesh car1;
Mesh car2;
Player player1;
Player player2;
Terrain t;
Brick b1;
Brick b2;
GLuint shaderProgram;
KeyboardController controller1(SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT);
KeyboardController controller2('z', 's', 'q', 'd');*/


class Projet : public App
{
public:
    // constructeur : donner les dimensions de l'image, et eventuellement la version d'openGL.
    Projet( ) : App(1024, 640),
    controller1(SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT),
    controller2('z', 's', 'q', 'd')
    {}
    int init( )
    {
        //t = Terrain(1, Point(-48.f, -48.f, 0), Point(48.f, 48.f, 0));
        t = Terrain("field1.field", Point(-48.f, -48.f, 0), Point(48.f, 48.f, 0));

        grid= Mesh(GL_TRIANGLES);

        for(int z= -50; z < 52; z++)
        for(int x= -60; x < 60; x++)
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


        std::vector<Brick> tb = t.getBricks();
        camera = Orbiter();
        mesh = t.getMesh();
        camera.lookat(Point(-48.f, -48.f, 0), Point(48.f, 48.f, 0));
        car1 = read_mesh("MMachine/mmachine.obj");
        car1.default_color(Color(1.0f, 0.f, 0.f));
        car2 = read_mesh("MMachine/mmachine.obj");
        car2.default_color(Color(0.0f, 0.f, 1.f));

        Point car1min, car1max, car2min, car2max;
        car1.bounds(car1min, car1max);
        car2.bounds(car2min, car2max);
        player1.set_terrain(&t) ;
        player1.set_controller(&controller1) ;
        player1.spawn_at(Point(-20.5,20.5,0), Vector(1,0,0), car1min, car1max) ;
        player1.activate() ;

        player2.set_terrain(&t) ;
        player2.set_controller(&controller2) ;
        player2.spawn_at(Point(-20.5,21.5,0), Vector(1,0,0), car2min, car2max) ;
        player2.activate() ;

        mTexture0 = read_texture(0, "proj/projet/data/liege.jpg");
        shaderProgram= read_program("proj/projet/brick.glsl");
        program_print_errors(shaderProgram);

        glClearDepth(1.f);
        glDepthFunc(GL_LESS);
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

        program_uniform(shaderProgram, "mvpMatrix", mvp);
        program_uniform(shaderProgram, "modelMatrix", model);
        program_uniform(shaderProgram, "viewInvMatrix", view.inverse());
        float val = global_time();
        program_uniform(shaderProgram, "time", val);
        program_use_texture(shaderProgram, "texture0", 0, mTexture0);
        program_uniform(shaderProgram, "type", 2);
        grid.draw(shaderProgram);

        for (unsigned int i = 0; i < t.getBricks().size(); ++i)
        {
        	//draw(meshes[i], camera);
            program_uniform(shaderProgram, "type", 1);

            t.getBricks()[i].getMesh().draw(shaderProgram);
            program_uniform(shaderProgram, "type", 0);
            //*t.getBricks()[i].getBottomTransform()
            for (int j = 0; j < t.getBricks()[i].getBorders().size(); ++j)
            {
                program_uniform(shaderProgram, "transform", t.getBricks()[i].getTransforms()[j]);
                t.getBricks()[i].getBorders()[j].draw(shaderProgram);
            }
        }
        //draw(grid, camera);
        Transform player1_pos = player1.transform(t.getBrickOn(player1.getPos()));
        draw(car1, player1_pos, camera);
    	player1.collideOther(player2.getBox());
        Transform player2_pos = player2.transform(t.getBrickOn(player2.getPos()));
        draw(car2, player2_pos, camera);
    	player2.collideOther(player1.getBox());
        //std::cout << "Ahead : " << t.whosAhead(player1.getPos(), player2.getPos()) << ", p1 sur " << t.getBrickOn(player1.getPos()).getPosition() << std::endl;
        //std::cout << "p1 in : " << player1.getBox().getPmin() << std::endl;

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
            for (int j = 0; j < t.getBricks()[i].getBorders().size(); ++j)
            {
                t.getBricks()[i].getBorders()[j].release();
            }
        }
        return 0;   // ras, pas d'erreur
    }


    /*int main( int argc, char **argv )
    {
    	srand(time(NULL));
        // etape 1 : creer la fenetre
        Window window= create_window(1024, 640);
        if(window == NULL)
            return 1;       // erreur lors de la creation de la fenetre ou de l'init de sdl2

        // etape 2 : creer un contexte opengl pour pouvoir dessiner
        Context context= create_context(window);
        if(context == NULL)
            return 1;       // erreur lors de la creation du contexte opengl

        // etape 3 : creation des objets
        if(init() < 0)
        {
            printf("[error] init failed.\n");
            return 1;
        }
        printf("%s\n", "test1");
        // etape 4 : affichage de l'application, tant que la fenetre n'est pas fermee. ou que draw() ne renvoie pas 0
        run(window, draw);

        // etape 5 : nettoyage
        quit();
        release_context(context);
        release_window(window);
        return 0;
    }*/
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
};

int main( int argc, char **argv )
{
    Projet pr;
    pr.run();
    
    return 0;
}
