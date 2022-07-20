#include "sketch.h"

    void Sketch::_bind_methods(){
        ClassDB::bind_method(D_METHOD("point"), &Sketch::point);
        ClassDB::bind_method(D_METHOD("circle"), &Sketch::circle);
        ClassDB::bind_method(D_METHOD("get_rid"), &Sketch::get_rid);
        ClassDB::bind_method(D_METHOD("clear"), &Sketch::clear);
        ClassDB::bind_method(D_METHOD("background"), &Sketch::background);
        ClassDB::bind_method(D_METHOD("draw_on"), &Sketch::draw_on);
        ClassDB::bind_method(D_METHOD("draw_off"), &Sketch::draw_off);
        ClassDB::bind_method(D_METHOD("is_drawing"), &Sketch::is_drawing);
        ClassDB::bind_method(D_METHOD("size"), &Sketch::size);
        ClassDB::bind_method(D_METHOD("screen_width"), &Sketch::screen_width);
        ClassDB::bind_method(D_METHOD("screen_height"), &Sketch::screen_height);
    }

    void Sketch::size(float x, float y){
        //ProjectSettings::get_singleton()->set_setting("display/window/size/width",x);
        //ProjectSettings::get_singleton()->set_setting("display/window/size/height",y);
        OS::get_singleton()->set_window_size(Size2(x,y));
        
        WIDTH = x;
        HEIGHT = y;
    }

    float Sketch::screen_height(){
        return ProjectSettings::get_singleton()->get_setting("display/window/size/height");
    }

    float Sketch::screen_width(){
        return ProjectSettings::get_singleton()->get_setting("display/window/size/width"); 
    }

    void Sketch::draw_on(){_candraw = true;}
    void Sketch::draw_off(){ _candraw = false;}
    bool Sketch::is_drawing(){ return _candraw;}

    //void Sketch::_ready(){}
    //void Sketch::_process(){
    //    //print_line("updating!!");
    //   if (is_drawing()){
    //        
    //    }
    //}

    RID Sketch::get_rid(){
        return _ci_rid;  
    }

    void Sketch::clear(){
        VS::get_singleton()->canvas_item_clear(get_rid());
    }

    void Sketch::background(Color color){
        VS::get_singleton()->set_default_clear_color(color);
    }


    void Sketch::circle(Vector2 pos,float size,Color color = Color(255,255,255,255)){
        if(is_drawing()){
            VS::get_singleton()->canvas_item_add_circle(get_rid(),pos,size,color);
        }
    }

    void Sketch::point(Vector2 pos,Color color = Color(255,255,255,255)){
        if(is_drawing()){
            VS::get_singleton()->canvas_item_add_circle(get_rid(),pos,1,color);
        }
    }