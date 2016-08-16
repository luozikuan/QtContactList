#include <QDebug>
#include "contactmodel.h"
#include "datacenter.h"

ContactModel::ContactModel(QObject *parent)
    : QAbstractListModel(parent)
{
    beginResetModel();
    foreach (quint64 gid, DataCenter::instance()->getGroupList()) {
        contactList.append({gid, false});
    }
    foreach (quint64 uid, DataCenter::instance()->getFriendList()) {
        contactList.append({uid, false});
    }
    qDebug() << "contactList size" << contactList.size();
    endResetModel();
}

int ContactModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return contactList.size();
}

QVariant ContactModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= contactList.size() || index.row() < 0)
        return QVariant();

    QPair<quint64,bool> contact = contactList.at(index.row());
    if (contact.second) { // group
        GroupInfo *group = DataCenter::instance()->getGroupInfo(contact.first);
        if (group == Q_NULLPTR) {
            qDebug() << "group is null";
            return QVariant();
        }
        switch (role) {
        case NicknameRole:
            return group->groupName;
        case AvatarRole:
        {
            QVariant tmp;
            tmp.setValue(Qt::black);
            return tmp;
        }
        case UserSignRole:
            return QString("group");
        default:
            return QVariant();
        }
    } else { // friend
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
        case UserSignRole:
            return person->sign;
        default:
            return QVariant();
        }
    }

    return QVariant();
}

//bool ContactModel::setData(const QModelIndex &index, const QVariant &value, int role)
//{
//    if (!index.isValid())
//        return false;

//    if (index.row() >= contactList.size() || index.row() < 0)
//        return false;

//    quint64 uid = DataCenter::instance()->getFriendList().at(index.row());
//    ContactInfo *contactInfo = DataCenter::instance()->getContactInfo(uid);

//    QVector<int> changedRole;
//    changedRole.append(role);

//    switch (role) {
//    case NicknameRole:
//        contactInfo->name = value.toString();
//        break;
//    case AvatarRole:
//        contactInfo->avatarColor = value.value<QColor>();
//        break;
//    case IdRole:
//        contactInfo->id = value.toULongLong();
//        break;
//    case IsGroupRole:
//        contactInfo->isGroup = value.toBool();
//        break;
//    case UserSignRole:
//        contactInfo->userSign = value.toString();
//        break;
//    case UnreadCountRole:
//        contactInfo->unreadCount = value.toInt();
//        break;
//    case LastMsgTimeRole:
//        contactInfo->lastMsgTime = value.toULongLong();
//        break;
//    case LastMsgContentRole:
//        contactInfo->lastMsgContent = value.toString();
//        break;
//    default:
//        return false;
//    }

//    emit dataChanged(index, index, changedRole);
//    return true;
//}

//Qt::ItemFlags ContactModel::flags(const QModelIndex &index) const
//{
//    return QAbstractListModel::flags(index) | Qt::ItemIsSelectable | Qt::ItemNeverHasChildren | Qt::ItemIsEnabled;
//}

//bool ContactModel::canFetchMore(const QModelIndex &parent) const
//{
//    Q_UNUSED(parent)
//    if (count < DataCenter::instance()->getFriendList().size()) {
//        return true;
//    }
//    return false;
//}

//void ContactModel::fetchMore(const QModelIndex &parent)
//{
//    Q_UNUSED(parent)
//    int remainder = DataCenter::instance()->getFriendList().size() - count;
//    int itemsToFetch = remainder; // qMin(10, remainder);

//    beginInsertRows(QModelIndex(), count, count+itemsToFetch-1);

//    count += itemsToFetch;

//    endInsertRows();
//}
