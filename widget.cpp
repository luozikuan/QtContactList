#include <QDebug>
#include <QGraphicsDropShadowEffect>
#include <QFontDialog>
#include <QFont>
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
    recentContactModel(new QSortFilterProxyModel(this)),
    contactSearchModel(new QSortFilterProxyModel(this)),
    searchTimer(new QTimer(this))
{
    ui->setupUi(this);

    ui->listView_all->setItemDelegate(new ContactDelegate(this));
    ui->listView_all->setModel(contactModel);

    //recentContactModel->setFilterRole(LastMsgTimeRole);
    recentContactModel->setSortRole(LastMsgTimeRole);
    recentContactModel->sort(0);
    recentContactModel->setSourceModel(contactModel);

    ui->listView_recent->setItemDelegate(new RecentContactDelegate(this));
    ui->listView_recent->setModel(recentContactModel);

    contactSearchModel->setSourceModel(contactModel);
    contactSearchModel->setFilterRole(NicknameRole);
    contactSearchModel->setFilterKeyColumn(0);

    searchTimer->setInterval(300);
    searchTimer->setSingleShot(true);
    connect(searchTimer, &QTimer::timeout, [=](){
        contactSearchModel->setFilterFixedString(ui->lineEdit->text());
    });
    connect(ui->lineEdit, &QLineEdit::textChanged, [=](){searchTimer->start();});
    connect(ui->listView_searchAll, &QListView::clicked, [=](const QModelIndex &index){
        qDebug() << index.row();
    });

    ui->listView_searchAll->setItemDelegate(new ContactDelegate(this));
    ui->listView_searchAll->setModel(contactSearchModel);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_2_clicked()
{
    bool ok = false;
    QFont font = QFontDialog::getFont(&ok);
    if (ok) {
        qDebug() << font;
        qApp->setFont(font);
    }
}
