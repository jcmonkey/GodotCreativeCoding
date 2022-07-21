#include "sketch.h"

void Sketch::_bind_methods() {
	ClassDB::bind_method(D_METHOD("point", "x", "y"), &Sketch::point);
	ClassDB::bind_method(D_METHOD("circle", "x", "y", "size"), &Sketch::circle);
	ClassDB::bind_method(D_METHOD("line", "x1", "y1", "x2", "y2", "width"), &Sketch::line);
	ClassDB::bind_method(D_METHOD("get_rid"), &Sketch::get_rid);
	ClassDB::bind_method(D_METHOD("clear"), &Sketch::clear);
	ClassDB::bind_method(D_METHOD("background"), &Sketch::background);
	ClassDB::bind_method(D_METHOD("draw_on"), &Sketch::draw_on);
	ClassDB::bind_method(D_METHOD("draw_off"), &Sketch::draw_off);
	ClassDB::bind_method(D_METHOD("is_drawing"), &Sketch::is_drawing);
	ClassDB::bind_method(D_METHOD("size"), &Sketch::size);
	ClassDB::bind_method(D_METHOD("stroke","rgb"), &Sketch::stroke);
	ClassDB::bind_method(D_METHOD("width"), &Sketch::width);
	ClassDB::bind_method(D_METHOD("height"), &Sketch::height);
}

void Sketch::stroke(Color rgb){
	_color = rgb;
}

void Sketch::size(float x, float y) {
	//ProjectSettings::get_singleton()->set_setting("display/window/size/width",x);
	//ProjectSettings::get_singleton()->set_setting("display/window/size/height",y);
	OS::get_singleton()->set_window_size(Size2(x, y));

	//WIDTH = x;
	//HEIGHT = y;
}

float Sketch::height() {
	//return ProjectSettings::get_singleton()->get_setting("display/window/size/height");
	//return HEIGHT;
	Vector2 size = OS::get_singleton()->get_window_size();
	return size.y;
}

float Sketch::width() {
	//return ProjectSettings::get_singleton()->get_setting("display/window/size/width");
	//return WIDTH;
	Vector2 size = OS::get_singleton()->get_window_size();
	return size.x;
}

void Sketch::draw_on() {
	_candraw = true;
}
void Sketch::draw_off() {
	_candraw = false;
}
bool Sketch::is_drawing() {
	return _candraw;
}

//void Sketch::_ready(){}
//void Sketch::_process(){
//    //print_line("updating!!");
//   if (is_drawing()){
//
//    }
//}

RID Sketch::get_rid() {
	return _ci_rid;
}

void Sketch::clear() {
	VS::get_singleton()->canvas_item_clear(get_rid());
}

void Sketch::background(Color color) {
	VS::get_singleton()->set_default_clear_color(color);
}

//--------------------------------------------------------------------------------------

void Sketch::point(float x, float y) {
	if (is_drawing()) {
		Point2 pos = Point2(x,y);
		VS::get_singleton()->canvas_item_add_circle(get_rid(), pos, 1, _color);
	}
}

void Sketch::circle(float x, float y, float size) {
	if (is_drawing()) {
		Point2 pos = Point2(x,y);
		VS::get_singleton()->canvas_item_add_circle(get_rid(), pos, size, _color);
	}
}

void Sketch::line(float x1, float y1, float x2, float y2, float width) {
	if (is_drawing()) {
		Vector2 pos1 = Vector2(x1, y1);
		Vector2 pos2 = Vector2(x2, y2);
		VS::get_singleton()->canvas_item_add_line(get_rid(),
				pos1,
				pos2,
				_color,
				width, // width of line
				true); // antialiasing enabled
	}
}


//--------------------------------------------------------------------------------------