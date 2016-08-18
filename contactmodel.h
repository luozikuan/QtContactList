#ifndef CONTACTMODEL_H
#define CONTACTMODEL_H

#include <QAbstractListModel>
#include <QList>

class ContactModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum ContactModelRole {
        NicknameRole = Qt::DisplayRole,
        AvatarRole = Qt::DecorationRole,

        UserSignRole = Qt::UserRole,
    };

    explicit ContactModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

signals:
public slots:
    void onFriendInfoChanged(quint64 uid);
    void onGroupInfoChanged(quint64 gid);

    void onAddFriend(quint64 uid);
    void onRemoveFriend(quint64 uid);

private:
    QList<QPair<quint64,bool>> contactList;
};

#endif // CONTACTMODEL_H
