/**
 * @file RectMatrix.cpp
 * @brief Houses the RectMatrix class
*/
#include <QDebug>
#include <QPixmap>

#include <cassert>

#include "RectMatrix.h"

/**
 * @name           RectMatrix: A basic widget to simulate a 15x7 LED matrix
 * @param rectSize LED square dimension in pixels, this size depicts the entire size of the widget
 */
RectMatrix::RectMatrix(int rectSize){


  assert(rectSize > 0);

  int row,col;
  this->rectSize = rectSize;
  this->padding = 1;

  this->row = 6;
  this->columnStatus = 0;

  this->ledColour = new QColor(255,0,0,255);

  background = new QPixmap(LM_NUM_ROWS * (this->rectSize) + 2 * padding - 1,
      LM_NUM_COLS * (this->rectSize) + 2 * padding );

  background->fill(Qt::white);

  buffer = new QPixmap(LM_NUM_ROWS * (this->rectSize) + 2 * padding - 1,
      LM_NUM_COLS * (this->rectSize) + 2 * padding );

  this->resize(LM_NUM_ROWS * (this->rectSize) + 2 * padding - 1,
      LM_NUM_COLS * (this->rectSize) + 2 * padding );


  QPainter painter(this->background);

  for(int i = 0; i < LM_AREA; i++){

    row = (i % LM_NUM_ROWS) * this->rectSize;
    col = (i / LM_NUM_ROWS) * this->rectSize;

    // fill the background with gray rectangles
    painter.fillRect(QRect(row + this->padding,
     col + this->padding, this->rectSize - this->padding, this->rectSize - this->padding), Qt::lightGray);

  }

  painter.end();

  this->updateBuffer();
  //TODO prevent background refill setBackgroundMode ??
}

RectMatrix::~RectMatrix(){

  delete this->background;
  delete this->buffer;
  delete this->ledColour;

}
/**
 * @brief updates the internal canvas buffer, called when the row/col configuration changes
 * @code
 *    ...
 *    this->setColHigh(i);
 *    this->updateBuffer();
 * @endcode 
 */
void RectMatrix::updateBuffer(void){

  QPainter painter(this->buffer);

  // Start with the background
  painter.drawPixmap(QPoint(0, 0), *this->background);

  for(int col = 0; col < LM_NUM_COLS; col++){

    // True if physical column pin is held low i.e. ground i.e. current sink for LED
    if(this->columnStatus & (1 << col)){

      // Draw the rectangle where the column and row meet
      painter.fillRect(QRect(
                         this->row*this->rectSize + this->padding,
                         col*this->rectSize + this->padding,
                         this->rectSize - this->padding,
                         this->rectSize - this->padding),
                       *this->ledColour);
    }
    
  }

  painter.end();
}

/**
 * @brief sets the specified column high, prevents a grounded connection in the LED matrix
 * @param column the column to set high
 */
void RectMatrix::setHigh(int column){
  
  assert(column >= 0 && column <= 14);

  this->columnStatus &= ~(1 << column);

  this->updateBuffer();
}


/**
 * @brief sets the specified column low, provides a ground to draw current and light up the LED
 * @param column the column to set low
 */
void RectMatrix::setLow(int column){

  assert(column >= 0 && column <= 14);

  // Setting a column low provides a ground for the LED
  this->columnStatus |= (1 << column); 

  this->updateBuffer();
}

/**
 * @brief selects the row to display
 * @param row the row to display, only rows ranging from 0-7 are considered
 */
void RectMatrix::setRow(int row){

  assert(row >= 0 && row <= 7);

  this->row = row;

  this->updateBuffer();
}

/**
 * @brief replace the internal column status with the bitfield specified
 * @param bitfield a bitfield represent the column status, LSB represents column 0
 */
void RectMatrix::setCol(int bitfield){

  this->columnStatus = bitfield & 0x00007FFF;
}

void RectMatrix::paintEvent(QPaintEvent *event){

  QPainter painter(this);

  painter.drawPixmap(QPoint(0,0), *this->buffer);
  painter.end();

}
