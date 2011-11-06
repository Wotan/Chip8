#include "emulator.h"
#include "graphics.h"

int	Graphics::HandleEvents(Emulator *emu, int *pause)
{
  sf::Event event;

  mWindow.PollEvent(event);
  switch (event.Type)
    {
    case sf::Event::Closed:
      return 1;
      break ;

    case sf::Event::KeyPressed:
      switch(event.Key.Code)
	{
	case sf::Keyboard::Space:
	  emu->DoCycle();
	  break ;
	case sf::Keyboard::P:
	  if (mPRelease)
	    {
	      *pause = !*pause;
	      mPRelease = 0;
	    }
	  break ;
	case sf::Keyboard::Escape:
	  return 1;
	  break;
	default:
	  break ;
	}
      break ;

    case sf::Event::KeyReleased:
      switch(event.Key.Code)
	{
	case sf::Keyboard::P:
	  mPRelease = 1;
	  break ;
	default:
	  break ;
	  }
      break;

    default:
      break ;
    }
  return 0;
}
