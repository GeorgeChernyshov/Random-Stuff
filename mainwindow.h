#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "shapedelegate.h"
#include <QMainWindow>
#include <QtWidgets>
#include <QtSql>
#include <QTableView>
#include <QPainter>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseDoubleClickEvent(QMouseEvent *e);

private slots:
    void on_addshape_clicked();
    void on_showall_toggled(bool checked);
    void on_hiderects_toggled(bool checked);
    void on_hideellipses_toggled(bool checked);
    void on_hidetriangles_toggled(bool checked);

    void on_connectbutton_clicked();

private:
    Ui::MainWindow *ui;
    QSqlTableModel* model;
    bool isshown[1000];
    int id = 0;
    int rectcount = 0;
    int ellipsecount = 0;
    int trianglecount = 0;
    QRect** rects;
    QRect** ellipses;
    QPolygon* triangles;
    QList<std::pair<int, std::pair<int, int>>> all;
    std::pair<int, std::pair<int, int>> current;
    ShapeDelegate* delegate;

    std::vector<int> connections[1000];
    int rectnum = 1;
    int ellipsenum = 0;
    int trianglenum = 0;
};

int findinbase(int data, QSqlQuery& query);
void baseconnect(int left, int right, QSqlQuery& query);

#endif // MAINWINDOW_H
