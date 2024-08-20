#ifndef RENDERER_H
#define RENDERER_H


#include <vector>
#include <string>
#include <iostream>
#include <math.h>

typedef struct {
    float x;
    float y;
} point2D;

typedef struct {
    float x;
    float y;
    float z;
} point3D;

class Renderer {
    public:
        Renderer(int width, int height);
        
        void Point2D(point2D *point);
        void Line2D(point2D *point1, point2D *point2);
        void Point3D(point3D *point);
        void Line3D(point3D *point1, point3D *point2);
        void Clear();
        std::string Render();

    private:
        int width;
        int height;
        std::vector<std::vector<bool>> buffer;
        
        static int ToPixels(float n, int s);
        static float Normalize(int n, int s);
        // int ToPixels(float x, float y); // need to be vector, to lazy to implement and will have the same drawbacks
        // float Normalize(int x, int y); 
};

#endif