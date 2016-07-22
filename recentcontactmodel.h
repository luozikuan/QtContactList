#ifndef RECENTCONTACTMODEL_H
#define RECENTCONTACTMODEL_H

#include <QAbstractListModel>

QT_FORWARD_DECLARE_STRUCT(ContactInfo)

class RecentContactModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit RecentContactModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

signals:

protected:
    bool canFetchMore(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    void fetchMore(const QModelIndex &parent) Q_DECL_OVERRIDE;

public slots:

private:
    QList<ContactInfo*> recentContactList;
    int count;
};

#endif // RECENTCONTACTMODEL_H
