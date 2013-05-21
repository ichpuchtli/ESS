#ifndef __RECTMATRIXWIDGET__
#define __RECTMATRIXWIDGET__

#include <QWidget>
#include <QPainter>
#include <QThread>

#define LM_NUM_ROWS 7
#define LM_NUM_COLS 15

#define LM_AREA (LM_NUM_ROWS * LM_NUM_COLS)

class RectMatrix : public QWidget {


  QThread thread;

  public:
    RectMatrix(int rectSize = 20);

    void set(int row, int col);
    void clear(int row, int col);

    void clearAll(void);

  private:
    QRect  LEDRects[LM_AREA];
    QColor LEDColours[LM_AREA];

    int rectSize;

  protected:
    void paintEvent(QPaintEvent *event);

};

#endif
