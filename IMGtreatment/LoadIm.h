#ifndef XORNEURALSYSTEM_H
#define XORNEURALSYSTEM_h

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#define M_PI 3.14159265358979323846

int IMGTreatment(SDL_Surface *image, char* torecognize, char* buffer);

void PromptImg(SDL_Surface *image);
void StayOpen();
void greyscale(SDL_Surface *img);
void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);
Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y);
Uint8* pixelref(SDL_Surface *surf, unsigned x, unsigned y);
void blackandwhite(SDL_Surface *img);
void noiseReduction(SDL_Surface *img);
SDL_Surface* RotCentDeg(SDL_Surface* origine, float angle);
void Contrast(SDL_Surface *img, double n);

#endif
