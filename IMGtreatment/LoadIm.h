#ifndef XORNEURALSYSTEM_H
#define XORNEURALSYSTEM_h

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int IMGTreatment(char* file);

void PromptImg(SDL_Surface *image);
void StayOpen();
void greyscale(SDL_Surface *img);
void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);
Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y);
Uint8* pixelref(SDL_Surface *surf, unsigned x, unsigned y);
void blackandwhite(SDL_Surface *img);

#endif
