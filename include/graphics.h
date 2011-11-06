#ifndef GRAPHICS_H_
# define GRAPHICS_H_

# include <SFML/Graphics.hpp>
# include <SFML/System.hpp>
# include "emulator.h"

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
  bool		IsKeyUp(BYTE numKey);

private:
  sf::RenderWindow	mWindow;
  sf::Texture		mScreen;
  sf::Sprite		mScreenSprite;
  sf::Keyboard::Key		mKey[16];
  int			mPRelease;
  bool			mPixelTab[64][32];

  sf::Uint8		mBlackSprite[8 * 8 * 4];
  sf::Uint8		mWhiteSprite[8 * 8 * 4];
};

#endif /* !GRAPHICS_H_ */
