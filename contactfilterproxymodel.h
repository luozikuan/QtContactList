#ifndef CONTACTFILTERPROXYMODEL_H
#define CONTACTFILTERPROXYMODEL_H

#include <QObject>
#include <QSortFilterProxyModel>

class ContactFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit ContactFilterProxyModel(QObject *parent = 0);

signals:

public slots:

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const Q_DECL_OVERRIDE;
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const Q_DECL_OVERRIDE;
};

#endif // CONTACTFILTERPROXYMODEL_H
