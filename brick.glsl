#version 330

#ifdef VERTEX_SHADER
layout(location= 0) in vec3 position;
layout(location=1) in vec2 texcoord;   // attribut de sommet
layout(location= 2) in vec3 normal;     // attribut de sommet

uniform mat4 mvpMatrix;    // matrice passage du repere local au repere projectif homogene de la camera
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 viewInvMatrix;
uniform mat4 transform;
uniform vec3 cameraVertex;
uniform int type;
uniform float time;
uniform sampler2D texture0;
out float orientation;
out vec3 color;
out vec2 vertex_texcoord;
out float type1;

void main( )
{
    // obligation du vertex shader : calculer les coordonnées du sommet dans le repère projectif homogene de la camera
    
    vec3 n= mat3(modelMatrix) * vec3(0, 0, 1);
    vec3 newpos = position;
    vec4 posfin;
    if (type == 1)
    {
        color= vec3(1, 0.5, 0);
        /*vec3 newpos = position;
        newpos.z += (sin(newpos.y*5+time*0.005)+cos(newpos.x*5+time*0.005))*0.5;

        gl_Position= mvpMatrix * vec4(newpos, 1);*/
        gl_Position= mvpMatrix * vec4(position, 1);
        posfin = mvpMatrix * vec4(position, 1);
    }
    else if(type == 2){
        color= vec3(0, 0.5, 0.8);

        newpos.z += (sin(newpos.y*20+time*0.003)+cos(newpos.x*20+time*0.003))*0.5;

        gl_Position= mvpMatrix * vec4(newpos, 1);
    }
    else if(type == 3){
        color= vec3(1, 1, 1);
        gl_Position= mvpMatrix* transform * vec4(position, 1);
    }
    else{
        color= vec3(0, 1, 0);
        
        gl_Position= mvpMatrix  * transform * vec4(position, 1);
        posfin = mvpMatrix  * transform * vec4(position, 1);
        n= mat3(modelMatrix* transform ) * normal;
        if (position[1] < 0.3)
        {
            color= vec3(0, 0, 1);
        }
    }
    // normale de la surface, dans le repere monde
    
   if (type == 2)
   {
        vec3 a = vec3(position.x+1, position.y, 0);   
        vec3 b = vec3(position.x, position.y+1, 0);
        a.z += (sin(a.y*20+time*0.003)+cos(a.x*20+time*0.003))*0.5;
        b.z += (sin(b.y*20+time*0.003)+cos(b.x*20+time*0.003))*0.5;

        vec3 da = normalize(a-newpos);
        vec3 db = normalize(b-newpos);
        vec3 nn = cross(da, db);
        vec3 n = mat3(modelMatrix) * normalize(nn);
        // position de la camera dans le repere du monde
        vec4 sourceh = viewInvMatrix * vec4(0, 0, 0, 1);
       
        // rappel : mat4 * vec4 = vec4 homogne, pour retrouver le point / la direction reelle, il faut diviser par la 4ieme composante
        vec3 source = sourceh.xyz / sourceh.w;

        // direction entre le sommet et la source de lumiere
        vec3 l= normalize(source - newpos);
        // calculer le cosinus de l'angle entre les 2 directions, a verifier...
        orientation = max(0, dot(n, l));
   }
   else{
        // position de la camera dans le repere du monde
        vec4 sourceh= viewInvMatrix * vec4(0, 0, 0, 1);
       
        // rappel : mat4 * vec4 = vec4 homogne, pour retrouver le point / la direction reelle, il faut diviser par la 4ieme composante
        vec3 source = sourceh.xyz / sourceh.w;

        // direction entre le sommet et la source de lumiere
        vec3 l= normalize(source - position);
        // calculer le cosinus de l'angle entre les 2 directions, a verifier...
        orientation = dot(n, l);
    }
    type1 = type;
    vertex_texcoord = texcoord;

}
#endif

#ifdef FRAGMENT_SHADER
// recuperer l'orientation calculee dans le vertex shader... a completer
in float orientation;
in float sil;
in vec3 color;
in vec2 vertex_texcoord;
in float type1;
out vec4 fragment_color;
uniform sampler2D texture0;

void main( )
{
    // utiliser l'orientation pour modifier la couleur de base... a completer
    //vec3 MaterialAmbientColor = vec3(0.2,0.2,0.2) * vec3(1, 0.5, 0);
    if((type1 > 0.5 && type1 < 1.5) || type1 > 2.5){
        vec4 color= texture(texture0, vertex_texcoord)*orientation;
        gl_FragColor = color;
    }
    else if (type1 > 1.5 && type1 < 2.5)
    {
        gl_FragColor= /*vec4(MaterialAmbientColor, 1) + */(vec4(color, 1)*orientation); 
    }
    else {
    gl_FragColor= /*vec4(MaterialAmbientColor, 1) + */(vec4(color, 2)*(floor(orientation * 5)/5)); 
    }   // orange opaque
}
#endif