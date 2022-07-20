/* sketch.h */

#ifndef SKETCH_H
#define SKETCH_H

#include "core/math/vector2.h"
#include "core/os/os.h"
#include "core/project_settings.h"
#include "scene/2d/node_2d.h"
#include "servers/visual/visual_server_canvas.h"
#include "servers/visual_server.h"
#include "string.h"

class Sketch : public Node2D {
	GDCLASS(Sketch, Node2D);

	bool _candraw;

	RID _ci_rid;

protected:
	static void _bind_methods();

public:
	float WIDTH;
	float HEIGHT;

	// drawing functions
	void draw_on();
	void draw_off();
	bool is_drawing();

	// main RID
	RID get_rid();

	// utility functions
	void size(float x, float y);
	void clear();
	void background(Color color);
	float width();
	float height();

	// shape functions
	//void point(float x, float y, Color color);
	void point(Vector2 pos, Color color);

	//void circle(float x, float y, float size, Color color);
	void circle(Vector2 pos, float size, Color color);

	//void line(float x1, float y1, float x2, float y2, Color color, float width);
	void line(Vector2 pos1, Vector2 pos2, Color color, float width);

	//void _ready();
	//void _process();

	//void draw();

	//void _notification(int what){
	//    switch(what){
	//        case NOTIFICATION_PROCESS:
	//            _process();
	//            break;
	//        case NOTIFICATION_READY:
	//            _ready();
	//            break;
	//    }
	//}

	Sketch() {
		// turn drawing on
		draw_on();

		//WIDTH = ProjectSettings::get_singleton()->get_setting("display/window/size/width");
		//HEIGHT = ProjectSettings::get_singleton()->get_setting("display/window/size/height");

		// create the canvas_item canvas
		_ci_rid = VS::get_singleton()->canvas_item_create();
		// set the ci_rid parent to our canvas_item
		VS::get_singleton()->canvas_item_set_parent(get_rid(), get_canvas_item());
	}

	//----------------------------------------
};

#endif // SKETCH_H