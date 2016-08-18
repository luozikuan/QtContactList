#include <QDebug>
#include "recentcontactmodel.h"
#include "datacenter.h"

RecentContactModel::RecentContactModel(QObject *parent)
    : QAbstractListModel(parent)
{
    beginResetModel();
    chatContactList = DataCenter::instance()->getRecentChatMap().keys();
    qDebug() << "chatContactList size" << chatContactList.size();
    endResetModel();
}

int RecentContactModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return chatContactList.size();
}

QVariant RecentContactModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= chatContactList.size() || index.row() < 0)
        return QVariant();

    QPair<quint64, bool> contact = chatContactList.at(index.row());
    RecentContactInfo *contactInfo = DataCenter::instance()->getRecentChatInfo(contact);
    if (contact.second) { // group
        GroupInfo *group = DataCenter::instance()->getGroupInfo(contact.first);
        switch (role) {
        case NicknameRole:
            return group->groupName;
        case AvatarRole:
        {
            QVariant tmp;
            tmp.setValue(Qt::red);
            return tmp;
        }
        default:
            break;
        }
    } else { // person
        PersonInfo *person = DataCenter::instance()->getPersonInfo(contact.first);
        switch (role) {
        case NicknameRole:
            return person->nickname;
        case AvatarRole:
        {
            QVariant tmp;
            tmp.setValue(person->avatarColor);
            return tmp;
        }
        default:
            break;
        }
    }

    switch (role) {
    case UnreadCountRole:
        return contactInfo->unreadCount;
    case LastMsgTimeRole:
        return (quint64)contactInfo->lastMsgTime;
    case LastMsgContentRole:
        return contactInfo->lastMsgContent;
    default:
        return QVariant();
    }

    return QVariant();
}

bool RecentContactModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;

    if (index.row() >= chatContactList.size() || index.row() < 0)
        return false;

    QPair<quint64, bool> contact = chatContactList.at(index.row());
    RecentContactInfo *contactInfo = DataCenter::instance()->getRecentChatInfo(contact);
    QVector<int> changedRole;
    changedRole.append(role);

    switch (role) {
    case UnreadCountRole:
        contactInfo->unreadCount = value.toInt();
        break;
    case LastMsgTimeRole:
        contactInfo->lastMsgTime = value.toULongLong();
        break;
    case LastMsgContentRole:
        contactInfo->lastMsgContent = value.toString();
        break;
    default:
        return false;
    }

    emit dataChanged(index, index, changedRole);
    return true;
}

Qt::ItemFlags RecentContactModel::flags(const QModelIndex &index) const
{
    return QAbstractListModel::flags(index) | Qt::ItemIsSelectable | Qt::ItemNeverHasChildren | Qt::ItemIsEnabled;
}

void RecentContactModel::removeChat(quint64 id, bool isGroup)
{
    int row = chatContactList.indexOf({id, isGroup});
    beginRemoveRows(QModelIndex(), row, row);
    chatContactList.removeAt(row);
    endRemoveRows();
}

void RecentContactModel::updateLastMsg(quint64 id, bool isGroup, time_t time, QString msg)
{
    int row = chatContactList.indexOf({id, isGroup});
    QModelIndex index = this->createIndex(row, 0);

    setData(index, (quint64)time, RecentContactModel::LastMsgTimeRole);
    setData(index, msg, RecentContactModel::LastMsgContentRole);
}

void RecentContactModel::updateUnreadCount(quint64 id, bool isGroup, int unread)
{
    int row = chatContactList.indexOf({id, isGroup});
    QModelIndex index = this->createIndex(row, 0);

    setData(index, unread, RecentContactModel::UnreadCountRole);
}

//bool RecentContactModel::canFetchMore(const QModelIndex &parent) const
//{
//    Q_UNUSED(parent)
//    if (count < chatContactList.size()) {
//        return true;
//    }
//    return false;
//}

//void RecentContactModel::fetchMore(const QModelIndex &parent)
//{
//    Q_UNUSED(parent)
//    int remainder = chatContactList.size() - count;
//    int itemsToFetch = qMin(10, remainder); //remainder; //

//    beginInsertRows(QModelIndex(), count, count+itemsToFetch-1);

//    count += itemsToFetch;

//    endInsertRows();
//}

