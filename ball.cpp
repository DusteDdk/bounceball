/*
 * ball.cpp
 *
 *  Created on: 11. dec. 2016
 *      Author: dusted
 */

#include "ball.hpp"

Ball::Ball(SDL_Texture *tex, SDL_Rect rect, float x, float y, float velx, float vely) {
	this->rect = rect;
	this->posx = x;
	this->posy = y;
	this->velx = velx;
	this->vely = vely;
	this->texture = tex;
}

void Ball::move(float time) {
	this->posx += this->velx*time;
	this->posy += this->vely*time;


	if( this->vely < 50)
		this->vely += 1;
}

void Ball::draw(SDL_Renderer* ren) {
	this->rect.x = int(this->posx);
	this->rect.y = int(this->posy);
	SDL_RenderCopy(ren, this->texture, NULL, &this->rect);
}

void Ball::reactInsideBox( int fx, int fy, int tx, int ty) {

	if(this->posx < fx ) {
		this->velx *= -0.9;
		this->posx = fx;
	} else if( this->posx+this->rect.w > tx) {
		this->velx *= -0.9;
		this->posx = tx - this->rect.w;
	}

	if(this->rect.y < fy ) {
		this->vely = 0;

		this->posy = fy;
	} else if((this->rect.y+this->rect.h) > ty) {
		this->vely *= -0.7;
		this->velx /=1.8;
		this->posy = ty - this->rect.h;

		if( fabs(this->vely) < 10 ) {
			this->vely *=5;
		}

	}

	if( fabs(this->velx) < 6 ) {
		this->velx *=5;
	}

}
