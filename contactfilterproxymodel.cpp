#include <QDebug>
#include "contactfilterproxymodel.h"
#include "contactmodel.h"

ContactFilterProxyModel::ContactFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{

}

bool ContactFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);

    QString nickname = index.data(ContactModel::NicknameRole).toString();
    return nickname.contains(filterRegExp());
}

bool ContactFilterProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    QString leftData = sourceModel()->data(left, ContactModel::NicknameRole).toString();
    QString rightData = sourceModel()->data(right, ContactModel::NicknameRole).toString();

    int ret = QString::compare(leftData, rightData);
    return ret < 0;
}

