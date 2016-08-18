#include <QDebug>
#include "contactmodel.h"
#include "datacenter.h"

ContactModel::ContactModel(QObject *parent)
    : QAbstractListModel(parent)
{
    beginResetModel();
    foreach (quint64 uid, DataCenter::instance()->getFriendList()) {
        contactList.append({uid, false});
    }
    foreach (quint64 gid, DataCenter::instance()->getGroupList()) {
        contactList.append({gid, true});
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

void ContactModel::onFriendInfoChanged(quint64 uid)
{
    int row = contactList.indexOf({uid, false});
    QModelIndex index = this->createIndex(row, 0);
    QVector<int> changedRole;
    changedRole << ContactModel::NicknameRole
                << ContactModel::AvatarRole
                << ContactModel::UserSignRole;
    emit dataChanged(index, index, changedRole);
}

void ContactModel::onGroupInfoChanged(quint64 gid)
{
    Q_UNUSED(gid)
}

void ContactModel::onAddFriend(quint64 uid)
{
    beginInsertRows(QModelIndex(), this->rowCount(), this->rowCount());
    contactList.append({uid, false});
    endInsertRows();
}

void ContactModel::onRemoveFriend(quint64 uid)
{
    int row = contactList.indexOf({uid, false});
    beginRemoveRows(QModelIndex(), row, row);
    contactList.removeAt(row);
    endRemoveRows();
}
