#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDrag>
#include <QMimeData>
#include <QLabel>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , currentLabel(nullptr)
    , gameEnded(false)
{
    ui->setupUi(this);
    //impelement the ui picture for drag and drop
ui->peashooter->setAcceptDrops(true);
ui->two_peashooter->setAcceptDrops(true);
ui->walnut->setAcceptDrops(true);
ui->plum_mine->setAcceptDrops(true);
ui->jelapino->setAcceptDrops(true);
ui->boomerang->setAcceptDrops(true);
ui->regular->setAcceptDrops(true);
ui->bucked_head->setAcceptDrops(true);
ui->leafhead->setAcceptDrops(true);
ui->tall->setAcceptDrops(true);
ui->astronaut->setAcceptDrops(true);
ui->purplehair->setAcceptDrops(true);
setAcceptDrops(true);
 //connect(moveTimer, &QTimer::timeout, this, &MainWindow::moveLabel);
 // Map source labels to the specific appearing labels
  labelMap["regular"] = ":/zombies_p/regular zombie_transparent.png";
  labelMap["bucked_head"] = ":/zombies_p/Bucket head zombie_trasparent.png";
  labelMap["leafhead"] = ":/zombies_p/leaf hair zombie_transparent.png";
  labelMap["tall"] = ":/zombies_p/tall zombie_transparent.png";
  labelMap["astronaut"] = ":/zombies_p/astronaut zombie_transparent.png";
  labelMap["purplehair"] = ":/zombies_p/purple hair zombie_transparent.png";

  speedMap["regular"] = 200;
  speedMap["bucked_head"] = 400;
  speedMap["leafhead"] = 200;
  speedMap["astronaut"] = 200;
  speedMap["purplehair"] = 200;
  speedMap["tall"] = 200;

}
MainWindow::~MainWindow()
{
    for (auto thread : moveThreads) {
           thread->quit();
           thread->wait();
           delete thread;
       }
    delete ui;
}



void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        QLabel *label = dynamic_cast<QLabel*>(childAt(event->pos()));
        if (label && (label->objectName() == "peashooter" || label->objectName() == "two_peashooter" ||label->objectName() =="walnut"||label->objectName() =="plum_mine"||label->objectName() =="jelapino"||label->objectName() =="boomerang"||label->objectName() == "regular" || label->objectName() == "bucked_head" ||label->objectName() =="leafhead"||label->objectName() =="tall"||label->objectName() =="astronaut"||label->objectName() =="purplehair")) {
            currentLabel = label;

            // Create a QDrag object
            QDrag *drag = new QDrag(this);
            QMimeData *mimeData = new QMimeData;

            // Set a textual representation of the object being dragged
            mimeData->setText("DraggedLabel");
            drag->setMimeData(mimeData);

            // Set the pixmap to be dragged (scaled to the label size)
            drag->setPixmap(label->pixmap().scaled(label->size(), Qt::KeepAspectRatio));

            // Start the drag operation
            Qt::DropAction dropAction = drag->exec(Qt::CopyAction | Qt::MoveAction);
        }
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (currentLabel && event->buttons() & Qt::LeftButton) {
        // Move the label with the mouse movement
        currentLabel->move(event->globalPos() - QPoint(currentLabel->width() / 2, currentLabel->height() / 2));
    }
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    // Accept drag events if they contain text indicating they are a "DraggedLabel"
    if (event->mimeData()->hasText() && event->mimeData()->text() == "DraggedLabel") {
        event->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent *event)
{
    // Handle drop events for "DraggedLabel"
    if (event->mimeData()->hasText() && event->mimeData()->text() == "DraggedLabel"&& ui->frame->geometry().contains(event->position().toPoint())) {
            QString labelName = currentLabel->objectName();
            if (labelMap.contains(labelName)&& speedMap.contains(labelName)) {
                QString pixmapPath = labelMap[labelName];
                int speed = speedMap[labelName];
                // Create a new QLabel at the drop position
                QLabel *newLabel = new QLabel(this);
                newLabel->setPixmap(QPixmap(pixmapPath).scaled(50, 50, Qt::KeepAspectRatio)); // Example size
                newLabel->setGeometry(event->position().toPoint().x(), event->position().toPoint().y(), 30, 40); // Example size
                newLabel->setScaledContents(true); // Ensure image scales to label size
                newLabel->show();

                // Start a new thread to move the label
                MoveThread *moveThread = new MoveThread(newLabel, ui->frame,speed, this);
                connect(moveThread, &MoveThread::gameOver, this, &MainWindow::gameOver);
                moveThreads.append(moveThread);
                moveThread->start();

                event->acceptProposedAction();
            }
        }

}
void MainWindow::gameOver()
{
    if (!gameEnded) {
           gameEnded = true; // Set the game ended flag
           QMessageBox::information(this, "Game Over", "A zombie reached the end of the frame. Game Over!");

           // Stop all running threads
           for (auto thread : moveThreads) {
               thread->quit();
               thread->wait();
           }

           // Optionally, you can close the application
           qApp->quit();
       }

}
