#ifndef DATACENTER_H
#define DATACENTER_H

#include <QObject>
#include <QMap>
#include <QColor>

struct PersonInfo
{
    quint64 uid;
    QString nickname;
    QColor avatarColor;
    QString sign;
    QString telephone;
};
//enum ContactRole {
//    NicknameRole = Qt::DisplayRole,
//    AvatarRole = Qt::DecorationRole,

//    IdRole = Qt::UserRole,
//    IsGroupRole,
//    UserSignRole,

//    UnreadCountRole,
//    LastMsgTimeRole,
//    LastMsgContentRole,
//};

struct GroupInfo
{
    quint64 gid;
    QString groupName;
    QList<quint64> memberList;
};

struct RecentContactInfo
{
    quint64 id;
    bool isGroup;

    int unreadCount;
    time_t lastMsgTime;
    QString lastMsgContent;
};

class DataCenter : public QObject
{
    Q_OBJECT
public:
    static DataCenter *instance();
    ~DataCenter();
    QList<quint64> &getFriendList();
    PersonInfo *getPersonInfo(quint64 uid);

    const QList<quint64> getGroupList();
    GroupInfo *getGroupInfo(quint64 gid);

    QList<QPair<quint64, bool>> &getRecentChatList();
    RecentContactInfo *getRecentChatInfo(QPair<quint64, bool> contact);

signals:

public slots:

private:
    explicit DataCenter(QObject *parent = 0);

    QMap<quint64, PersonInfo*> m_personInfoMap;
    QList<quint64> m_friendList;

    QMap<quint64, GroupInfo*> m_groupInfoMap;

    QMap<QPair<quint64, bool>, RecentContactInfo*> m_recentChatMap;
    QList<QPair<quint64, bool>> m_recentChatList;
};

#endif // DATACENTER_H
