#include <QDebug>

#include "RectMatrix.h"

RectMatrix::RectMatrix(int rectSize){

  int row,col;
  int padding = 1;

  this->rectSize = rectSize;

  this->resize(LM_NUM_ROWS * (this->rectSize) + 2 * padding - 1,
      LM_NUM_COLS * (this->rectSize) + 2 * padding );

  for(int i = 0; i < LM_AREA; i++){

    row = (i % LM_NUM_ROWS) * this->rectSize;
    col = (i / LM_NUM_ROWS) * this->rectSize;

    this->LEDRects[i] = QRect(row+padding, col+padding, this->rectSize-padding, this->rectSize-padding);
    this->LEDColours[i] = QColor(Qt::lightGray);
  }

}

void RectMatrix::clearAll(void){

  for(int i = 0; i < LM_AREA; i++){
    this->LEDColours[i] = Qt::lightGray;
  }

}

void RectMatrix::set(int row, int col){

  col = (LM_NUM_COLS-1) - col;

  this->LEDColours[row % 7 + col*7] = Qt::red;
}

void RectMatrix::clear(int row, int col){

  col = (LM_NUM_COLS-1) - col;

  this->LEDColours[row % 7 + col*7] = Qt::lightGray;
}

void RectMatrix::paintEvent(QPaintEvent *event){

  QPainter painter(this);

  for(int i = 0; i < LM_AREA; i++){

    painter.fillRect(this->LEDRects[i], this->LEDColours[i] );

  }

}
