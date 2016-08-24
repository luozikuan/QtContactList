#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSortFilterProxyModel>
#include <QCompleter>

QT_FORWARD_DECLARE_CLASS(ContactModel)
QT_FORWARD_DECLARE_CLASS(RecentContactModel)
QT_FORWARD_DECLARE_CLASS(ContactFilterProxyModel)
QT_FORWARD_DECLARE_CLASS(SearchContactResultForm)
QT_FORWARD_DECLARE_CLASS(CourseModel)

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

signals:
    void chatWith(quint64 id, bool isGroup);

private slots:
    void on_pushButton_clicked();
    void showSearchedInfo(const QModelIndex &index);
    void searchContact(QString key);

private:
    void initRecentChatModel();
    void initContactModel();

    Ui::Widget *ui;

    ContactModel *contactModel;
    RecentContactModel *recentContactModel;
    ContactFilterProxyModel *contactSearchModel;
    SearchContactResultForm *searchResult;
    CourseModel *courseModel;
};

#endif // WIDGET_H
