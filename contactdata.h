#ifndef CONTACTDATA_H
#define CONTACTDATA_H

#include <QObject>
#include <QHash>
#include <QColor>

struct ContactInfo
{
    quint64 id;
    bool isGroup;

    QString name;
    QColor avatarColor;
    QString userSign;

    int unreadCount;
    time_t lastMsgTime;
    QString lastMsgContent;
};

class ContactData : public QObject
{
    Q_OBJECT
public:
    static ContactData *instance();
    ~ContactData();
    const QHash<int, ContactInfo*>& getAllContact();

signals:

public slots:

private:
    explicit ContactData(QObject *parent = 0);

    QHash<int, ContactInfo*> contactList;
};

#endif // CONTACTDATA_H
