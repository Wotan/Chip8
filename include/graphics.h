/*
** graphics.h for  in /home/wotan/projets/chip8
** 
** Made by geoffroy aubey
** Login   <aubey_g@epitech.net>
** 
** Started on  Thu Nov  3 10:46:26 2011 geoffroy aubey
** Last update Thu Nov  3 10:46:26 2011 geoffroy aubey
*/

#ifndef GRAPHICS_H_
# define GRAPHICS_H_

# include "SDL/SDL.h"

typedef struct	s_graphics
{
  SDL_Surface	*screen;
  char		key[16];
  int		p_release;
}		t_graphics;

int	init_graphics(t_graphics **graphics);
int	delete_graphics(t_graphics *graphics);
int	is_pixel_set(t_graphics *graphics, int x, int y);
int	set_pixel(t_graphics *graphics, int x, int y, int on);


#endif /* !GRAPHICS_H_ */
