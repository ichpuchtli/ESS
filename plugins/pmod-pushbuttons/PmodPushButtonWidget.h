#ifndef PMODPUSHBUTTONWIDGET_H
#define PMODPUSHBUTTONWIDGET_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include <QtGui/QResizeEvent>

class PmodPushButtonWidget : public QWidget
{

public:
  PmodPushButtonWidget();

  QPushButton* btn0;
  QPushButton* btn1;
  QPushButton* btn2;
  QPushButton* btn3;

protected:

  virtual void keyPressEvent( QKeyEvent *event );
  virtual void keyReleaseEvent( QKeyEvent *event );

};

#endif // PMODPUSHBUTTONWIDGET_H
