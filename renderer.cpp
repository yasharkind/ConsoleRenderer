#include "renderer.h"

#define FOV 10

#pragma region helper functions

template<typename T>
void swap(T a, T b) {
    *a ^= *b; // a turns into a key for b
    *b ^= *a; // b turns into a with the key and also becomes a key for a at the same time
    *a ^= *b; // a turns into b with the key
}

point2D castPoint(point3D *point) {
    // x = (X * FOV) / (Z + FOV)
    // y = (Y * FOV) / (Y + FOV)

    // weak projection formula easy but a bit inaccurate
    float x = (point->x * FOV) / (point->z + FOV);
    float y = (point->y * FOV) / (point->z + FOV);

    point2D res = {x, y};
    return res;
}

#pragma endregion

#pragma region public methods

Renderer::Renderer(int width, int height) {
    this->width = width;
    this->height = height;

    for (int i = 0; i < height; i++) {
        // make space in memory for the buffer
        buffer.push_back(std::vector<bool>());
        for (int j = 0; j < width; j++) {
            buffer.at(i).push_back(0);
        }
    }
}

void Renderer::Point2D(point2D *point) {
    // draw a 2D point by making buffer[y][x] = true
    float x = point->x;
    float y = point->y;
    
    try {
        this->buffer.at(this->ToPixels(y, height)).at(this->ToPixels(x, width)) = 1;
    } catch (std::out_of_range e) {}
}

void Renderer::Line2D(point2D *point1, point2D *point2) {
    // some weird algorithm i came up with for drawing a 2d line over a pixelated screen
    // lets say the line is vertical, then it has to break y2 - y1 times if y2 > y1
    // and to calcualte where it needs to break we do n = (x2 - x1) / (y2 - y1)
    // so the y value of the line should go up by 1 every nth pixel
    // has some bugs for very high slope values but im too lazy to fix

    int x1 = ToPixels(point1->x, width);
    int y1 = ToPixels(point1->y, height);

    int x2 = ToPixels(point2->x, width);
    int y2 = ToPixels(point2->y, height);

    if (x1 > x2){

        swap<int*>(&x1, &x2);
        
        swap<int*>(&y1, &y2);
    }


    if (x2 == x1) {
        if (y1 > y2) {
            swap<int*>(&y1, &y2);
        }
        for (int j = y1; j < y2; j++)
        try{
            buffer.at(j).at(x1) = 1;
        }catch(std::out_of_range e){}
        return;
    }

    float slope = 1;
    if (x1 != x2)
        slope = (y1 - y2) / (x1 - x2);

    
    int sign = 1;
    if (slope > 1) sign = -1;
    for (int i = x1; i < x2; i++) {
        try{
        this->buffer.at(y1 + sign * (floorf((float((i - x1)) / float((x2 - x1))) * (y2 - y1))) - 1).at(i) = 1;
        } catch(std::out_of_range e){}
    }


}

void Renderer::Point3D(point3D *point) {
    point2D p = castPoint(point);
    Point2D(&p);
}

void Renderer::Line3D(point3D *point1, point3D *point2) {
    point2D p1 = castPoint(point1);
    point2D p2 = castPoint(point2);
    Line2D(&p1, &p2);
}

void Renderer::Clear() {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            buffer.at(y).at(x) = 0;
        }
    }
}

std::string Renderer::Render() {
    std::string res = "";
    
    for (std::vector i : this->buffer) {
        for (bool j : i) {
            if (!j)
                res.append(" ");
            else {
                res.append("#");        
            }
        }
        res.append("\n");
    }

    return res;
}

#pragma endregion

#pragma region private methods

int Renderer::ToPixels(float n, int s) {

    // -1 ... 1  -> 0 ... w
    return floorf((s + ( s * n)) / 2);
}

float Renderer::Normalize(int n, int s) {

    // 0 ... w -> -1 ... 1
    return (2 * n / s) - 1;
}
#pragma endregion
