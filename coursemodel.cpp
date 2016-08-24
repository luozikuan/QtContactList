#include <QDebug>
#include "coursemodel.h"
#include "datacenter.h"

CourseModel::CourseModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    beginResetModel();
    // TODO: set courseList data
    foreach (auto schoolCourses, DataCenter::instance()->getCourseList()) {
        foreach (auto course, schoolCourses) {
            courseList.append(qMakePair(course->schoolId, course->courseId));
        }
    }
    endResetModel();
    qDebug() << "courseList size" << courseList.size();
}

int CourseModel::rowCount(const QModelIndex &parent) const
{
    return courseList.size();
}

int CourseModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant CourseModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= courseList.size() || index.row() < 0)
        return QVariant();

    QPair<quint64, quint64> courseInfo = courseList.at(index.row());
    CourseNode *courseNode = DataCenter::instance()->getCourseNode(courseInfo.first, courseInfo.second);


    return QVariant();
}

QModelIndex CourseModel::index(int row, int column, const QModelIndex &parent) const
{
    return QModelIndex();
}

QModelIndex CourseModel::parent(const QModelIndex &index) const
{
    return QModelIndex();
}
