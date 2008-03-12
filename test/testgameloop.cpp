#include "../TetrisBoard.h"
#include "../TetrominoFactory.h"
#include "../Tetromino.h"
#include "../Graphics.h"
#include "../BoardGraphics.h"
#include "../TetrisLogic.h"
#include <iostream>

void pause() {
  fflush ( stdout );
  getchar();
}

int main(void) {
//  CTetrisLogic *logic = new CTetrisLogic;
  SGraphics *g = new SGraphics();
  CTetrisBoard *gameBoard = new CTetrisBoard(GAMEBOARD_WIDTH, GAMEBOARD_HEIGHT);
  CTetrisBoard *previewBoard = new CTetrisBoard(PREVIEWBOARD_WIDTH, PREVIEWBOARD_HEIGHT);
  CBoardGraphics *gbg = new CBoardGraphics(gameBoard, g, 2, 1);
  CBoardGraphics *pbg = new CBoardGraphics(previewBoard, g, 20, 1);
  pbg->setBorderStyle(SGraphics::BORDER_SINGLE);
  CTetrominoFactory *factory = new CTetrominoFactory();
  CTetromino *current = factory->createRandom();
  current->attach(gameBoard);
  CTetromino *previews[PREVIEW_TETROMINOES];
  int previewSpacingY = 4;
  int i=0;
  for(i=0; i<PREVIEW_TETROMINOES; i++) {
    previews[i] = factory->createRandom();
    previews[i]->attach(previewBoard, previewSpacingY * i * -1 - previewSpacingY/2);
  }

  pause();

  bool gameOver = false;

  while(!gameOver) {
    current->drop();
    pause();

    delete current;
    previews[0]->detach(true);
    current = previews[0];
    if(current->attach(gameBoard)) {
      // Nostaa j‰ljelle j‰‰neiden preview-palikoiden vuoronumeroa yhdell‰.
      for(i=0; i<PREVIEW_TETROMINOES-1; i++) {
        previews[i] = previews[i+1];
        previews[i]->moveUp(previewSpacingY);
      }
      previews[PREVIEW_TETROMINOES-1] = factory->createRandom();
      previews[PREVIEW_TETROMINOES-1]->attach(previewBoard, previewSpacingY * i * -1 - previewSpacingY/2);
    } else {
      gameOver = true;
      delete current;
      for(i=1; i<PREVIEW_TETROMINOES; i++)
        delete previews[i];
    }
  }
  delete gameBoard;
  delete previewBoard;
  delete factory;
  delete g;
  delete gbg;
  delete pbg;

//  delete logic;
  return 0;
}
