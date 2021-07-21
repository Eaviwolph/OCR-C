#include "LoadIm.h"



int IMGTreatment(char* file)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Surface *img = SDL_LoadBMP(file);
    greyscale(img);
    blackandwhite(img);
    PromptImg(img);
    SDL_Quit();
    return 0;
}

void PromptImg(SDL_Surface *image)
{
  int width,height;
  width = image -> w;
  height = image -> h;
  SDL_Window *ecran = SDL_CreateWindow("OCR", SDL_WINDOWPOS_UNDEFINED
				       ,SDL_WINDOWPOS_UNDEFINED, width, height,0);
  SDL_BlitSurface(image,NULL,SDL_GetWindowSurface(ecran),0);
  SDL_UpdateWindowSurface(ecran);

  StayOpen();
  SDL_FreeSurface(image);
  SDL_DestroyWindow(ecran);
}

void StayOpen()
{
  SDL_Event event;
  for(;;)
    {
      SDL_PollEvent(&event);
      switch (event.type)
        {
	case SDL_KEYDOWN: return;
	default: break;
        }
    }
}


void greyscale(SDL_Surface *img)
{
  Uint32 pixel;
  Uint8 r ,g ,b;
  int width,height;
  width = img -> w;
  height = img -> h;
  for(int i = 0; i < width; i++)
    {
      for(int j = 0; j < height; j++)
	{
	  pixel = getpixel(img, i, j);
	  SDL_GetRGB(pixel, img->format, &r, &g, &b);
	  r = r*0.3 + g*0.59 + b*0.11;
	  g = r*0.3 + g*0.59 + b*0.11;
	  b = r*0.3 + g*0.59 + b*0.11;
	  pixel = SDL_MapRGB(img->format, r, g, b);
	  putpixel(img,i,j,pixel);
	}
    }
}

void blackandwhite(SDL_Surface *img)
{
   Uint32 pixel;
   Uint8 r ,g ,b;
   int width,height;
   width = img -> w;
   height = img -> h;
   for(int i = 0; i < width; i++)
   {
       for(int j = 0; j < height; j++)
       {
           pixel = getpixel(img, i, j);
           SDL_GetRGB(pixel, img->format, &r, &g, &b);
           if(r >= 127 && g >= 127 && b >= 127)
           {
               r = 255;
               g = 255;
               b = 255;
           }
           else
           {
               r = 0;
               g = 0;
               b = 0;
           }
           pixel = SDL_MapRGB(img->format, r, g, b);
           putpixel(img,i,j,pixel);
       }
   }
}


// test de nouveaux gris
void BlackWhite(SDL_Surface *img)
{
   Uint32 pixel;
   Uint8 r ,g ,b;
   int width,height;
   width = img -> w;
   height = img -> h;
   for(int i = 0; i < width; i++)
   {
       for(int j = 0; j < height; j++)
       {
           pixel = getpixel(img, i, j);
           SDL_GetRGB(pixel, img->format, &r, &g, &b);
           if(r >= 127 && g >= 127 && b >= 127)
           {
               r = 255;
               g = 255;
               b = 255;
           }
           else
           {
               r = 0;
               g = 0;
               b = 0;
           }
           pixel = SDL_MapRGB(img->format, r, g, b);
           putpixel(img,i,j,pixel);
       }
   }
}


void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel) {
  Uint8 *p = pixelref(surface, x, y);
  switch(surface->format->BytesPerPixel)
  {
  case 1:
    *p = pixel;
    break;
  case 2:
    *(Uint16 *)p = pixel;
    break;
  case 3:
    if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
      p[0] = (pixel >> 16) & 0xff;
      p[1] = (pixel >> 8) & 0xff;
      p[2] = pixel & 0xff;
    } else {
      p[0] = pixel & 0xff;
      p[1] = (pixel >> 8) & 0xff;
      p[2] = (pixel >> 16) & 0xff;
    }
    break;
  case 4:
    *(Uint32 *)p = pixel;
    break;
  }
}

Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y) {
  Uint8 *p = pixelref(surface, x, y);
  switch(surface->format->BytesPerPixel)
  {
  case 1:
    return *p;
  case 2:
    return *(Uint16 *)p;
  case 3:
    if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
      return p[0] << 16 | p[1] << 8 | p[2];
    else
      return p[0] | p[1] << 8 | p[2] << 16;
  case 4:
    return *(Uint32 *)p;
  }
  return 0;
}

Uint8* pixelref(SDL_Surface *surf, unsigned x, unsigned y) {
  int bpp = surf->format->BytesPerPixel;//the number of bytes required to hold a pixel value
  Uint8 *p =(Uint8*)surf->pixels + y * surf->pitch + x * bpp;//p is the adresse to the pixel we want to retrieve
  return p;
}

//gcc LoadIm.c $(sdl2-config --cflags --libs)
