#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDrag>
#include <QMimeData>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
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

}
MainWindow::~MainWindow()
{
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
    if (event->mimeData()->hasText() && event->mimeData()->text() == "DraggedLabel") {
        // Retrieve the QLabel object at the drop position
        QLabel *label = dynamic_cast<QLabel *>(childAt(event->position().toPoint()));

        if (label) {
            // Move the label to the drop position
            label->move(event->position().toPoint());
        } else {
            // Create a new QLabel at the drop position
            QLabel *newLabel = new QLabel(this);
            newLabel->setPixmap(currentLabel->pixmap().scaled(100, 100, Qt::KeepAspectRatio)); // Example size
            newLabel->setGeometry(event->position().toPoint().x(), event->position().toPoint().y(), 100, 100); // Example size
            newLabel->setScaledContents(true); // Ensure image scales to label size
            newLabel->setObjectName(currentLabel->objectName()); // Set object name for identification
            newLabel->show();
        }

        event->acceptProposedAction();
    }
}
