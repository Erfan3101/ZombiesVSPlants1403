#ifndef MOVETHREAD_H
#define MOVETHREAD_H

#include <QThread>
#include <QLabel>

class MoveThread : public QThread
{
    Q_OBJECT

public:
    explicit MoveThread(QLabel *label, QWidget *field, int speed, QObject *parent = nullptr);
      void run() override;

signals:
    void gameOver();

private:
    QLabel *label;
    int start_x, start_y, field_width;
      QWidget *field;
      int speed;
};

#endif // MOVETHREAD_H
