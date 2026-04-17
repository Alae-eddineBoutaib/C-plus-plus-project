#include "../include/level.hpp"

level::level(){

}

//destructor logic
level::~level(){
    for(auto obs : obstacles) delete obs;
    for(auto c : coins) delete c;
}

//draw logic
void level::draw(){
    for(auto obs : obstacles) obs->Draw();
    for(auto c : coins) c->Draw();
}

//update logic
void level::update(){
    for(auto obs : obstacles) obs->update();
    for(auto c : coins) c->update();
}

//reset position logic
void level::reset(){
    for(auto obs : obstacles){
        obs->position.x = obs->start_x;
        obs->position.y = obs->start_y;
        obs->direction = -1;  
    }
    for(auto c : coins){
        c->collected = false;
    }

}