#include <QDebug>
#include <QGraphicsDropShadowEffect>
#include <QFontDialog>
#include <QFont>
#include "widget.h"
#include "ui_widget.h"
#include "datacenter.h"
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

    // set all contact
    QSortFilterProxyModel *allContactProxyModel = new QSortFilterProxyModel(this);
    allContactProxyModel->setSortRole(ContactModel::NicknameRole);
    allContactProxyModel->sort(0);
    allContactProxyModel->setSourceModel(contactModel);
    ui->listView_all->setItemDelegate(new ContactDelegate(this));
    ui->listView_all->setModel(allContactProxyModel);

//    // set recent contact
//    //recentContactModel->setFilterRole(LastMsgTimeRole);
//    recentContactModel->setSortRole(LastMsgTimeRole);
//    recentContactModel->sort(0);
//    recentContactModel->setSourceModel(contactModel);

//    ui->listView_recent->setItemDelegate(new RecentContactDelegate(this));
//    ui->listView_recent->setModel(recentContactModel);

    // set search contact
    contactSearchModel->setSourceModel(contactModel);
    contactSearchModel->setFilterRole(ContactModel::NicknameRole);
    contactSearchModel->setFilterKeyColumn(0);

    searchTimer->setInterval(300);
    searchTimer->setSingleShot(true);
    connect(searchTimer, &QTimer::timeout, [=](){
        contactSearchModel->setFilterFixedString(ui->lineEdit->text());
        on_pushButton_2_clicked();
    });
    connect(ui->lineEdit, &QLineEdit::textChanged, [=](){searchTimer->start();});
    connect(ui->listView_searchAll, &QListView::clicked, [=](const QModelIndex &index){
        qDebug() << index.row();
    });

    ui->listView_searchAll->setItemDelegate(new ContactDelegate(this));
    ui->listView_searchAll->setModel(contactSearchModel);

    on_pushButton_2_clicked();

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect;
    shadow->setOffset(0, 3);
    shadow->setColor(QColor(0, 0, 0, 127));
    shadow->setBlurRadius(8);
    ui->listView_searchAll->setGraphicsEffect(shadow);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_2_clicked()
{
//    bool ok = false;
//    QFont font = QFontDialog::getFont(&ok);
//    if (ok) {
//        qDebug() << font;
//        qApp->setFont(font);
//    }
    int rowCount = ui->listView_searchAll->model()->rowCount();
    int rowHeight = ui->listView_searchAll->sizeHintForRow(0);

    qDebug() << rowCount << rowHeight;
    int totalHeight = rowCount * rowHeight;
    if (totalHeight > maximumHeight()) {
        totalHeight = maximumHeight();
    }
    ui->listView_searchAll->resize(ui->listView_searchAll->width(), totalHeight);
}

void Widget::on_pushButton_clicked()
{
    PersonInfo *person = DataCenter::instance()->getPersonInfo(0);
    person->avatarColor = Qt::GlobalColor(4+qrand()%17); // 2~18   2+(0~16)
    person->nickname = QStringLiteral("testCourse2");
    contactModel->onFriendInfoChanged(person->uid);
}
