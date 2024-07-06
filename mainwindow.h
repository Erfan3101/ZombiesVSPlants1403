#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QMouseEvent>
#include <QTimer>
#include <vector>
#include <QMessageBox>
#include "movethread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:

private slots:

    //void mousePressEvent(QMouseEvent *event) override;
        void mousePressEvent(QMouseEvent *event) override;
          void mouseMoveEvent(QMouseEvent *event) override;
          void dragEnterEvent(QDragEnterEvent *event) override;
          void dropEvent(QDropEvent *event) override;

      //void moveLabel();
private:
    Ui::MainWindow *ui;
    //void setupLabels();
      QLabel *currentLabel = nullptr;
      QTimer *moveTimer;
       // QLabel *movingLabel;
       // std::vector<QLabel *> movingLabels;
      QMap<QString, int> speedMap; // Mapping source labels to specific speeds
        QMap<QString, QString> labelMap;
        QMap<QString,QString>plantslabel;// Mapping source labels to specific appearing labels
        QVector<MoveThread*> moveThreads;
         bool gameEnded;
         // Define grid layout (adjust cell size based on your image dimensions)
         int parentWidth;
         int parentHeight ;
         int centerX ;
         int centerY ;
          int gridRows ;
          int gridCols ;
          int cellWidth ;
          int cellHeight ;
          QPoint snapToCell(const QPoint &pos);
public slots:
    void gameOver();
};


#endif // MAINWINDOW_H
