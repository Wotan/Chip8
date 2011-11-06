#include "emulator.h"
#include "graphics.h"

int	Graphics::HandleEvents(Emulator *emu)
{
  sf::Event event;

  PollEvent(event);
  switch (event.Type)
    {
    case sf::Event::KeyPressed:
      switch(event.Key.Code)
	{
	case sf::Keyboard::Space:
	  emu->DoCycle();
	  break ;
	default:
	  break ;
	}
      break ;

    case sf::Event::KeyReleased:
      switch(event.Key.Code)
	{
	default:
	  break ;
	  }
      break;

    default:
      break ;
    }
  return 0;
}
