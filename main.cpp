#include <iostream>
#include <random>

#include "renderer.h"

point3D rotateX(point3D p, float deg) {
    // 3D point rotation matrices
    float x = p.x;
    float y = p.y;
    float z = p.z;
    point3D res = {x, (y * cosf(deg) - ( z * sinf(deg))), (y * sinf(deg) + z * cosf(deg))};
    return res;
}

point3D rotateY(point3D p, float deg) {
    // 3D point rotation matrices
    float x = p.x;
    float y = p.y;
    float z = p.z;
    point3D res = {(x * cosf(deg)) + (z * sinf(deg)), y, ((-sinf(deg) * x) + (z * cosf(deg)))};
    return res;
}

point3D rotateZ(point3D p, float deg) {
    // 3D point rotation matrices
    float x = p.x;
    float y = p.y;
    float z = p.z;
    point3D res = {(x * cosf(deg) + (y * -sinf(deg))), (x * sinf(deg) + (y * cosf(deg))), z};
    return res;
}

int main() {
    Renderer* renderer = new Renderer(150, 50);
    point3D fur = { 0.5,  0.5, -.5};
    point3D ful = {-0.5,  0.5, -.5};
    point3D fdr = { 0.5, -0.5, -.5};
    point3D fdl = {-0.5, -0.5, -.5};
    point3D bur = { 0.5,  0.5,  .5};
    point3D bul = {-0.5,  0.5,  .5};
    point3D bdr = { 0.5, -0.5,  .5};
    point3D bdl = {-0.5, -0.5,  .5};
    
    float ro = 0.01;
    while(true) {
        fur = rotateX(rotateY(rotateZ(fur, ro), ro), ro);
        ful = rotateX(rotateY(rotateZ(ful, ro), ro), ro);
        fdr = rotateX(rotateY(rotateZ(fdr, ro), ro), ro);
        fdl = rotateX(rotateY(rotateZ(fdl, ro), ro), ro);
        bur = rotateX(rotateY(rotateZ(bur, ro), ro), ro);
        bul = rotateX(rotateY(rotateZ(bul, ro), ro), ro);
        bdr = rotateX(rotateY(rotateZ(bdr, ro), ro), ro);
        bdl = rotateX(rotateY(rotateZ(bdl, ro), ro), ro);
        ro += 0.01;
        renderer->Line3D(&ful, &fur);
        renderer->Line3D(&fur, &fdr);
        renderer->Line3D(&fdr, &fdl);
        renderer->Line3D(&fdl, &ful);
        renderer->Line3D(&fur, &bur);
        renderer->Line3D(&ful, &bul);
        renderer->Line3D(&fdr, &bdr);
        renderer->Line3D(&fdl, &bdl);
        renderer->Line3D(&bul, &bur);
        renderer->Line3D(&bur, &bdr);
        renderer->Line3D(&bdr, &bdl);
        renderer->Line3D(&bdl, &bul);


        system("cls");
        std::cout << renderer->Render() << std::endl;
        renderer->Clear();
    }

    return 0;

}