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

        ClassNameRole = Qt::UserRole,
        ClassStartTimeRole,
        ClassLengthRole,
        ClassIdentityRole,
    };

    explicit CourseModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QModelIndex parent(const QModelIndex &index) const Q_DECL_OVERRIDE;

signals:

public slots:

private:
    QList<QPair<quint64, quint64>> courseList;
};

#endif // COURSEMODEL_H
