#include "shapedelegate.h"

void ShapeDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                         const QModelIndex &index) const
{
    if(index.column() < 3){
        QStyledItemDelegate::paint(painter, option, index);
    }else{
        QRect rect = option.rect;
        int type = 0;
        const QAbstractItemModel* model = index.model();
        QString str = model->data(model->index(index.row(), index.column() - 2, index.parent()), Qt::DisplayRole).toString();
        if(str == "Rect") type = 1;
        if(str == "Ellipse") type = 2;
        if(str == "Triangle") type = 3;
        if(index.data().toInt() > 0){
            if(type == 1) painter->drawRect(rect.left() + 1, rect.top() + 4, 20, 20);
            if(type == 2) painter->drawEllipse(rect.left() + 1, rect.top() + 4, 20, 20);
            if(type == 3){
                QPolygon F;
                F.putPoints(0, 3, rect.left() + 11, rect.top() + 4, rect.left() + 1, rect.top() + 24, rect.left() + 21, rect.top() + 24);
                painter->drawConvexPolygon(F);
            }
        }
        if(index.data().toInt() > 3){
            if(type == 1) painter->drawRect(rect.left() + 25, rect.top() + 4, 20, 20);
            if(type == 2) painter->drawEllipse(rect.left() + 25, rect.top() + 4, 20, 20);
            if(type == 3){
                QPolygon F;
                F.putPoints(0, 3, rect.left() + 35, rect.top() + 4, rect.left() + 25, rect.top() + 24, rect.left() + 45, rect.top() + 24);
                painter->drawConvexPolygon(F);
            }
        }
        if(index.data().toInt() > 10){
            if(type == 1) painter->drawRect(rect.left() + 49, rect.top() + 4, 20, 20);
            if(type == 2) painter->drawEllipse(rect.left() + 49, rect.top() + 4, 20, 20);
            if(type == 3){
                QPolygon F;
                F.putPoints(0, 3, rect.left() + 59, rect.top() + 4, rect.left() + 49, rect.top() + 24, rect.left() + 69, rect.top() + 24);
                painter->drawConvexPolygon(F);
            }
        }
    }
}
