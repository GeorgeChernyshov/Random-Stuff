#ifndef RECTDELEGATE_H
#define RECTDELEGATE_H

#include <QWidget>
#include <QPainter>
#include <QVector>
#include <QStyledItemDelegate>

class ShapeDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    ShapeDelegate(QWidget *parent = 0) : QStyledItemDelegate(parent) {}

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const Q_DECL_OVERRIDE;

private:

};

#endif // RECTDELEGATE_H
