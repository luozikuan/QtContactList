#include <QColor>
#include <QDateTime>
#include <QDebug>
#include "contactdata.h"

const int total = 5;

ContactData::ContactData(QObject *parent)
    : QObject(parent)
{
    contactList.reserve(total);
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

const QHash<int, ContactInfo *> &ContactData::getAllContact()
{
    return contactList;
}
