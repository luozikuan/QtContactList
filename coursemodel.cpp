#include "coursemodel.h"

CourseModel::CourseModel(QObject *parent) : QAbstractItemModel(parent)
{

}

int CourseModel::rowCount(const QModelIndex &parent) const
{
    return 0;
}

QVariant CourseModel::data(const QModelIndex &index, int role) const
{
    return QVariant();
}
