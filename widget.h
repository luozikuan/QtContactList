#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSortFilterProxyModel>
#include <QTimer>

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

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::Widget *ui;

    ContactModel *contactModel;
    QSortFilterProxyModel *recentContactModel;
    QSortFilterProxyModel *contactSearchModel;
    QTimer *searchTimer;
};

#endif // WIDGET_H
