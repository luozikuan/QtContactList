#include <QDebug>
#include <QGraphicsDropShadowEffect>
#include "widget.h"
#include "ui_widget.h"
#include "contactdata.h"
#include "contactdelegate.h"
#include "contactmodel.h"
#include "recentcontactmodel.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    contactModel(new ContactModel(this)),
    recentContactModel(new RecentContactModel(this))
{
    ui->setupUi(this);

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect;
    shadow->setOffset(1, 1);
    shadow->setColor(QColor(0, 0, 0, 127));
    shadow->setBlurRadius(5);
    ui->listView_all->setGraphicsEffect(shadow);

    ui->listView_all->setItemDelegate(new ContactDelegate(ui->listView_all));
    ui->listView_all->setModel(contactModel);

    //ui->listView_recent->setItemDelegate(new ContactDelegate(ui->listView_recent));
    ui->listView_recent->setModel(recentContactModel);
}

Widget::~Widget()
{
    delete ui;
}
