#include <QtGui>
#include <QWidget>
#include <QLabel>
class W: public QWidget
    {
        Q_OBJECT

        public:
            explicit W(QWidget *parent=0) : QWidget(parent) { }

        protected:
            void mousePressEvent(QMouseEvent *evt)
            {
                oldPos = evt->globalPos();
            }

            void mouseMoveEvent(QMouseEvent *evt)
            {
                const QPoint delta = evt->globalPos() - oldPos;
                move(x()+delta.x(), y()+delta.y());
                oldPos = evt->globalPos();

            }




        private:
            QPoint oldPos;
    };
