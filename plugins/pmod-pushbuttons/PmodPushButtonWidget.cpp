#include "PmodPushButtonWidget.h"

#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>

PmodPushButtonWidget::PmodPushButtonWidget()
{
  this->btn0 = new QPushButton( QString( '1' ), this );
  this->btn1 = new QPushButton( QString( '2' ), this );
  this->btn2 = new QPushButton( QString( '3' ), this );
  this->btn3 = new QPushButton( QString( '4' ), this );

  QGridLayout* grid = new QGridLayout( this );

  grid->addWidget( this->btn0, 0, 0 );
  grid->addWidget( this->btn1, 0, 1 );
  grid->addWidget( this->btn2, 1, 0 );
  grid->addWidget( this->btn3, 1, 1 );

  setFocusPolicy(Qt::ClickFocus);
}

void PmodPushButtonWidget::keyPressEvent( QKeyEvent* event )
{

  switch ( event->key() ) {
  case Qt::Key_1:
    btn0->pressed();
    btn0->setDown( true );
    break;
  case Qt::Key_2:
    btn1->pressed();
    btn1->setDown( true );
    break;
  case Qt::Key_3:
    btn2->pressed();
    btn2->setDown( true );
    break;
  case Qt::Key_4:
    btn3->pressed();
    btn3->setDown( true );
    break;
   default:
    QWidget::keyPressEvent( event );

  }

}

void PmodPushButtonWidget::keyReleaseEvent( QKeyEvent* event )
{

  switch ( event->key() ) {
  case Qt::Key_1:
    btn0->released();
    btn0->setDown( false );
    break;
  case Qt::Key_2:
    btn1->released();
    btn1->setDown( false );
    break;
  case Qt::Key_3:
    btn2->released();
    btn2->setDown( false );
    break;
  case Qt::Key_4:
    btn3->released();
    btn3->setDown( false );
    break;
  default:
    QWidget::keyReleaseEvent( event );

  }

}
