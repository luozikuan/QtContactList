#include "networksearchresultmodel.h"
#include "datacenter.h"
#include "contactmodel.h"

NetworkSearchResultModel::NetworkSearchResultModel(QObject *parent)
    : QAbstractListModel(parent)
{
    clearResultList();
}

void NetworkSearchResultModel::setResultList(const QList<quint64> &person)
{
    beginResetModel();
    m_person = person;
    endResetModel();
}

void NetworkSearchResultModel::clearResultList()
{
    beginResetModel();
    m_person.clear();
    endResetModel();
}

int NetworkSearchResultModel::rowCount(const QModelIndex &parent) const
{
    return m_person.size();
}

QVariant NetworkSearchResultModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= m_person.size() || index.row() < 0)
        return QVariant();

    quint64 uid = m_person.at(index.row());
    PersonInfo *person = DataCenter::instance()->getPersonInfo(uid);
    switch (role) {
    case ContactModel::NicknameRole:
        return person->nickname;
    case ContactModel::AvatarRole:
    {
        QVariant tmp;
        tmp.setValue(person->avatarColor);
        return tmp;
    }
    case ContactModel::UserSignRole:
        return person->sign;
    default:
        return QVariant();
    }

    return QVariant();
}

