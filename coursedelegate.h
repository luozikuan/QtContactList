#ifndef COURSEDELEGATE_H
#define COURSEDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>

class CourseDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit CourseDelegate(QObject *parent = 0);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
signals:

public slots:

private:
    void paintBackground(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paintCoursePic(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paintCourseName(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paintProgress(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paintLesson(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // COURSEDELEGATE_H
