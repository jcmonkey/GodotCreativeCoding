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
#include "core/math/random_number_generator.h"
#include "core/math/rect2.h"
#include "core/math/math_defs.h"
#include "core/math/math_funcs.h"

class Sketch : public Node2D {
	GDCLASS(Sketch, Node2D);

	RandomNumberGenerator _r;

	// state 
	bool _candraw;
	bool _canfill;

	float _stroke_width;

	Color _stroke_color;
	Color _color;

	float _mouse_x;
	float _mouse_y;

	Vector<RID> items;
	

protected:
	static void _bind_methods();

public:


	// drawing functions
	void draw_on();
	void draw_off();
	bool is_drawing();
	void clear();
	void stroke(Color color);
	void stroke_width(float width);
	void fill(Color color);
	void no_fill();

	// utility functions
	void size(float x, float y);
	float mouse_x();
	float mouse_y();

	void background(Color color);
	
	float width();
	float height();
	
	void random_color();
	Color r_random_color();
	float random_x();
	float random_y();
	float map(float value, float istart, float istop, float ostart, float ostop);

	// shape functions

	void point(float x, float y);

	void circle(float x, float y, float size);
	void circle_empty(float h, float k, float r);

	void ellipse(float x, float y, float width, float height);
	void ellipse_empty(float h, float k, float width,float height);
	
	void line(float x1, float y1, float x2, float y2, float width);

	void rect(float x, float y, float width, float height, bool center);
	void rect_empty(float ltx, float lty, 
						float lbx, float lby,
						float rtx, float rty, 
						float rbx, float rby);

	void polyline(Vector<Vector2> points,Vector<Color> colors,bool antialiased);


	//void ready();
	void process();

	//void draw();

	void _notification(int what){
	    switch(what){
	        case NOTIFICATION_PROCESS:
	            process();
	            break;
	    }
	}

	Sketch() {
		ProjectSettings::get_singleton()->set_setting("display/window/size/resizable",false);

		// turn drawing on
		draw_on();

		_canfill = false;
		_stroke_width=1.0;
		_stroke_color = Color(1.0,1.0,1.0);
	}

	//----------------------------------------
};

#endif // SKETCH_H