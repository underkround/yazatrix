/**
 * TetrisBoard.cpp
 *
 * $Id$
 * $HeadURL$
 *
 * Y-koordinaatit alkavat alhaalta, eli alin rivi on y==0
 */

#include "TetrisBoard.h"

TetrisBoard::TetrisBoard(void) {

}

TetrisBoard::~TetrisBoard(void) {

}

int TetrisBoard::getWidth(void) {

}

int TetrisBoard::getHeight(void) {

}

int TetrisBoard::getRemovedLines(void) {

}

int TetrisBoard::getRemovedLinesLast(void) {

}

int TetrisBoard::getSlot(int x, int y) {

}

// returns old content
int TetrisBoard::setSlot(int x, int y, int content) {

}

// koskee koko lautaa
bool TetrisBoard::isEmpty(){

}

 // haluttu ruutu, offgrid = false, paitsi ylhäällä
bool TetrisBoard::isEmpty(int x, int y) {

}
bool TetrisBoard::isEmpty(int y) {

}

bool TetrisBoard::isFull(int y){

}

void TetrisBoard::reset(void) {

}

int TetrisBoard::clearFullLines(void) {

}

void TetrisBoard::notifyChange(void) {

}

bool TetrisBoard::registerBoardChangeListener(BoardChangeListener* bcl) {

}

bool TetrisBoard::unregisterBoardChangeListener(BoardChangeListener* bcl) {

}

//PRIVATE siirrä yläpuolen rivejä yhdellä
bool TetrisBoard::removeLine(int y){

}
