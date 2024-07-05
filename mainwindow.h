#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDragEnterEvent>
#include <QDropEvent>
#include "plants.h"
#include <QMainWindow>
#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>
#include <QLabel>

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

private:
    Ui::MainWindow *ui;
      QLabel *currentLabel = nullptr;
};
#endif // MAINWINDOW_H
