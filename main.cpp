#include "terrain.hpp"
#include "controller.hpp"
#include "player.hpp"
#include "draw.h"
#include "orbiter.h"
#include "window.h"
#include "wavefront.h"
#include <stdio.h>
#include <ctime>


std::vector<Mesh> meshes;
Orbiter camera;
Mesh mesh;
Mesh car1;
Mesh car2;
Player player1;
Player player2;
Terrain t;
Brick b1;
Brick b2;
KeyboardController controller1(SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT);
KeyboardController controller2('z', 's', 'q', 'd');

int init( )
{
    t = Terrain(6, 6, Point(-20.f, -20.f, 0), Point(20.f, 20.f, 0));
    std::vector<Brick> tb = t.getBricks();
    camera = Orbiter();
    mesh = t.getMesh();
    camera.lookat(Point(-20.f, -20.f, 0), Point(20.f, 20.f, 0));
    car1 = read_mesh("MMachine/mmachine.obj");
    car1.default_color(Color(1.0f, 0.f, 0.f));
    car2 = read_mesh("MMachine/mmachine.obj");
    car2.default_color(Color(0.0f, 0.f, 1.f));

    Point car1min, car1max, car2min, car2max;
    car1.bounds(car1min, car1max);
    car2.bounds(car2min, car2max);
    player1.set_terrain(&t) ;
    player1.set_controller(&controller1) ;
    player1.spawn_at(Point(-18.5,17.5,0), Vector(1,0,0), car1min, car1max) ;
    player1.activate() ;

    player2.set_terrain(&t) ;
    player2.set_controller(&controller2) ;
    player2.spawn_at(Point(-18.5,18.5,0), Vector(1,0,0), car2min, car2max) ;
    player2.activate() ;


    for (unsigned int i = 0; i < tb.size(); ++i)
    {
    	meshes.push_back(tb[i].getMesh());
    }
    glClearDepth(1.f);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    return 0;   // renvoyer 0 ras, pas d'erreur, sinon renvoyer -1
}

// affichage
int draw( )
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

    for (unsigned int i = 0; i < meshes.size(); ++i)
    {
    	draw(meshes[i], camera);
    }

    Transform player1_pos = player1.transform(t.getBrickOn(player1.getPos()));
    draw(car1, player1_pos, camera);
    Transform player2_pos = player2.transform(t.getBrickOn(player2.getPos()));
    draw(car2, player2_pos, camera);
    //std::cout << "Ahead : " << t.whosAhead(player1.getPos(), player2.getPos()) << ", p1 sur " << t.getBrickOn(player1.getPos()).getPosition() << std::endl;
    //std::cout << "p1 in : " << player1.getBox().getPmin() << std::endl;

    return 1;   // on continue, renvoyer 0 pour sortir de l'application
}

// destruction des objets openGL
int quit( )
{
	for (unsigned int i = 0; i < meshes.size(); ++i)
    {
    	meshes[i].release();
    }
   	//mesh.release();
   	car1.release();
   	car2.release();
    return 0;   // ras, pas d'erreur
}


int main( int argc, char **argv )
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
}

