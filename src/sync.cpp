#include <SDL/SDL.h>
#include "emulator.h"

void	sync_CPU()
{
  SDL_Delay((1000) / FREQUENCE);
}
