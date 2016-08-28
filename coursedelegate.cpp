#include <qdrawutil.h>
#include <QPainter>
#include "coursedelegate.h"
#include "coursemodel.h"

const int CourseHeight = 50;
const int LessonHeight = 30;

CourseDelegate::CourseDelegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

void CourseDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

    //painter->draw
}

QSize CourseDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(100, 50);
//    QVariant lessonList = index.data(CourseModel::VisibleClassListRole);
//    return QSize(CourseHeight + LessonHeight * lessonNum, 0);
}

void CourseDelegate::paintBackground(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

}

void CourseDelegate::paintCoursePic(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

}

void CourseDelegate::paintCourseName(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

}

void CourseDelegate::paintProgress(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

}

void CourseDelegate::paintLesson(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

}

