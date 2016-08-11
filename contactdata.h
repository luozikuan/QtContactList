#ifndef CONTACTDATA_H
#define CONTACTDATA_H

#include <QObject>
#include <QMap>
#include <QColor>

struct ContactInfo
{
    quint64 id;
    bool isGroup;

    QString name;
    QColor avatarColor;
    QString userSign;

    int unreadCount;
    time_t lastMsgTime;
    QString lastMsgContent;
};
enum ContactRole {
    NicknameRole = Qt::DisplayRole,
    AvatarRole = Qt::DecorationRole,

    IdRole = Qt::UserRole,
    IsGroupRole,
    UserSignRole,
    UnreadCountRole,
    LastMsgTimeRole,
    LastMsgContentRole,
};

class ContactData : public QObject
{
    Q_OBJECT
public:
    static ContactData *instance();
    ~ContactData();
    const QMap<quint64, ContactInfo*>& getAllContact();
    QList<quint64> &getFriendList();
    ContactInfo *getPersonInfo(quint64 uid);

signals:

public slots:

private:
    explicit ContactData(QObject *parent = 0);

    QMap<quint64, ContactInfo*> contactList;
    QList<quint64> friendList;
};

#endif // CONTACTDATA_H
