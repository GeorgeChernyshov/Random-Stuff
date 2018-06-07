#include "mainwindow.h"
#include "ui_mainwindow.h"

//Initializing and creating the database
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    rects = new QRect*[1000];
    ellipses = new QRect*[1000];
    triangles = new QPolygon[1000];
    ui->setupUi(this);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(":memory:");
    db.open();

    //Aside from creating a database, we create one rectangle, just for the sakr of it
    QSqlQuery query;
    query.exec("create table shapes (id int primary key, type varchar(20), connections varchar(100), number int)");
    query.exec("insert into shapes values(0, \"Rect\", null, 1)");
    model = new QSqlTableModel;
    model->setParent(this);

    model->setTable("shapes");
    model->select();

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Connections"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Number"));

    ui->tableView->setModel(model);
//This is for choosing which item to create
    ui->shapetype->insertItem(0, "Rect");
    ui->shapetype->insertItem(1, "Ellipse");
    ui->shapetype->insertItem(2, "Triangle");

    ui->showall->setChecked(1);
    for(int i = 0; i < 1000; i++) isshown[i] = 1;
    ui->HeightspinBox->setRange(1, 500);
    ui->WidthspinBox->setRange(1, 500);
    ui->HeightspinBox->setValue(100);
    ui->WidthspinBox->setValue(100);
    /*Ok, I guess somewhere here I should explain the main logic. There are three arrays: of rectangles, ellipses and triangles
    To connect them all into one instance there is a list of everything. List node contains type of shape, its index in array
    and its ID, unigue for each item*/
    std::pair<int, std::pair<int, int>> p;
    p.first = id++;
    rects[rectcount] = new QRect(700, 100+10*id, ui->WidthspinBox->value(), ui->HeightspinBox->value());
    p.second.first = 0;
    p.second.second = rectcount++;
    all.push_back(p);
    delegate = new ShapeDelegate;
    ui->tableView->setItemDelegate(delegate);
}

MainWindow::~MainWindow()
{
    delete ui;
}
//Repainting everything
void MainWindow::paintEvent(QPaintEvent *e){
    QPainter painter(this);
    //Note that we're using the main list and try to evade the usage of three arrays
    for(auto it = all.begin(); it != all.end(); ++it){
       std::pair<int, std::pair<int, int>> p = *it;
       if(p.second.first == 0 && isshown[p.first]){
           painter.drawRect(*rects[p.second.second]);
       } else if(p.second.first == 1 && isshown[p.first]){
           painter.drawEllipse(*ellipses[p.second.second]);
       } else if(p.second.first == 2 && isshown[p.first]){
           painter.drawConvexPolygon(triangles[p.second.second]);
       }
    }
    for(auto it = all.begin(); it != all.end(); ++it){
       std::pair<int, std::pair<int, int>> p = *it;
       QPoint beg, end;
       if(p.second.first == 0 && isshown[p.first]){
           beg = rects[p.second.second]->center();
       } else if(p.second.first == 1 && isshown[p.first]){
           beg = ellipses[p.second.second]->center();
       } else if(p.second.first == 2 && isshown[p.first]){
           //I dont like how this is done, but it is the best I came up with
           int X = triangles[p.second.second].point(0).x() + triangles[p.second.second].point(1).x() + triangles[p.second.second].point(2).x();
           X /= 3;
           int Y = triangles[p.second.second].point(0).y() + triangles[p.second.second].point(1).y() + triangles[p.second.second].point(2).y();
           Y /= 3;
           beg.setX(X);
           beg.setY(Y);
       }
       //And this is just code copying. Should've spend more time on this
       QSqlQuery query;
       query.prepare("select connections from shapes where id = :id");
       query.bindValue(":id", p.first);
       query.exec();
       query.next();
       QString str = query.value(0).toString();
       QStringList list = str.split(" ");
       for(int i = 0; i < list.size(); i++){
           bool found = 0;
           for(auto it2 = it; it2 != all.end(); ++it2){
               std::pair<int, std::pair<int, int>> p2 = *it2;
               if(p2.first == list[i].toInt() && list[i] != ""){
                   found = 1;
                   if(p2.second.first == 0 && isshown[p2.first]){
                       end = rects[p2.second.second]->center();
                   } else if(p2.second.first == 1 && isshown[p2.first]){
                       end = ellipses[p2.second.second]->center();
                   } else if(p2.second.first == 2 && isshown[p.first]){
                       int X = triangles[p2.second.second].point(0).x() + triangles[p2.second.second].point(1).x() + triangles[p2.second.second].point(2).x();
                       X /= 3;
                       int Y = triangles[p2.second.second].point(0).y() + triangles[p2.second.second].point(1).y() + triangles[p2.second.second].point(2).y();
                       Y /= 3;
                       end.setX(X);
                       end.setY(Y);
                   }
                   break;
               }
           }
           //50 lines of code above were just for this
           if(found) painter.drawLine(beg, end);
       }
    }
}
//When lmb is pressed, check all of the shapes to choose the one to hide or remove
//Dont be scared with math below, it is really simple
void MainWindow::mousePressEvent(QMouseEvent *e){
    std::pair<int, std::pair<int, int>> current;
    bool found = 0;
    for(auto it = all.begin(); it != all.end(); ++it){
       std::pair<int, std::pair<int, int>> p = *it;
       if(p.second.first == 0){
           if(rects[p.second.second]->contains(e->pos()) && isshown[p.first]){
               current = p;
               found = 1;
           }
       } else if(p.second.first == 1){
           if(ellipses[p.second.second]->contains(e->pos()) && isshown[p.first]){
               double h = (e->pos().y() - ellipses[p.second.second]->center().y());
               h = h > 0 ? h : -h;
               double w = (e->pos().x() - ellipses[p.second.second]->center().x());
               w = w > 0 ? w : -w;
               double h1 = 2*(double)(e->pos().y() - ellipses[p.second.second]->center().y())/ellipses[p.second.second]->height();
               double ah1 = asin(h1);
               double w1 = (cos(ah1)*ellipses[p.second.second]->width())/2;
               double w2 = 2*(double)(e->pos().x() - ellipses[p.second.second]->center().x())/ellipses[p.second.second]->width();
               double aw2 = acos(w2);
               double h2 = (sin(aw2)*ellipses[p.second.second]->height())/2;
               if(w < w1 && h < h2){
                   current = p;
                   found = 1;
               }
           }
       } else if(p.second.first == 2){
           int Y = e->pos().y() - triangles[p.second.second].point(0).y();
           double C = static_cast<double>(triangles[p.second.second].point(1).x() - triangles[p.second.second].point(0).x())/(triangles[p.second.second].point(1).y() - triangles[p.second.second].point(0).y());
           if(e->pos().x() - (triangles[p.second.second].point(0).x()) < Y*C && e->pos().x() - (triangles[p.second.second].point(0).x()) > -Y*C
                   && triangles[p.second.second].point(1).y() > e->pos().y() && triangles[p.second.second].point(0).y() < e->pos().y() && isshown[p.first]){
               current = p;
               found = 1;
           }
       }
    }
    if(found){
        if(e->button() == Qt::RightButton){
            isshown[current.first] = 0;
        }else{
            all.removeOne(current);
            all.push_back(current);
        }
    }
    repaint();
}

void MainWindow::mouseMoveEvent(QMouseEvent *e){
    std::pair<int, std::pair<int, int>> p = all.back();
    if(p.second.first == 0){
        rects[p.second.second]->moveTo(e->pos());
    }else if(p.second.first == 1){
        ellipses[p.second.second]->moveTo(e->pos());
    }else if(p.second.first == 2){
        triangles[p.second.second].translate(e->pos() - triangles[p.second.second].point(0));
    }
    repaint();
}
//Code repeating again. I'm sorry
//Won't even comment the rest. Screw that
void MainWindow::mouseDoubleClickEvent(QMouseEvent *e){
    std::pair<int, std::pair<int, int>> current;
    for(auto it = all.begin(); it != all.end(); ++it){
       std::pair<int, std::pair<int, int>> p = *it;
       if(p.second.first == 0){
           if(rects[p.second.second]->contains(e->pos()) && isshown[p.first]) current = p;
       } else if(p.second.first == 1){
           if(ellipses[p.second.second]->contains(e->pos()) && isshown[p.first]){
               double h = (e->pos().y() - ellipses[p.second.second]->center().y());
               h = h > 0 ? h : -h;
               double w = (e->pos().x() - ellipses[p.second.second]->center().x());
               w = w > 0 ? w : -w;
               double h1 = 2*(e->pos().y() - ellipses[p.second.second]->center().y())/ellipses[p.second.second]->height();
               double ah1 = asin(h1);
               double w1 = (cos(ah1)*ellipses[p.second.second]->width())/2;
               double w2 = 2*(e->pos().x() - ellipses[p.second.second]->center().x())/ellipses[p.second.second]->width();
               double aw2 = acos(w2);
               double h2 = (sin(aw2)*ellipses[p.second.second]->height())/2;
               if(w < w1 && h < h2) current = p;
           }
       } else if(p.second.first == 2){
           int Y = e->pos().y() - triangles[p.second.second].point(0).y();
           double C = static_cast<double>(triangles[p.second.second].point(1).x() - triangles[p.second.second].point(0).x())/(triangles[p.second.second].point(1).y() - triangles[p.second.second].point(0).y());
           if(e->pos().x() - (triangles[p.second.second].point(0).x()) < Y*C && e->pos().x() -
                   (triangles[p.second.second].point(0).x()) > -Y*C && triangles[p.second.second].point(1).y() > e->pos().y() && triangles[p.second.second].point(0).y() < e->pos().y() && isshown[p.first]){
               current = p;
           }
       }
    }
    all.removeOne(current);
    QSqlQuery query;
    query.prepare("delete from shapes where id = :id");
    query.bindValue(":id", current.first);
    query.exec();
    if(current.second.first == 0){
        query.exec("select count(*) from shapes where type = 'Rect'");
        query.next();
        rectnum = query.value(0).toInt();
        query.prepare("update shapes set number = :num where type ='Rect'");
        query.bindValue(":num", rectnum);
    }else if(current.second.first == 1){
        query.prepare("update shapes set number = :num where type ='Ellipse'");
        query.bindValue(":num", --ellipsenum);
    }else{
        query.prepare("update shapes set number = :num where type ='Triangle'");
        query.bindValue(":num", --trianglenum);
    }
    query.exec();
    query.exec("select count(*) from shapes");
    query.next();
    int num = query.value(0).toInt();
    query.exec("select id, connections from shapes");
    query.next();
    QSqlQuery query2;
    for(int i = 0; i < num; i++){
        QString str = query.value(1).toString();
        str.replace(QString::number(current.first), "");
        str.replace("  ", " ");
        int curid = query.value(0).toInt();
        query2.prepare("update shapes set connections = :con where id = :id");
        query2.bindValue(":con", str);
        query2.bindValue(":id", curid);
        query2.exec();
        query.next();
    }
    model->select();
    repaint();
}

void MainWindow::on_addshape_clicked()
{
    QSqlQuery query;
    query.prepare("insert into shapes values(:id, :type, null, :num)");
    query.bindValue(":id", id);
    query.bindValue(":type", ui->shapetype->currentText());
    std::pair<int, std::pair<int, int>> p;
    p.first = id++;
    if(ui->shapetype->currentText() == "Rect"){
        rects[rectcount] = new QRect(700, 100+10*id, ui->WidthspinBox->value(), ui->HeightspinBox->value());
        p.second.first = 0;
        p.second.second = rectcount++;
        query.bindValue(":num", rectnum++);
        query.exec();
        query.prepare("update shapes set number = :num where type ='Rect'");
        query.bindValue(":num", rectnum);
    }else if(ui->shapetype->currentText() == "Ellipse"){
        ellipses[ellipsecount] = new QRect(700, 100+10*id, ui->WidthspinBox->value(), ui->HeightspinBox->value());
        p.second.first = 1;
        p.second.second = ellipsecount++;
        query.bindValue(":num", ellipsenum++);
        query.exec();
        query.prepare("update shapes set number = :num where type ='Ellipse'");
        query.bindValue(":num", ellipsenum);
    }else{
        triangles[trianglecount].putPoints(0, 3, 700 + ui->WidthspinBox->value()/2, 100 + (10*id),
                700 + ui->WidthspinBox->value(), 100 + (10*id) + ui->HeightspinBox->value(), 700, 100 + (10*id) + ui->HeightspinBox->value());
        p.second.first = 2;
        p.second.second = trianglecount++;
        query.bindValue(":num", trianglenum++);
        query.exec();
        query.prepare("update shapes set number = :num where type ='Triangle'");
        query.bindValue(":num", trianglenum);
    }
    query.exec();
    all.push_back(p);
    model->select();
    repaint();
}

void MainWindow::on_showall_toggled(bool checked)
{
    if(checked){
        ui->hiderects->setChecked(1);
        ui->hideellipses->setChecked(1);
        ui->hidetriangles->setChecked(1);
        for(auto it = all.begin(); it != all.end(); ++it){
           std::pair<int, std::pair<int, int>> p = *it;
           isshown[p.first] = 1;
        }
    }else{
        ui->hiderects->setChecked(0);
        ui->hideellipses->setChecked(0);
        ui->hidetriangles->setChecked(0);
        for(auto it = all.begin(); it != all.end(); ++it){
           std::pair<int, std::pair<int, int>> p = *it;
           isshown[p.first] = 0;
        }
    }
    repaint();
}

void MainWindow::on_hiderects_toggled(bool checked)
{
    if(checked){
        for(auto it = all.begin(); it != all.end(); ++it){
           std::pair<int, std::pair<int, int>> p = *it;
           if(p.second.first == 0){
               isshown[p.first] = 1;
           }
        }
    }else{
        for(auto it = all.begin(); it != all.end(); ++it){
           std::pair<int, std::pair<int, int>> p = *it;
           if(p.second.first == 0){
               isshown[p.first] = 0;
           }
        }
    }
    repaint();
}

void MainWindow::on_hideellipses_toggled(bool checked)
{
    if(checked){
        for(auto it = all.begin(); it != all.end(); ++it){
           std::pair<int, std::pair<int, int>> p = *it;
           if(p.second.first == 1){
               isshown[p.first] = 1;
           }
        }
    }else{
        for(auto it = all.begin(); it != all.end(); ++it){
           std::pair<int, std::pair<int, int>> p = *it;
           if(p.second.first == 1){
               isshown[p.first] = 0;
           }
        }
    }
    repaint();
}

void MainWindow::on_hidetriangles_toggled(bool checked)
{
    if(checked){
        for(auto it = all.begin(); it != all.end(); ++it){
           std::pair<int, std::pair<int, int>> p = *it;
           if(p.second.first == 2){
               isshown[p.first] = 1;
           }
        }
    }else{
        for(auto it = all.begin(); it != all.end(); ++it){
           std::pair<int, std::pair<int, int>> p = *it;
           if(p.second.first == 2){
               isshown[p.first] = 0;
           }
        }
    }
    repaint();
}

void MainWindow::on_connectbutton_clicked()
{
    QSqlQuery query;
    int left = ui->leftcon->text().toInt();
    int right = ui->rightcon->text().toInt();
    int leftexists = findinbase(left, query);
    int rightexists = findinbase(right, query);
    if(leftexists && rightexists && left != right){
        bool connected = 0;
        for(unsigned int i = 0; i < connections[left].size(); i++){
            if(connections[left][i] == right) connected = 1;
        }
        if(!connected){
            connections[left].push_back(right);
            connections[right].push_back(left);
            baseconnect(left, right, query);
            baseconnect(right, left, query);
            model->select();
            repaint();
        }
    }
}

int findinbase(int data, QSqlQuery& query){
    query.prepare("select count(*) from shapes where id = :id");
    query.bindValue(":id", data);
    query.exec();
    query.next();
    return query.value(0).toInt();
}

void baseconnect(int left, int right, QSqlQuery& query){
    query.prepare("select connections from shapes where id = :id");
    query.bindValue(":id", left);
    query.exec();
    query.next();
    QString str = query.value(0).toString();
    if(str != "") str.append(" ");
    str.append(QString::number(right));
    query.prepare("update shapes set connections = :con where id = :id");
    query.bindValue(":con", str);
    query.bindValue(":id", left);
    query.exec();
}
