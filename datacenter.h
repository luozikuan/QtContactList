#ifndef DATACENTER_H
#define DATACENTER_H

#include <QObject>
#include <QMap>
#include <QColor>
#include <QVector>

struct PersonInfo
{
    quint64 uid;
    QString nickname;
    QColor avatarColor;
    QString sign;
    QString telephone;
};

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

struct ClassNode
{
    quint64 classId;
    QString className;
    int role;
    time_t startTime;
    qint64 length;
};

struct CourseNode
{
    quint64 schoolId;
    quint64 courseId;
    QString courseName;
    QString photoUrl;
    QVector<ClassNode*> classList;
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

    const QMap<QPair<quint64, bool>, RecentContactInfo*> &getRecentChatMap();
    RecentContactInfo *getRecentChatInfo(QPair<quint64, bool> contact);

    const QMap<quint64, QMap<quint64, CourseNode*>> getCourseList();
    CourseNode *getCourseNode(quint64 schoolId, quint64 courseId);
signals:

public slots:

private:
    explicit DataCenter(QObject *parent = 0);

    QMap<quint64, PersonInfo*> m_personInfoMap;
    QList<quint64> m_friendList;

    QMap<quint64, GroupInfo*> m_groupInfoMap;

    QMap<QPair<quint64, bool>, RecentContactInfo*> m_recentChatMap;

    QMap<quint64, QMap<quint64, CourseNode*>> courseList;
};

#endif // DATACENTER_H
