#ifndef __RECTMATRIXWIDGET__
#define __RECTMATRIXWIDGET__

#include <QWidget>
#include <QPainter>
#include <QThread>
#include <QPixmap>

#define LM_NUM_ROWS 7
#define LM_NUM_COLS 15

#define LM_AREA (LM_NUM_ROWS * LM_NUM_COLS)

class RectMatrix : public QWidget {


  QThread thread;

  public:
    RectMatrix(int rectSize = 20);
    ~RectMatrix();

  public slots:
    void setHigh(int column);
    void setLow(int column);

    void setCol(int bitfield);

    void setRow(int row);

  private:

    int rectSize; // pixel size of each "LED"
    int columnStatus;
    int row;
    int padding;

    QColor* ledColour;

    QPixmap* background;
    QPixmap* buffer;

    void updateBuffer(void);

  protected:
    void paintEvent(QPaintEvent *event);

};

#endif
