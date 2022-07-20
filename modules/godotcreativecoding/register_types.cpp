/* register_types.cpp */

#include "register_types.h"

#include "core/class_db.h"
#include "point.h"
#include "sketch.h"

void register_godotcreativecoding_types() {
    ClassDB::register_class<Point>();
    ClassDB::register_class<Sketch>();
}

void unregister_godotcreativecoding_types() {
   // Nothing to do here in this example.
}