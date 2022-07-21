#include "sketch.h"

void Sketch::random_color(){
	_r.randomize();
	float r = map(_r.randi_range(0,255),0,255,0.0,1.0);
	_r.randomize();
	float g = map(_r.randi_range(0,255),0,255,0.0,1.0);
	_r.randomize();
	float b = map(_r.randi_range(0,255),0,255,0.0,1.0);
	_color = Color(r,g,b);
}

float Sketch::random_x(){
	_r.randomize();
	return _r.randi_range(0,width());
}

float Sketch::random_y(){
	_r.randomize();
	return _r.randi_range(0,height());
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

void Sketch::background(Color c) {
	VS::get_singleton()->set_default_clear_color(c);
}

float Sketch::map(float value, float istart, float istop, float ostart, float ostop) {
    return ostart + (ostop - ostart) * ((value - istart) / (istop - istart));
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

void Sketch::_bind_methods() {
	ClassDB::bind_method(D_METHOD("point"), &Sketch::point);
	ClassDB::bind_method(D_METHOD("circle"), &Sketch::circle);
	ClassDB::bind_method(D_METHOD("line"), &Sketch::line);
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
	ClassDB::bind_method(D_METHOD("random_color"), &Sketch::random_color);
	ClassDB::bind_method(D_METHOD("random_x"), &Sketch::random_x);
	ClassDB::bind_method(D_METHOD("random_y"), &Sketch::random_y);
	ClassDB::bind_method(D_METHOD("map"), &Sketch::map);
}