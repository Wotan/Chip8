#include <SDL/SDL.h>
#include "graphics.h"

Graphics::Graphics()
{
  int	i;

  SDL_Init(SDL_INIT_VIDEO);
  mScreen = SDL_SetVideoMode(64 * 8, 32 * 8, 32,
			    SDL_HWSURFACE);

  SDL_WM_SetCaption("Wotan's Chip8 emulator", NULL);

  for (i = 0; i < 16; i++)
    mKey[i] = 0;
  mPRelease = 1;
}
Graphics::~Graphics()
{
  SDL_Quit();
}

bool	Graphics::IsPixelSet(int x, int y)
{
  Uint8 *p;
  unsigned int	bpp = 4;

  x = x * 8;
  y = y * 8;

  if (y > 32 * 8 || x > 64 * 8 || x < 0 || y < 0)
    return 0;
  p = (Uint8 *)mScreen->pixels + y * mScreen->pitch + x * bpp;
  return (p[1] == 0xFF ? 1 : 0);
}

void	Graphics::SetPixel(int x, int y, bool on)
{
  unsigned int	bpp = 4;
  Uint8 *p;
  unsigned int i, j;

  x = x * 8;
  y = y * 8;

  p = (Uint8 *)mScreen->pixels + y * mScreen->pitch + x * bpp;
  if (y >= 32 * 8 || x >= 64 * 8 || x < 0 || y < 0)
    return ;
  for (j = 0; j < 8; j++)
    {
      for (i = 0; i < bpp * 8; i++)
	p[i] = on ? 0xFF : 0x0;
      p += mScreen->pitch;
    }
}

void	Graphics::Flip()
{
  SDL_Flip(mScreen);
}

void	Graphics::Clear()
{
  SDL_FillRect(mScreen, NULL, SDL_MapRGB(mScreen->format, 0, 0, 0));
}

bool	Graphics::IsKeyUp(int numKey)
{
  if (mKey[numKey] == 1)
    return true;
  return false;
}
