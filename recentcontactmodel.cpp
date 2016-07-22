#include "recentcontactmodel.h"

RecentContactModel::RecentContactModel(QObject *parent)
    : QAbstractListModel(parent)
{
    //recentContactList;

//    QList<ContactList*> allContact = ContactData::instance()->getAllContact();
//    foreach (ContactList *contact, allContact) {

//    }

    beginResetModel();
    count = 0;
    endResetModel();
}

int RecentContactModel::rowCount(const QModelIndex &parent) const
{
    return 10;
}

QVariant RecentContactModel::data(const QModelIndex &index, int role) const
{
    switch (role) {
    case Qt::DisplayRole:
        return QString("name");
    }

    return QVariant("default");
}

bool RecentContactModel::canFetchMore(const QModelIndex &parent) const
{
//    if (count < ContactData::instance()->getAllContact().size()) {
//        return true;
//    }
    return false;
}

void RecentContactModel::fetchMore(const QModelIndex &parent)
{

}
