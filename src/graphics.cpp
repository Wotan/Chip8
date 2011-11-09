#include <iostream>
#include <QMainWindow>
#include <QWidget>
#include <QString>
#include <QMenuBar>
#include <QFileDialog>
#include <QMessageBox>
#include <unistd.h>
#include "graphics.h"

Graphics::Graphics(QWidget* Parent, QApplication *app, const QPoint& Position, const QSize& Size) :
  QSFMLCanvas(Parent, Position, Size, 16)
{
  mApp = app;
  for (int i = 0; i < 8 * 8 * 4; i++)
    mBlackSprite[i] = 0x00;
  for (int i = 0; i < 8 * 8 * 4; i++)
    mWhiteSprite[i] = 0xFF;

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
  mEmu = NULL;
}

Graphics::~Graphics()
{

}

void	Graphics::ConfigureQt()
{
  QMainWindow	*mainWindow = (QMainWindow *)parentWidget();
  QMenuBar	*menuBar = mainWindow->menuBar();

  QMenu *menuFile = menuBar->addMenu("&File");
  QMenu *menuPlay = menuBar->addMenu("&Play");

  mActionPlay = menuPlay->addAction("&Play");
  mActionPause = menuPlay->addAction("&Pause");
  mActionStop = menuPlay->addAction("&Stop");
  mActionReset = menuPlay->addAction("&Reset");
  mActionPause->setEnabled(false);
  mActionPlay->setEnabled(false);
  mActionReset->setEnabled(false);
  mActionStop->setEnabled(false);
  QAction *actionOpen = menuFile->addAction("&Open");
  QAction *actionExit = menuFile->addAction("&Exit");

  connect(actionExit, SIGNAL(triggered()), mApp, SLOT(quit()));
  connect(actionOpen, SIGNAL(triggered()), this, SLOT(OpenFile()));
  connect(mActionPlay, SIGNAL(triggered()), this, SLOT(Play()));
  connect(mActionPause, SIGNAL(triggered()), this, SLOT(Pause()));
  connect(mActionReset, SIGNAL(triggered()), this, SLOT(Reset()));
  connect(mActionStop, SIGNAL(triggered()), this, SLOT(Stop()));

  actionExit->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
  actionOpen->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
}

void	Graphics::OpenFile()
{
  mFileName = QFileDialog::getOpenFileName(0, "Open Chip8's Rom", getcwd(NULL, 64));
  if (mFileName != 0)
    {
      if (mEmu)
	delete mEmu;
      mEmu = new Emulator();
      mEmu->SetGraphics(this);
      ClearScreen();
      if (!mEmu->Open(mFileName))
	{
	  QMessageBox::critical(this, "Error", FILE_ERROR);
	  Stop();
	  return;
	}
      Play();
    }
}

void	Graphics::OnInit()
{
  ConfigureQt();
  mScreen.Create(64 * 8, 32 * 8);
  mScreenSprite.SetTexture(mScreen);
  mPRelease = 1;
  mPause = 0;
  Flip();
  ClearScreen();
  mKeyClock.Reset();

  std::cout << "OnInit()" << std::endl;

}

void	Graphics::OnUpdate()
{
  if (mEmu)
    {
      HandleEvents(mEmu);
      if (!mPause)
	for (int i = 0; i < FREQUENCE / 60; i++)
	  mEmu->DoCycle();
    }
  Flip();
}

void	Graphics::Play()
{
  mPause = 0;
  mActionReset->setEnabled(true);
  mActionPlay->setEnabled(false);
  mActionPause->setEnabled(true);
  mActionStop->setEnabled(true);
}

void	Graphics::Pause()
{
  mPause = 1;
  mActionPlay->setEnabled(true);
  mActionPause->setEnabled(false);
}

void	Graphics::Stop()
{
  Pause();
  if (mEmu)
    delete mEmu;
  mEmu = NULL;
  mActionPlay->setEnabled(false);
  mActionPause->setEnabled(false);
  mActionStop->setEnabled(false);
  mActionReset->setEnabled(false);
  ClearScreen();
}

void	Graphics::Reset()
{
  if (!mEmu)
    return ;
  ClearScreen();
  delete mEmu;
  mEmu = new Emulator();
  mEmu->SetGraphics(this);
  if (!mEmu->Open(mFileName))
    {
      QMessageBox::critical(this, "Error", FILE_ERROR);
      Stop();
      return;
    }
  Play();
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
  Clear();
  Draw(mScreenSprite);
  Display();
}

void	Graphics::ClearScreen()
{
  for (int i = 0; i < 64; i++)
    for (int j = 0; j < 32; j++)
      SetPixel(i, j, false);
}

BYTE	Graphics::GetKey()
{

  if (mKeyClock.GetElapsedTime() > TIME_WAIT_KEY)
    {
      mKeyClock.Reset();
      for (int i = 0; i < 0xF; i++)
	if (IsKeyUp(i))
	  return i;
    }
  return 0xFF;
}

bool	Graphics::IsKeyUp(BYTE numKey)
{
  if (sf::Keyboard::IsKeyPressed(mKey[numKey]))
    return true;
  else
    return false;
}
