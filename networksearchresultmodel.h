#ifndef NETWORKSEARCHRESULTMODEL_H
#define NETWORKSEARCHRESULTMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QList>

class NetworkSearchResultModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit NetworkSearchResultModel(QObject *parent = 0);

    void setResultList(const QList<quint64> &person);
    void clearResultList();

    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

signals:

public slots:

private:
    QList<quint64> m_person;
};

#endif // NETWORKSEARCHRESULTMODEL_H
