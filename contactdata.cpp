#include <QColor>
#include <QDateTime>
#include <QDebug>
#include "contactdata.h"

const int total = 99999;

ContactData::ContactData(QObject *parent)
    : QObject(parent)
{
    for (int i = 0; i < total; i++) {
        ContactInfo *contactInfo = new ContactInfo;
        contactInfo->id = i;
        contactInfo->isGroup = false;
        contactInfo->name = QString("nickname of %1").arg(i);
        contactInfo->avatarColor = Qt::GlobalColor(4+qrand()%17); // 2~18   2+(0~16)
        contactInfo->userSign = QString("UserSign of %1").arg(i);

        contactInfo->unreadCount = i;
        contactInfo->lastMsgTime = QDateTime::currentDateTime().toTime_t() - qrand() % (86400 * 7);
        contactInfo->lastMsgContent = QString("Chated with someone");

        contactList.insert(i, contactInfo);
        if (i % 2 == 0) {
            friendList.append(i);
        }
    }
    qDebug() << "created";
}

ContactData *ContactData::instance()
{
    static ContactData s;
    return &s;
}

ContactData::~ContactData()
{
    qDeleteAll(this->contactList);
    this->contactList.clear();
}

const QMap<quint64, ContactInfo *> &ContactData::getAllContact()
{
    return contactList;
}

QList<quint64> &ContactData::getFriendList()
{
    return friendList;
}

ContactInfo *ContactData::getPersonInfo(quint64 uid)
{
    auto it = contactList.find(uid);
    if (it != contactList.end()) {
        return it.value();
    }
    return Q_NULLPTR;
}
