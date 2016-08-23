#include <QDebug>
#include <QGraphicsDropShadowEffect>
#include <QFontDialog>
#include <QFont>
#include <QGraphicsDropShadowEffect>

#include "widget.h"
#include "ui_widget.h"
#include "datacenter.h"
#include "contactdelegate.h"
#include "contactmodel.h"
#include "recentcontactmodel.h"
#include "recentcontactdelegate.h"
#include "contactfilterproxymodel.h"
#include "searchcontactresultform.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    contactModel(new ContactModel(this)),
    recentContactModel(new RecentContactModel(this)),
    contactSearchModel(new ContactFilterProxyModel(this)),
    searchResult(new SearchContactResultForm(this))
{
    ui->setupUi(this);
    //searchResult->setWindowFlags(Qt::Popup);
    searchResult->hide();
    searchResult->setLocalSourceModel(contactModel);
    searchResult->raise();

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0, 2);
    shadow->setBlurRadius(16);
    searchResult->setGraphicsEffect(shadow);

    initRecentChatModel();
    initContactModel();

    connect(ui->lineEdit, &QLineEdit::textChanged, this, &Widget::searchContact);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
//    PersonInfo *person = DataCenter::instance()->getPersonInfo(0);
//    person->avatarColor = Qt::GlobalColor(4+qrand()%17); // 2~18   2+(0~16)
//    person->nickname = QStringLiteral("testCourse2");
//    contactModel->onFriendInfoChanged(person->uid);

    //contactModel->onRemoveFriend(6);
    //contactModel->onAddFriend(20);
    searchResult->hide();
}

void Widget::showSearchedInfo(const QModelIndex &index)
{
    qDebug() << index.data(ContactModel::NicknameRole);
    ui->lineEdit->clear(); // FIXME:
}

void Widget::initRecentChatModel()
{
    // set recent contact
    QSortFilterProxyModel *recentChatProxyModel = new QSortFilterProxyModel(this);
    recentChatProxyModel->setSortRole(RecentContactModel::LastMsgTimeRole);
    recentChatProxyModel->sort(0);
    recentChatProxyModel->setSourceModel(recentContactModel);
    ui->listView_recent->setItemDelegate(new RecentContactDelegate(this));
    ui->listView_recent->setModel(recentChatProxyModel);
}

void Widget::initContactModel()
{
    // set all contact
    QSortFilterProxyModel *allContactProxyModel = new QSortFilterProxyModel(this);
    allContactProxyModel->setSortRole(ContactModel::NicknameRole);
    allContactProxyModel->sort(0);
    allContactProxyModel->setSourceModel(contactModel);
    ui->listView_all->setItemDelegate(new ContactDelegate(this));
    ui->listView_all->setModel(allContactProxyModel);
}

void Widget::searchContact(QString key)
{
    searchResult->setSearchString(key);
    searchResult->resize(ui->lineEdit->width(), 200);
    QPoint globalTopLeft = ui->lineEdit->geometry().bottomLeft();
    searchResult->move(globalTopLeft + QPoint(0, 5));
    //searchResult->show();
}
