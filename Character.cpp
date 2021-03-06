//
//  Character.cpp
//  SuperOOPBros
//
//  Created by Maxime Moison on 3/22/18.
//  Copyright © 2018 Maxime Moison. All rights reserved.
//
#include "Character.hpp"
#include<iostream>

static Character* self;

static void animate(int i) {
    self->advance();
    glutTimerFunc(32, animate, i);
}

Character::Character(const char* normalFileName, const char* deadFileName, float x, float y){
    this->vx = 0;
    this->vy = 0;
    this->frame = Frame(x, y, .1, .2);
    this->hitbox = Frame(x, y, .1, .2);
    this->flyingTex = new AnimatedRect(normalFileName, 1, 7, &(this->frame.x), &(this->frame.y), &(this->frame.width), &(this->frame.height));
    this->deadTex = new AnimatedRect(deadFileName, 6, 6, &(this->frame.x), &(this->frame.y), &(this->frame.width), &(this->frame.height));
    this->dead = false;
    this->roids = false;
    self = this;
    jumpForce = DEFAULT_JUMP;
    animate(0);
}

Character::~Character() {
    delete flyingTex;
    delete deadTex;
}

void Character::setPosition(float x, float y){
    this->frame.x = x;
    this->frame.y = y;
    this->hitbox.x = x;
    this->hitbox.y = y;
}

void Character::setVelocity(float vx, float vy){
    this->vx = vx;
    this->vy = vy;
}

void Character::setVX(float vx){
    this->vx = vx;
}

void Character::setVY(float vy){
    this->vy = vy;
}


void Character::jump() {
    vy = jumpForce;
}

void Character::setState(bool roids){
    this->roids = roids;
}

bool Character::getState(){
    return roids;
}

void Character::move(Direction direction) {
    if (vx <= 0.02 && vx >= -0.02) {
        vx += direction * 0.01;
    }
}

void Character::attack(){
    // todo
}

void Character::setJumpForce(float jumpForce){
    this->jumpForce = jumpForce;
    if (vy > .02)
        this->vy = vy/1.5;
}

void Character::die(){
    // todo
    this->dead = true;
}

Frame Character::getHitbox() {
    return this->hitbox;
}

bool Character::collidesWith(Object *other) {
    if(roids)
        return false;
    return hitbox.collidesWith(other->getHitbox());
}

void Character::handleCollisionWith(Object *other) {
    if (collidesWith(other)) {
        // Handle collision with object
    }
}

float Character::getMinX() { return this->frame.x; }
float Character::getMaxX() { return this->frame.x + this->frame.width; }
float Character::getMinY() { return this->frame.y; }
float Character::getMaxY() { return this->frame.y + this->frame.height; }

float Character::getVX(){ return this->vx; }
float Character::getVY(){ return this->vy; }

void Character::calculateNextFrame() {
    // implement velocity handling
//    if (getMinY() < -.93)
//        jump();
    
    float x = this->frame.x;
    float y = this->frame.y;
    
    x += vx;
    y += vy;
    
    // update frames
    this->frame.x = x;
    this->frame.y = y;
    this->hitbox.x = x;
    this->hitbox.y = y;
}

void Character::advance(){
    if(!dead){
        flyingTex->advance();
    }
    else{
        deadTex->advance(1);
    }
}

void Character::draw() {
    //frame.draw(); //this draws the hitbox
    if(!dead){
        flyingTex->draw();
    }
    else{
        deadTex->draw();
    }
}

bool Character::isDead(){
    return this->dead;
}

void Character::reset(){
    this->setPosition(-0.5, 0.6);
    this->setVelocity(0, 0);
    this->dead = false;
    this->deadTex->reset();
    this->flyingTex->reset();
    this->jumpForce = DEFAULT_JUMP;
}
