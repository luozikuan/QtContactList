#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSortFilterProxyModel>
#include <QTimer>
#include <QCompleter>

QT_FORWARD_DECLARE_CLASS(ContactModel)
QT_FORWARD_DECLARE_CLASS(RecentContactModel)

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

private:
    void adjustLayout();

    Ui::Widget *ui;

    ContactModel *contactModel;
    RecentContactModel *recentContactModel;
    QCompleter *completer;

    QSortFilterProxyModel *contactSearchModel;
    QTimer *searchTimer;
};

#endif // WIDGET_H
