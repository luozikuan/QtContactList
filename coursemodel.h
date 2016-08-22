#ifndef COURSEMODEL_H
#define COURSEMODEL_H

#include <QObject>
#include <QAbstractItemModel>

class CourseModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    enum CourseModelRole {
        CourseNameRole = Qt::DisplayRole,
        CoursePictureRole = Qt::DecorationRole,


    };

    explicit CourseModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;

signals:

public slots:

};

#endif // COURSEMODEL_H
