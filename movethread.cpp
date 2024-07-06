#include "movethread.h"

MoveThread::MoveThread(QLabel *label, QWidget *field, int speed, QObject *parent)
    : QThread(parent), label(label), field(field), speed(speed)
{
}

void MoveThread::run()
{
    bool gameEnded = false; // Flag to ensure game over is only emitted once
    while (label->x() + label->width() > 0) {
        QMetaObject::invokeMethod(label, [this, &gameEnded]() {
            if (!gameEnded) {
                int x = label->x() - 5;
                int y = label->y();
                label->move(x, y);

                // Check if the label has reached the end of the frame
                if (x <=  80 ) {
                    emit gameOver();
                    gameEnded = true; // Set the flag to true to prevent further emissions
                }
            }
        }, Qt::QueuedConnection);
        msleep(speed); // Adjust speed here
    }
}
