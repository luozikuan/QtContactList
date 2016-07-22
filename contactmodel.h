#ifndef CONTACTMODEL_H
#define CONTACTMODEL_H

#include <QAbstractListModel>
#include <QList>

enum ContactRole {
    NicknameRole = Qt::DisplayRole,
    AvatarRole = Qt::DecorationRole,

    IdRole = Qt::UserRole,
    IsGroupRole,
    UserSignRole,
    UnreadCountRole,
    LastMsgTimeRole,
    LastMsgContentRole,
};

class ContactModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit ContactModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) Q_DECL_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;

signals:

protected:
    bool canFetchMore(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    void fetchMore(const QModelIndex &parent) Q_DECL_OVERRIDE;
public slots:

private:
    int count;
};

#endif // CONTACTMODEL_H
