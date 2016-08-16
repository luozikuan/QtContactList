#include <QDebug>
#include "recentcontactmodel.h"
#include "datacenter.h"

RecentContactModel::RecentContactModel(QObject *parent)
    : QObject(parent)
{
    beginResetModel();
    count = 0;
    endResetModel();
}

int RecentContactModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return count;
}

QVariant RecentContactModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= DataCenter::instance()->getFriendList().size() || index.row() < 0)
        return QVariant();

    quint64 uid = DataCenter::instance()->getFriendList().at(index.row());
    ContactInfo *contactInfo = DataCenter::instance()->getContactInfo(uid);
    QVariant tmp;
    switch (role) {
    case NicknameRole:
        return contactInfo->name;
    case AvatarRole:
        tmp.setValue(contactInfo->avatarColor);
        return tmp;
    case IdRole:
        return contactInfo->id;
    case IsGroupRole:
        return contactInfo->isGroup;
    case UserSignRole:
        return contactInfo->userSign;
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

    if (index.row() >= DataCenter::instance()->getFriendList().size() || index.row() < 0)
        return false;

    quint64 uid = DataCenter::instance()->getFriendList().at(index.row());
    ContactInfo *contactInfo = DataCenter::instance()->getContactInfo(uid);

    QVector<int> changedRole;
    changedRole.append(role);

    switch (role) {
    case NicknameRole:
        contactInfo->name = value.toString();
        break;
    case AvatarRole:
        contactInfo->avatarColor = value.value<QColor>();
        break;
    case IdRole:
        contactInfo->id = value.toULongLong();
        break;
    case IsGroupRole:
        contactInfo->isGroup = value.toBool();
        break;
    case UserSignRole:
        contactInfo->userSign = value.toString();
        break;
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

bool RecentContactModel::canFetchMore(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    if (count < DataCenter::instance()->getFriendList().size()) {
        return true;
    }
    return false;
}

void RecentContactModel::fetchMore(const QModelIndex &parent)
{
    Q_UNUSED(parent)
    int remainder = DataCenter::instance()->getFriendList().size() - count;
    int itemsToFetch = remainder; // qMin(10, remainder);

    beginInsertRows(QModelIndex(), count, count+itemsToFetch-1);

    count += itemsToFetch;

    endInsertRows();
}

