#ifndef RECENTCONTACTMODEL_H
#define RECENTCONTACTMODEL_H

#include <QAbstractListModel>
#include <QList>

class RecentContactModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum RecentContactModelRole {
        NicknameRole = Qt::DisplayRole,
        AvatarRole = Qt::DecorationRole,

        UnreadCountRole = Qt::UserRole,
        LastMsgTimeRole,
        LastMsgContentRole,
    };
    explicit RecentContactModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) Q_DECL_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;

signals:

public slots:
    void removeChat(quint64 id, bool isGroup);
    void updateLastMsg(quint64 id, bool isGroup, time_t time, QString msg);
    void updateUnreadCount(quint64 id, bool isGroup, int unread);

//protected:
//    bool canFetchMore(const QModelIndex &parent) const Q_DECL_OVERRIDE;
//    void fetchMore(const QModelIndex &parent) Q_DECL_OVERRIDE;

private:
    enum ListItemType{FriendItem, GroupItem, FriendRequest};
    QList<QPair<quint64,int>> chatContactList;
};

#endif // RECENTCONTACTMODEL_H
