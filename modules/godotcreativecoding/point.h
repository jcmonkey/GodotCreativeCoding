/* point.h */

#ifndef POINT_H
#define POINT_H

#include "scene/2d/node_2d.h"
#include "string.h"

class Point : public Reference {
    GDCLASS(Point, Reference);
 
protected:
    static void _bind_methods();

public:
    Point2 pos;
    float size;
    Color color;

    void stroke(Color c){
        color = c;
    }

    void set_size(float s){
        size = s;
    }

    Point(){
        size = 1;
    }   

};

#endif // POINT_H