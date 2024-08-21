#include <iostream>
#include <random>

#include "renderer.h"

point3D rotateX(point3D p, float deg)
{
    // 3D point rotation matrices over X
    float x = p.x;
    float y = p.y;
    float z = p.z;
    point3D res = {x, (y * cosf(deg) - (z * sinf(deg))), (y * sinf(deg) + z * cosf(deg))};
    return res;
}

point3D rotateY(point3D p, float deg)
{
    // 3D point rotation matrices over Y
    float x = p.x;
    float y = p.y;
    float z = p.z;
    point3D res = {(x * cosf(deg)) + (z * sinf(deg)), y, ((-sinf(deg) * x) + (z * cosf(deg)))};
    return res;
}

point3D rotateZ(point3D p, float deg)
{
    // 3D point rotation matrices over Z
    float x = p.x;
    float y = p.y;
    float z = p.z;
    point3D res = {(x * cosf(deg) + (y * -sinf(deg))), (x * sinf(deg) + (y * cosf(deg))), z};
    return res;
}

point3D incPoint(point3D p, float val)
{
    
    // move a point along all axis by +val if positive or -val if negative
    

    if (p.x > 0.0)
    {
        p.x = .5 + val;
    }
    else if (p.x < 0.0)
    {
        p.x = -.5 - val;
    }

    if (p.y > 0.0)
    {
        p.y = .5 + val;
    }
    else if (p.y < 0.0)
    {
        p.y = -.5 - val;
    }

    if (p.z > 0.0)
    {
        p.z = .5 + val;
    }
    else if (p.z < 0.0)
    {
        p.z = -.5 - val;
    }

    return p;
}

int main()
{
    Renderer *renderer = new Renderer(150, 50);

    point3D cube1[] = {      
        { 0.25,  0.25, -.25},  // fur 0
        {-0.25,  0.25, -.25},  // ful 1
        { 0.25, -0.25, -.25},  // fdr 2
        {-0.25, -0.25, -.25},  // fdl 3
        { 0.25,  0.25,  .25},  // bur 4
        {-0.25,  0.25,  .25},  // bul 5
        { 0.25, -0.25,  .25},  // bdr 6
        {-0.25, -0.25,  .25},  // bdl 7
    };

    int EBO[] = {
        // tells which index of points should be connected together
        0, 1,
        1, 3,
        3, 2,
        0, 2,
        0, 4,
        1, 5,
        2, 6,
        3, 7,
        4, 5,
        5, 7,
        7, 6, 
        6, 4,
    };
    point3D cube2[] = {
        { 0.75,  0.75, -.75}, // fur 0
        {-0.75,  0.75, -.75}, // ful 1
        { 0.75, -0.75, -.75}, // fdr 2
        {-0.75, -0.75, -.75}, // fdl 3
        { 0.75,  0.75,  .75}, // bur 4
        {-0.75,  0.75,  .75}, // bul 5
        { 0.75, -0.75,  .75}, // bdr 6
        {-0.75, -0.75,  .75}, // bdl 7 
    };

    float frame = 0;
    float ro;
    while (true)
    {
        frame++;
        ro = sinf(frame / 10) * .3;

        // rotate and move
        for (int i = 0; i < 8; i++) {
            // rotate and move each point to make an animation
            // rotates by a value between -.3 and .3
            // moves between -75 and -25 or 25 and 75 for x, y and z
            cube1[i] = rotateX(rotateY(rotateZ(incPoint(cube1[i],  sin(frame / 10) / 4), ro), ro), ro); 
            cube2[i] = rotateX(rotateY(rotateZ(incPoint(cube2[i], -sin(frame / 10) / 4), ro), ro), ro); 
        }

        for (int i = 0; i < 24; i+=2) {
            // draw each line by connecting each vertex index of each cube from EBO 
            renderer->Line3D(&cube1[EBO[i]], &cube1[EBO[i+1]]);
            renderer->Line3D(&cube2[EBO[i]], &cube2[EBO[i+1]]);
        }

        // connect both cubes
        for (int i = 0; i < 8; i++){
            renderer->Line3D(&cube1[i], &cube2[i]);
        }

        system("cls"); // clear console system("clear"); for linux
        std::cout << renderer->Render() << std::endl; // print the rendered string
        renderer->Clear(); // clear the buffer
    }

    return 0;
}
