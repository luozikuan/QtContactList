#include <QColor>
#include <QDateTime>
#include <QDebug>
#include "datacenter.h"

const int personTotal = 100000;
const int frientTotal = 4000;
const int groupTotal = 3000;
const int courseTotal = 30;
const int classTotal = 30;

DataCenter::DataCenter(QObject *parent)
    : QObject(parent)
{
    for (int i = 0; i < personTotal; i++) {
        PersonInfo *person = new PersonInfo;
        person->uid = i;
        person->nickname = QString("%1's nickname").arg(i);
        person->avatarColor = Qt::GlobalColor(4+qrand()%17); // 2~18   2+(0~16)
        person->sign = QString("UserSign of %1").arg(i);
        person->telephone = QString::number(i);
        m_personInfoMap.insert(i, person);
    }

    for (int i = 0; i < frientTotal; i++) {
        quint64 uid = 2 *i;
        m_friendList.append(uid);

        RecentContactInfo *chatInfo = new RecentContactInfo;
        chatInfo->id = uid;
        chatInfo->isGroup = false;
        chatInfo->unreadCount = i;
        chatInfo->lastMsgTime = QDateTime::currentDateTime().toTime_t() - qrand() % (86400 * 7);
        chatInfo->lastMsgContent = QString("Chated with %1").arg(uid);
        m_recentChatMap[qMakePair(uid, false)] = chatInfo;
    }

    for (int i = 0; i < groupTotal; i++) {
        GroupInfo *group = new GroupInfo;
        quint64 gid = personTotal + i;
        group->gid = gid;
        group->groupName = QString("%1's group name(%2)").arg(i).arg(group->gid);
        group->memberList.append(i);
        group->memberList.append(i+1);
        group->memberList.append(i+2);
        group->memberList.append(i+3);
        group->memberList.append(i+5);

        m_groupInfoMap.insert(group->gid, group);

        RecentContactInfo *chatInfo = new RecentContactInfo;
        chatInfo->id = gid;
        chatInfo->isGroup = true;
        chatInfo->unreadCount = i;
        chatInfo->lastMsgTime = QDateTime::currentDateTime().toTime_t() - qrand() % (86400 * 7);
        chatInfo->lastMsgContent = QString("Chated in group %1").arg(gid);
        m_recentChatMap[qMakePair(gid, true)] = chatInfo;
    }

//    for (int i = 0; i < courseTotal; i++) {
//        CourseNode *course = new CourseNode;
//        course->schoolId = i;
//        course->courseId = i * 10 + i;
//        course->courseName = QString("course %1-%2").arg(course->schoolId).arg(course->courseId);
//        course->photoUrl = "http://www.w3school.com.cn/i/eg_cute.gif";

//        for (int j = 0; j < classTotal; j++) {
//            ClassNode *classNode = new ClassNode;
//            classNode->classId = i;
//            //classNode->
//        }
//    }
    qDebug() << "created";
}

DataCenter *DataCenter::instance()
{
    static DataCenter s;
    return &s;
}

DataCenter::~DataCenter()
{
    qDeleteAll(m_personInfoMap);
    m_personInfoMap.clear();

    qDeleteAll(m_groupInfoMap);
    m_groupInfoMap.clear();

    qDeleteAll(m_recentChatMap);
    m_recentChatMap.clear();
}

QList<quint64> &DataCenter::getFriendList()
{
    return m_friendList;
}

PersonInfo *DataCenter::getPersonInfo(quint64 uid)
{
    auto it = m_personInfoMap.find(uid);
    if (it != m_personInfoMap.end()) {
        return it.value();
    }
    return Q_NULLPTR;
}

const QList<quint64> DataCenter::getGroupList()
{
    return m_groupInfoMap.keys();
}

GroupInfo *DataCenter::getGroupInfo(quint64 gid)
{
    auto it = m_groupInfoMap.find(gid);
    if (it != m_groupInfoMap.end()) {
        return it.value();
    }
    return Q_NULLPTR;
}

const QMap<QPair<quint64, bool>, RecentContactInfo *> &DataCenter::getRecentChatMap()
{
    return m_recentChatMap;
}

RecentContactInfo *DataCenter::getRecentChatInfo(QPair<quint64, bool> contact)
{
    auto it = m_recentChatMap.find(contact);
    if (it != m_recentChatMap.end()) {
        return it.value();
    }
    return Q_NULLPTR;
}
