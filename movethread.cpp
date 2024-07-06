#include "movethread.h"

MoveThread::MoveThread(QLabel *label, QWidget *field, int speed, QObject *parent)
    : QThread(parent), label(label), field(field), speed(speed)
{
}

void MoveThread::run()
{
    while (true) {
           if (!label->isVisible()) break;

           // Move the label to the left
           label->move(label->x() - 1, label->y()); // Adjust the movement logic as needed

           // Check if the label has reached the left boundary of the frame
           if (label->x() + label->width() < field->x()) {
               emit gameOver(); // Signal game over if a zombie reaches the end
               break;
           }

           // Adjust the speed of movement
           msleep(speed); // msleep is a static function of QThread to pause execution

           // Ensure GUI updates properly
           field->update();
       }
}
