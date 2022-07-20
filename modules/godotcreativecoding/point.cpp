#include "point.h"


void Point::_bind_methods(){
    ClassDB::bind_method(D_METHOD("set_size"), &Point::set_size);
    ClassDB::bind_method(D_METHOD("stroke"), &Point::stroke);
}






