#include <iostream>
#include "graphics.h"

Graphics::Graphics()
{
  mPRelease = 0;
  mWindow.Create(sf::VideoMode(64 * 8, 32 * 8), "Wotan's Chip8 emulator");
  mWindow.SetFramerateLimit(60);
  for (int i = 0; i < 8 * 8 * 4; i++)
    mBlackSprite[i] = 0x00;
  for (int i = 0; i < 8 * 8 * 4; i++)
    mWhiteSprite[i] = 0xFF;

  mScreen.Create(64 * 8, 32 * 8);
  mScreenSprite.SetTexture(mScreen);

  Clear();
  Flip();

  for (int i = 0; i < 64; i++)
    for (int j = 0; j < 32; j++)
      mPixelTab[i][j] = false;

  mPRelease = 1;
  mKey[0x0] = sf::Keyboard::Numpad0;
  mKey[0x1] = sf::Keyboard::Numpad1;
  mKey[0x2] = sf::Keyboard::Numpad2;
  mKey[0x3] = sf::Keyboard::Numpad3;
  mKey[0x4] = sf::Keyboard::Numpad4;
  mKey[0x5] = sf::Keyboard::Numpad5;
  mKey[0x6] = sf::Keyboard::Numpad6;
  mKey[0x7] = sf::Keyboard::Numpad7;
  mKey[0x8] = sf::Keyboard::Numpad8;
  mKey[0x9] = sf::Keyboard::Numpad9;
  mKey[0xA] = sf::Keyboard::Q;
  mKey[0xB] = sf::Keyboard::W;
  mKey[0xC] = sf::Keyboard::E;
  mKey[0xD] = sf::Keyboard::R;
  mKey[0xE] = sf::Keyboard::T;
  mKey[0xF] = sf::Keyboard::Y;
}

Graphics::~Graphics()
{

}

bool	Graphics::IsPixelSet(int x, int y)
{
  if (y > 32 * 8 || x > 64 * 8 || x < 0 || y < 0)
    return 0;
  return mPixelTab[x][y];
}

void	Graphics::SetPixel(int x, int y, bool on)
{
  if (y >= 32 * 8 || x >= 64 * 8 || x < 0 || y < 0)
    return ;
  mPixelTab[x][y] = on;
  if (on)
    mScreen.Update(mWhiteSprite, 8, 8, x * 8, y * 8);
  else
    mScreen.Update(mBlackSprite, 8, 8, x * 8, y * 8);
}

void	Graphics::Flip()
{
  mWindow.Clear();
  mWindow.Draw(mScreenSprite);
  mWindow.Display();
}

void	Graphics::Clear()
{
  for (int i = 0; i < 64; i++)
    for (int j = 0; j < 32; j++)
      SetPixel(i, j, false);
}

bool	Graphics::IsKeyUp(BYTE numKey)
{
  if (sf::Keyboard::IsKeyPressed(mKey[numKey]))
    return true;
  else
    return false;
}
