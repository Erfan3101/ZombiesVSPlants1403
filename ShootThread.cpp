#include "ShootThread.h"
#include <QDebug>
#include <QApplication>
#include <QTimer>

ShootThread::ShootThread(QLabel *shoot, QWidget *frame, QWidget *parent)
    : QThread(parent), shoot(shoot), frame(frame)
{
    connect(this, &ShootThread::finished, shoot, &QObject::deleteLater); // Cleanup when thread finishes
}

ShootThread::~ShootThread()
{
    if (timer) {
        timer->stop();
        delete timer;
    }
}

void ShootThread::run()
{
    // Ensure this code runs on the main thread
    QMetaObject::invokeMethod(QApplication::instance(), [this]() {
        // Create a QTimer in the context of the main thread
        timer = new QTimer();

        // Connect the QTimer to the performShootActions slot
        connect(timer, &QTimer::timeout, this, &ShootThread::performShootActions);

        // Start the QTimer with an interval of 50 milliseconds (or any desired interval)
        timer->start(40);
    }, Qt::BlockingQueuedConnection);

    // Enter the event loop
    exec();
}

void ShootThread::performShootActions()
{
    if (shoot) {
        qDebug() << "Shoot widget is initialized.";
        qDebug() << "Shoot visibility: " << shoot->isVisible();
        qDebug() << "Shoot enabled: " << shoot->isEnabled();
        if (shoot->isVisible() && shoot->isEnabled()) {
            qDebug() << "Performing shoot actions";
            // Example action: move the shoot widget
            shoot->move(shoot->x() + 4, shoot->y());
            if (shoot->x() > frame->width()) {
                shoot->hide(); // Hide the shoot when it moves out of the frame
                timer->stop(); // Stop the timer when the shoot is out of frame
                exit(); // Exit the thread's event loop
            }
        }
    } else {
        qDebug() << "Shoot widget is not initialized.";
    }
}
