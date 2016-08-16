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
    //bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) Q_DECL_OVERRIDE;
    //Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;

signals:
public slots:

//protected:
//    bool canFetchMore(const QModelIndex &parent) const Q_DECL_OVERRIDE;
//    void fetchMore(const QModelIndex &parent) Q_DECL_OVERRIDE;

private:
    QList<QPair<quint64,bool>> contactList;
};

#endif // CONTACTMODEL_H
