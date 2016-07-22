#include <QApplication>
#include <QPalette>
#include <QDebug>
#include "contactmodel.h"
#include "contactdata.h"

ContactModel::ContactModel(QObject *parent)
    : QAbstractListModel(parent)
{
    beginResetModel();
    count = 0;
    endResetModel();
}

int ContactModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return count;
}

QVariant ContactModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= ContactData::instance()->getAllContact().size() || index.row() < 0)
        return QVariant();

    ContactInfo *contactInfo = ContactData::instance()->getAllContact().value(index.row());
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
        return contactInfo->lastMsgTime;
    case LastMsgContentRole:
        return contactInfo->lastMsgContent;
    default:
        return QVariant();
    }

    return QVariant();
}

bool ContactModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;

    if (index.row() >= ContactData::instance()->getAllContact().size() || index.row() < 0)
        return false;

    ContactInfo *contactInfo = ContactData::instance()->getAllContact().value(index.row());
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
    return true;
}

Qt::ItemFlags ContactModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index)
    return Qt::ItemIsSelectable | Qt::ItemNeverHasChildren | Qt::ItemIsEnabled;
}

bool ContactModel::canFetchMore(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    if (count < ContactData::instance()->getAllContact().size()) {
        return true;
    }
    return false;
}

void ContactModel::fetchMore(const QModelIndex &parent)
{
    Q_UNUSED(parent)
    int remainder = ContactData::instance()->getAllContact().size() - count;
    int itemsToFetch = qMin(10, remainder);

    beginInsertRows(QModelIndex(), count, count+itemsToFetch-1);

    count += itemsToFetch;

    endInsertRows();
}
