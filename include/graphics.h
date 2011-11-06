#ifndef GRAPHICS_H_
# define GRAPHICS_H_

# include <SFML/Graphics.hpp>
# include <SFML/System.hpp>
# include <QApplication>
# include "QSFMLCanvas.h"
# include "emulator.h"

# define FILE_ERROR "Error, can't open file"

class	Emulator;

class	Graphics : public QSFMLCanvas
{
  Q_OBJECT

public:
  Graphics(QWidget* Parent, QApplication *app, const QPoint& Position, const QSize& Size);
  ~Graphics();

  void		ConfigureQt();
  bool		IsPixelSet(int x, int y);
  void		SetPixel(int x, int y, bool on);
  void		Flip();
  void		ClearScreen();
  int		HandleEvents(Emulator *emu);
  bool		IsKeyUp(BYTE numKey);
  BYTE		WaitKey();

public slots:
  void		OpenFile();
  void		Pause();
  void		Play();
  void		Stop();
  void		Reset();

private:
  void		OnInit();
  void		OnUpdate();
  sf::Texture		mScreen;
  sf::Sprite		mScreenSprite;
  sf::Keyboard::Key	mKey[16];
  int			mPRelease;
  bool			mPixelTab[64][32];

  sf::Uint8		mBlackSprite[8 * 8 * 4];
  sf::Uint8		mWhiteSprite[8 * 8 * 4];

  QString		mFileName;

  bool			mPause;
  Emulator		*mEmu;

  QApplication		*mApp;
  QAction		*mActionPlay;
  QAction		*mActionPause;
  QAction		*mActionReset;
  QAction		*mActionStop;
};

#endif /* !GRAPHICS_H_ */
