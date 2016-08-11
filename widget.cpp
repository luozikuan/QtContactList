#include <QDebug>
#include <QGraphicsDropShadowEffect>
#include "widget.h"
#include "ui_widget.h"
#include "contactdata.h"
#include "contactdelegate.h"
#include "contactmodel.h"
#include "recentcontactdelegate.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    contactModel(new ContactModel(this)),
    recentContactModel(new QSortFilterProxyModel(this))
{
    ui->setupUi(this);

//    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect;
//    shadow->setOffset(1, 1);
//    shadow->setColor(QColor(0, 0, 0, 127));
//    shadow->setBlurRadius(5);
//    ui->listView_all->setGraphicsEffect(shadow);

//    shadow = new QGraphicsDropShadowEffect;
//    shadow->setOffset(1, 1);
//    shadow->setColor(QColor(0, 0, 0, 127));
//    shadow->setBlurRadius(5);
//    ui->listView_recent->setGraphicsEffect(shadow);

    ui->listView_all->setItemDelegate(new ContactDelegate(ui->listView_all));
    ui->listView_all->setModel(contactModel);

    //recentContactModel->setFilterRole(LastMsgTimeRole);
    recentContactModel->setSortRole(LastMsgTimeRole);
    recentContactModel->sort(0);
    recentContactModel->setSourceModel(contactModel);

    ui->listView_recent->setItemDelegate(new RecentContactDelegate(ui->listView_recent));
    ui->listView_recent->setModel(recentContactModel);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    quint64 uid = 2;
    int row = ContactData::instance()->getFriendList().indexOf(uid);
    QModelIndex index = ui->listView_all->model()->index(row, 0, QModelIndex());
    ui->listView_all->model()->setData(index, 20, UnreadCountRole);
}
