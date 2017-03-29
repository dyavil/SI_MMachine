#include "terrain.hpp"
#include "draw.h"
#include "orbiter.h"
#include "window.h"
#include "wavefront.h"
#include <stdio.h>


std::vector<Mesh> meshes;
Orbiter camera;
Mesh mesh;

int init( )
{

    Terrain t = Terrain(32, 31, Point(-10, -10, 0), Point(10, 10, 0));
    std::vector<Brick> tb = t.getBricks();
    camera = Orbiter();
    mesh =Mesh(GL_TRIANGLES);
    int a = mesh.vertex(-1, -1, 0);
    int b = mesh.vertex(-1, 1, 0);
    int c = mesh.vertex(1, 1, 0);
    int d = mesh.vertex(1, -1, 0);
    mesh.triangle(a, b, c);
    mesh.triangle(c, d, a);
    Point pmin, pmax;
    mesh.bounds(pmin, pmax);
    std::cout << "bound " << pmin << ", " << pmax << std::endl;
    camera.lookat(Point(-10, -10, 0), Point(10, 10, 0));
    for (int i = 0; i < tb.size(); ++i)
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

     for (int i = 0; i < meshes.size(); ++i)
    {
    	draw(meshes[i], camera);
    }
    /*static float angle= 0;      // il faudrait declarer angle comme variable globale...
        if(key_state('j'))
            angle= angle + 3;
        if(key_state('k'))1
            angle= angle - 3;
        
        Transform T= RotationY( angle );
        draw(torse, T, Identity(), Identity());*/

    return 1;   // on continue, renvoyer 0 pour sortir de l'application
}

// destruction des objets openGL
int quit( )
{
	for (int i = 0; i < meshes.size(); ++i)
    {
    	meshes[i].release();
    }
   	//mesh.release();
    return 0;   // ras, pas d'erreur
}


int main( int argc, char **argv )
{
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

