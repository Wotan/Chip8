/*
** graphics.h for  in /home/wotan/projets/chip8
** 
** Made by geoffroy aubey
** Login   <aubey_g@epitech.net>
** 
** Started on  Thu Nov  3 10:46:26 2011 geoffroy aubey
** Last update Sat Nov  5 23:40:41 2011 geoffroy aubey
*/

#ifndef GRAPHICS_H_
# define GRAPHICS_H_

# include "SDL/SDL.h"

static const unsigned int key_tab[16] =
{
  SDLK_KP0,
  SDLK_KP1,
  SDLK_KP2,
  SDLK_KP3,
  SDLK_KP4,
  SDLK_KP5,
  SDLK_KP6,
  SDLK_KP7,
  SDLK_KP8,
  SDLK_KP9,
  SDLK_a,
  SDLK_b,
  SDLK_c,
  SDLK_d,
  SDLK_e,
  SDLK_f
};

class	Graphics
{
public:
  Graphics();
  ~Graphics();
  bool		IsPixelSet(int x, int y);
  void		SetPixel(int x, int y, bool on);
  void		Flip();
  void		Clear();
  int		HandleEvents(class Emulator *emu, int *pause);
  bool		IsKeyUp(int numKey);

private:
  SDL_Surface	*mScreen;
  char		mKey[16];
  int		mPRelease;
};

#endif /* !GRAPHICS_H_ */
