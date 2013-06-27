#ifndef __RECTMATRIXWIDGET__
#define __RECTMATRIXWIDGET__

#include <QtWidgets/QWidget>
#include <QtGui/QPainter>
#include <QtGui/QPixmap>

class RectMatrix : public QWidget {

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
