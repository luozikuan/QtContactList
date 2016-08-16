#ifndef CONTACTDELEGATE_H
#define CONTACTDELEGATE_H

#include <QObject>
#include <QMarginsF>
#include <QPainter>
#include <QStyledItemDelegate>

class ContactDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit ContactDelegate(QObject *parent = 0);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
    //bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) Q_DECL_OVERRIDE;

signals:
    void contactAvatarClicked();
    void contactInfoClicked();

public slots:

private:
    void paintBackground(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paintAvatar(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paintNickname(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paintUserSign(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    //void paintUnreadNum(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // CONTACTDELEGATE_H
