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

//-------------------------------------------------------

Color Sketch::r_random_color(){
	_r.randomize();
	float r = map(_r.randi_range(0,255),0,255,0.0,1.0);
	_r.randomize();
	float g = map(_r.randi_range(0,255),0,255,0.0,1.0);
	_r.randomize();
	float b = map(_r.randi_range(0,255),0,255,0.0,1.0);
	return Color(r,g,b);
}

//-------------------------------------------------------

float Sketch::random_x(){
	_r.randomize();
	return _r.randi_range(0,width());
}

//-------------------------------------------------------

float Sketch::random_y(){
	_r.randomize();
	return _r.randi_range(0,height());
}

//-------------------------------------------------------

void Sketch::stroke(Color color){
	_stroke_color = color;
}

//-------------------------------------------------------

void Sketch::stroke_width(float width){
	_stroke_width = width;
}

//-------------------------------------------------------

void Sketch::size(float x, float y) {
	//ProjectSettings::get_singleton()->set_setting("display/window/size/width",x);
	//ProjectSettings::get_singleton()->set_setting("display/window/size/height",y);
	OS::get_singleton()->set_window_size(Size2(x, y));

	//WIDTH = x;
	//HEIGHT = y;
}

//-------------------------------------------------------

float Sketch::height() {
	//return ProjectSettings::get_singleton()->get_setting("display/window/size/height");
	//return HEIGHT;
	Vector2 size = OS::get_singleton()->get_window_size();
	return size.y;
}

//-------------------------------------------------------

float Sketch::width() {
	//return ProjectSettings::get_singleton()->get_setting("display/window/size/width");
	//return WIDTH;
	Vector2 size = OS::get_singleton()->get_window_size();
	return size.x;
}

//-------------------------------------------------------

void Sketch::draw_on() {
	_candraw = true;
}
void Sketch::draw_off() {
	_candraw = false;
}
bool Sketch::is_drawing() {
	return _candraw;
}

//-------------------------------------------------------

void Sketch::fill(Color color){
	_canfill = true;
	_color = color;
}

void Sketch::no_fill(){
	_canfill = false;
}

//-------------------------------------------------------
float Sketch::mouse_x(){
	return _mouse_x;
}

float Sketch::mouse_y(){
	return _mouse_y;
}

//-------------------------------------------------------

void Sketch::process(){
	Vector2 mpos = OS::get_singleton()->get_mouse_position();
	_mouse_x = mpos.x;
	_mouse_y = mpos.y;
}

//-------------------------------------------------------

void Sketch::clear() {
	for(int i = 0; i<items.size(); i++){
		VS::get_singleton()->canvas_item_clear(items[i]);
	}
}

//-------------------------------------------------------

void Sketch::background(Color color) {
	VS::get_singleton()->set_default_clear_color(color);
}

//-------------------------------------------------------

float Sketch::map(float value, float istart, float istop, float ostart, float ostop) {
    return ostart + (ostop - ostart) * ((value - istart) / (istop - istart));
}
//--------------------------------------------------------------------------------------

void Sketch::point(float x, float y) {
	if (is_drawing()) {
		RID ci_rid = VS::get_singleton()->canvas_item_create();
		VS::get_singleton()->canvas_item_set_parent(ci_rid, get_canvas_item());
		items.push_back(ci_rid);

		Point2 pos = Point2(x,y);
		VS::get_singleton()->canvas_item_add_circle(ci_rid, pos, 1, _color);
	}
}

//-------------------------------------------------------

void Sketch::circle(float x, float y, float size) {
	if (is_drawing()) {
		
		if(_canfill){
			
			// filled circle rid
			RID ci_rid2 = VS::get_singleton()->canvas_item_create();
			VS::get_singleton()->canvas_item_set_parent(ci_rid2, get_canvas_item());
			items.push_back(ci_rid2);

			Point2 pos = Point2(x,y);
			
			circle_empty(x,y,size);
			
			VS::get_singleton()->canvas_item_add_circle(ci_rid2, pos, size, _color);
			VS::get_singleton()->canvas_item_set_z_index(ci_rid2,0);
		}else{
			circle_empty(x,y,size);
		}
		
	}
}

//-------------------------------------------------------

// function for drawing the outline of a circle 
// not visible to users
void Sketch::circle_empty(float h, float k, float r){
	RID ci_rid = VS::get_singleton()->canvas_item_create();
	VS::get_singleton()->canvas_item_set_parent(ci_rid, get_canvas_item());
	VS::get_singleton()->canvas_item_set_z_index(ci_rid,1);
	items.push_back(ci_rid);
	
	Vector<Vector2> points;
	Vector<Color> colors;

	float step = 2 * Math_PI/40;
	for(float theta = 0; theta < 360; theta+=step){
		float x = h + r * cos(theta);
		float y = k - r * sin(theta);
		
		Vector2 pos = Vector2(x,y);

		points.push_back(pos);
		colors.push_back(_stroke_color);
	}
	// cheap hack to draw a stroke circle
	VS::get_singleton()->canvas_item_add_polyline(ci_rid,points,colors,_stroke_width,true);
}

//-------------------------------------------------------

void Sketch::line(float x1, float y1, float x2, float y2, float width) {
	if (is_drawing()) {
		RID ci_rid = VS::get_singleton()->canvas_item_create();
		VS::get_singleton()->canvas_item_set_parent(ci_rid, get_canvas_item());
		items.push_back(ci_rid);

		Vector2 pos1 = Vector2(x1, y1);
		Vector2 pos2 = Vector2(x2, y2);
		
		VS::get_singleton()->canvas_item_add_line(ci_rid,
				pos1,
				pos2,
				_color,
				_stroke_width, // width of line
				true); // antialiasing enabled
	}
}

//-------------------------------------------------------

void Sketch::rect(float x, float y, float width, float height,bool center = false){
	if(is_drawing()){
		Rect2 r;
		Vector2 pos;
		Vector2 size = Vector2(width,height);
		
		if(_canfill){
			// filled rect rid
			RID ci_rid = VS::get_singleton()->canvas_item_create();
			VS::get_singleton()->canvas_item_set_parent(ci_rid, get_canvas_item());
			VS::get_singleton()->canvas_item_set_z_index(ci_rid,0);
			items.push_back(ci_rid);

			// position based of center of rect, or upper left corner
			if(center){
				pos = Vector2(x - (width/2),y - (height/2));
			}else{
				pos = Vector2(x,y);
			}

			r.set_position(pos);
			r.set_size(size);

			rect_empty(pos.x,pos.y,
						pos.x,pos.y+size.y,
						pos.x + size.x,pos.y,
						pos.x + size.x,pos.y+size.y);

			// filled rect
			VS::get_singleton()->canvas_item_add_rect (ci_rid, r, _color);
		}else{
			pos = Vector2(x,y);
			rect_empty(pos.x,pos.y,
						pos.x,pos.y+size.y,
						pos.x + size.x,pos.y,
						pos.x + size.x,pos.y+size.y);
		}
	}
}

//-------------------------------------------------------

// not visible to users
void Sketch::rect_empty(float ltx, float lty, 
						float lbx, float lby,
						float rtx, float rty, 
						float rbx, float rby){

	RID ci_rid = VS::get_singleton()->canvas_item_create();
	VS::get_singleton()->canvas_item_set_parent(ci_rid, get_canvas_item());
	VS::get_singleton()->canvas_item_set_z_index(ci_rid,1);
	items.push_back(ci_rid);

	Vector2 lt = Vector2(ltx,lty);
	Vector2 lb = Vector2(lbx,lby);
	Vector2 rt = Vector2(rtx,rty);
	Vector2 rb = Vector2(rbx,rby);

	Vector<Vector2> points;
	Vector<Color> colors;

	points.push_back(lt);
	points.push_back(lb);
	points.push_back(rb);
	points.push_back(rt);
	points.push_back(lt);

	// no loop here, fight me!
	colors.push_back(_stroke_color);
	colors.push_back(_stroke_color);
	colors.push_back(_stroke_color);
	colors.push_back(_stroke_color);
	colors.push_back(_stroke_color);

	VS::get_singleton()->canvas_item_add_polyline(ci_rid,points,colors,_stroke_width,true);	
}

//-------------------------------------------------------

void Sketch::polyline(Vector<Vector2> points,Vector<Color> colors,bool antialiased = true){
	if(is_drawing()){
		RID ci_rid = VS::get_singleton()->canvas_item_create();
		VS::get_singleton()->canvas_item_set_parent(ci_rid, get_canvas_item());
		items.push_back(ci_rid);

		VS::get_singleton()->canvas_item_add_polyline(ci_rid,points,colors,_stroke_width,antialiased);
	}
}


//--------------------------------------------------------------------------------------

void Sketch::_bind_methods() {
	ClassDB::bind_method(D_METHOD("point","x","y"), &Sketch::point);
	ClassDB::bind_method(D_METHOD("circle","x","y","size"), &Sketch::circle);
	ClassDB::bind_method(D_METHOD("line","x1","y1","x2","y2","width"), &Sketch::line);
	ClassDB::bind_method(D_METHOD("rect","x","y","length","width","center"), &Sketch::rect);
	ClassDB::bind_method(D_METHOD("polyline","points","colors","antialiased"), &Sketch::polyline);
	ClassDB::bind_method(D_METHOD("clear"), &Sketch::clear);
	ClassDB::bind_method(D_METHOD("process"), &Sketch::process);
	ClassDB::bind_method(D_METHOD("background","color"), &Sketch::background);
	ClassDB::bind_method(D_METHOD("draw_on"), &Sketch::draw_on);
	ClassDB::bind_method(D_METHOD("draw_off"), &Sketch::draw_off);
	ClassDB::bind_method(D_METHOD("mouse_x"), &Sketch::mouse_x);
	ClassDB::bind_method(D_METHOD("mouse_y"), &Sketch::mouse_y);
	ClassDB::bind_method(D_METHOD("is_drawing"), &Sketch::is_drawing);
	ClassDB::bind_method(D_METHOD("fill","color"), &Sketch::fill);
	ClassDB::bind_method(D_METHOD("no_fill"), &Sketch::no_fill);
	ClassDB::bind_method(D_METHOD("size","x","y"), &Sketch::size);
	ClassDB::bind_method(D_METHOD("stroke","color"), &Sketch::stroke);
	ClassDB::bind_method(D_METHOD("stroke_width","width"), &Sketch::stroke_width);
	ClassDB::bind_method(D_METHOD("width"), &Sketch::width);
	ClassDB::bind_method(D_METHOD("height"), &Sketch::height);
	ClassDB::bind_method(D_METHOD("random_color"), &Sketch::random_color);
	ClassDB::bind_method(D_METHOD("r_random_color"), &Sketch::r_random_color);
	ClassDB::bind_method(D_METHOD("random_x"), &Sketch::random_x);
	ClassDB::bind_method(D_METHOD("random_y"), &Sketch::random_y);
	ClassDB::bind_method(D_METHOD("map","value","istart","istop","ostart","ostop"), &Sketch::map);
}