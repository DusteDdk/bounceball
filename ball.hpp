/*
 * ball.cpp
 *
 *  Created on: 11. dec. 2016
 *      Author: dusted
 */

#ifndef BALL_HPP_
#define BALL_HPP_

#include <SDL2/SDL.h>

class Ball {
public:
	Ball(SDL_Texture *tex, SDL_Rect rect, float x, float y, float velx, float vely);
	void move(float time);
	void draw(SDL_Renderer* ren);
	void reactInsideBox( int fx, int fy, int tx, int ty);

private:
	float posx, posy, velx, vely;
	SDL_Texture* texture;
	SDL_Rect rect;
};


#endif /* BALL_HPP_ */
