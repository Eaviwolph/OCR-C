#ifndef UI_H
#define UI_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


int IMGTreatment(SDL_Surface *image, char* torecognize, char* buffer);
SDL_Surface* RotCentDeg(SDL_Surface* origine, float angle);
void Contrast(SDL_Surface *img, double n);

int ui ();
#endif
