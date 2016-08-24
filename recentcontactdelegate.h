#ifndef RECENTCONTACTDELEGATE_H
#define RECENTCONTACTDELEGATE_H

#include <QObject>
#include <QMarginsF>
#include <QPainter>
#include <QStyledItemDelegate>

class RecentContactDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit RecentContactDelegate(QObject *parent = 0);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
    //bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) Q_DECL_OVERRIDE;

signals:
    void recentContactClicked();
    void removeChat(quint64 uid);
    void removeAllChat();

public slots:

private:
    void paintBackground(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paintAvatar(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paintNicknameAndMsgTime(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paintMsgContent(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paintUnreadNum(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // RECENTCONTACTDELEGATE_H
