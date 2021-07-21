#include "LoadIm.h"
#include "../CharDetector/CharBlockDetector.h"


//ici test de la transformation de binaire les gars 
void BinaryTransformation(SDL_Surface* img, int lignes, int colonnes, int tableau[lignes][colonnes]) //fct de oim (oim=cele)
{
    //va construire le tableau de 0 et de 1 à partir de l'image en noir et blanc

    Uint32 pixel;
    Uint8 r, g, b;
    int width, height;
    width = img->w;
    height = img->h;
    //on parcourt tous les pixels de la matrice image
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            pixel = getpixel(img, i, j);
            SDL_GetRGB(pixel, img->format, &r, &g, &b);
            if (r >= 127) //on se trouve sur un pixel blanc -> 0
            {
                tableau[i][j] = 0;
            }
            else //on est sur du noir -> 1
            {
                tableau[i][j] = 1;
            }
        }
    }
}


// ici fin binarisation
//ici debut resizing


//ici fin resizing
int IMGTreatment(SDL_Surface *img, char* torecognize, char* buffer)
{
  //PromptImg(img);//on affiche l'image en couleur
  greyscale(img);
  blackandwhite(img);
  noiseReduction(img);
  int lines = img -> w;
  int col = img -> h;
  int BinArr[lines][col];

  BinaryTransformation(img, lines, col, BinArr);
  CharDetector(lines, col, BinArr, torecognize, buffer);

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
  //SDL_FreeSurface(image);
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
   int limit = 200;
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
           if(r >= limit && g >= limit && b >= limit)
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


void noiseReduction(SDL_Surface *img)
{
  int w;
  int h;
  w = img -> w;
  h = img -> h;
  int L[5];
  for(int i = 0; i < w; i++)
    {
      for(int j= 0; j < h; j++)
	{
	  if(i == 0)
	    {
	      if(j == 0)
		{
		  L[0] = getpixel(img, i, j);
		  L[1] = getpixel(img, i, j);
		  L[2] = getpixel(img, i+1, j+1);
		  L[3] = getpixel(img, i, j + 1);
		  L[4] = getpixel(img, i + 1, j);
		}
	      else if(j == h)
		{
		  L[0] = getpixel(img, i, j);
		  L[1] = getpixel(img, i, j - 1);
		  L[2] = getpixel(img, i, j+1);
		  L[3] = getpixel(img, i+1, j-1);
		  L[4] = getpixel(img, i + 1, j);
		}
	      else
		{
		  L[0] = getpixel(img, i, j);
		  L[1] = getpixel(img, i, j - 1);
		  L[2] = getpixel(img, i, j);
		  L[3] = getpixel(img, i, j + 1);
		  L[4] = getpixel(img, i + 1, j);
		}
	    }
	  else if(i == w)
	    {
	      if(j == 0)
		{
		  L[0] = getpixel(img, i, j);
		  L[1] = getpixel(img, i, j);
		  L[2] = getpixel(img, i - 1, j);
		  L[3] = getpixel(img, i, j + 1);
		  L[4] = getpixel(img, i-1, j+1);
		}
	      else if(j == h)
		{
		  L[0] = getpixel(img, i, j);
		  L[1] = getpixel(img, i, j - 1);
		  L[2] = getpixel(img, i - 1, j);
		  L[3] = getpixel(img, i - 1, j - 1);
		  L[4] = getpixel(img, i, j);
		}
	      else
		{
		  L[0] = getpixel(img, i, j);
		  L[1] = getpixel(img, i, j - 1);
		  L[2] = getpixel(img, i - 1, j);
		  L[3] = getpixel(img, i, j + 1);
		  L[4] = getpixel(img, i - 1, j - 1);
		}
	    }
	  else
	    {
	      if(j == 0)
		{
		  L[0] = getpixel(img, i, j);
		  L[1] = getpixel(img, i + 1, j + 1);
		  L[2] = getpixel(img, i - 1, j);
		  L[3] = getpixel(img, i, j + 1);
		  L[4] = getpixel(img, i + 1, j);
		}
	      else if(j == h)
		{
		  L[0] = getpixel(img, i, j);
		  L[1] = getpixel(img, i, j - 1);
		  L[2] = getpixel(img, i - 1, j);
		  L[3] = getpixel(img, i - 1, j - 1);
		  L[4] = getpixel(img, i + 1, j);
		}
	      else
		{
		  L[0] = getpixel(img, i, j);
		  L[1] = getpixel(img, i, j - 1);
		  L[2] = getpixel(img, i - 1, j);
		  L[3] = getpixel(img, i, j);
		  L[4] = getpixel(img, i + 1, j);
		}
	    }
	  int pixel1 = L[0];
	  int pixel2 = L[1];
	  int pixel3 = L[2];
	  int pixel4 = L[3];
	  int pixel5 = L[4];
	  Uint8 r1,g1,b1;
	  SDL_GetRGB(pixel1, img->format, &r1, &g1, &b1);
	  Uint8 r2,g2,b2;
	  SDL_GetRGB(pixel2, img->format, &r2, &g2, &b2);
	  Uint8 r3,g3,b3;
	  SDL_GetRGB(pixel3, img->format, &r3, &g3, &b3);
	  Uint8 r4,g4,b4;
	  SDL_GetRGB(pixel4, img->format, &r4, &g4, &b4);
	  Uint8 r5,g5,b5;
	  SDL_GetRGB(pixel5, img->format, &r5, &g5, &b5);
	  Uint8 rm=(r1+r2+r3+r4+r5)/5;
	  if(rm>127)
	    {
	      rm=255;
	    }
	  else
	    {
	      rm=0;
	    }
	  pixel1 = SDL_MapRGB(img->format, rm, rm, rm);
	  putpixel(img,i,j,pixel1);
	}
    }
}

Uint8 formula(Uint8 c, double n)
{
    if(c <= 255 / 2)
        return (Uint8)( (255/2) * SDL_pow((double) 2 * c / 255, n));
    else
        return 255 - formula(255 - c, n);
}

void Contrast(SDL_Surface *img, double n)
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
	  r = formula(r, n);
	  g = formula(g, n);
	  b = formula(b, n);
	  pixel = SDL_MapRGB(img->format, r, g, b);
	  putpixel(img,i,j,pixel);
	}
    }
}

SDL_Surface* RotCentDeg(SDL_Surface* origine, float angle)
{
  SDL_Surface* destination;
  int i;
  int j;
  Uint32 couleur;
  int mx, my;
  int bx, by;
  float angle_radian;
  Uint32 pixel = SDL_MapRGB(origine->format, 255, 255, 255);

  angle_radian = -angle * M_PI / 180.0;
  destination = SDL_CreateRGBSurface(SDL_SWSURFACE, origine->w, origine->h, origine->format->BitsPerPixel,
				     origine->format->Rmask, origine->format->Gmask, origine->format->Bmask, origine->format->Amask);
 
  if(destination==NULL)
    return NULL;

  for(i=0;i<origine->w;i++)
    {
      for(j=0;j<origine->h;j++)
	{
	  putpixel(destination, i, j, pixel);
	}
    }
  
  mx = origine->w/2;
  my = origine->h/2;

  for(i=0;i<origine->w;i++)
    {
      for(j=0;j<origine->h;j++)
	{
	  bx = (int) (cos(angle_radian) * (i-mx) + sin(angle_radian) * (j-my)) + mx;
	  by = (int) (-sin(angle_radian) * (i-mx) + cos(angle_radian) * (j-my)) + my;
	  if (bx>=0 && bx< origine->w && by>=0 && by< origine->h)
	    {
	      couleur = getpixel(origine, i, j);
	      putpixel(destination, bx, by, couleur);
	    }
	}
    }
  return destination;
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

  switch (surface->format->BytesPerPixel)
    {
    case 1:
      return *p;

    case 2:
      return *(Uint16 *)p;

    case 3:
      if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
	return p[0] << 16 | p[1] << 8 | p[2];
      else
	return p[0] | p[1] << 8 | p[2] << 16;

    case 4:
      return *(Uint32 *)p;
    }

  return 0;
}

Uint8* pixelref(SDL_Surface *surf, unsigned x, unsigned y) {
  int bpp = surf->format->BytesPerPixel;
  return (Uint8*)surf->pixels + y * surf->pitch + x * bpp;
}

//gcc LoadIm.c $(sdl2-config --cflags --libs)
