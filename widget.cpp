#include <QDebug>
#include <QGraphicsDropShadowEffect>
#include <QFontDialog>
#include <QFont>
#include <QStackedLayout>
#include "widget.h"
#include "ui_widget.h"
#include "datacenter.h"
#include "contactdelegate.h"
#include "contactmodel.h"
#include "recentcontactmodel.h"
#include "recentcontactdelegate.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    contactModel(Q_NULLPTR),
    recentContactModel(Q_NULLPTR),
    completer(Q_NULLPTR),
    contactSearchModel(Q_NULLPTR),
    searchTimer(new QTimer(this))
{
    ui->setupUi(this);
    adjustLayout();

    // set all contact
    contactModel = new ContactModel(this);
    QSortFilterProxyModel *allContactProxyModel = new QSortFilterProxyModel(this);
    allContactProxyModel->setSortRole(ContactModel::NicknameRole);
    allContactProxyModel->sort(0);
    allContactProxyModel->setSourceModel(contactModel);
    ui->listView_all->setItemDelegate(new ContactDelegate(this));
    ui->listView_all->setModel(allContactProxyModel);

    // set recent contact
    recentContactModel = new RecentContactModel(this);
    QSortFilterProxyModel *recentChatProxyModel = new QSortFilterProxyModel(this);
    recentChatProxyModel->setSortRole(RecentContactModel::LastMsgTimeRole);
    recentChatProxyModel->sort(0);
    recentChatProxyModel->setSourceModel(recentContactModel);
    ui->listView_recent->setItemDelegate(new RecentContactDelegate(this));
    ui->listView_recent->setModel(recentChatProxyModel);

    // set completer
    completer = new QCompleter(contactModel, this);
    completer->setCompletionRole(ContactModel::NicknameRole);
    completer->popup()->setItemDelegate(new ContactDelegate(this));
    connect(completer, SIGNAL(activated(QModelIndex)), this, SLOT(showSearchedInfo(QModelIndex)), Qt::QueuedConnection);

    ui->lineEdit->setCompleter(completer);
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

    contactModel->onRemoveFriend(6);
    //contactModel->onAddFriend(20);
}

void Widget::showSearchedInfo(const QModelIndex &index)
{
    qDebug() << index.data(ContactModel::NicknameRole);
    ui->lineEdit->clear(); // FIXME:
}

void Widget::adjustLayout()
{
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(ui->listView_recent, 0, 0, 2, 1);
    layout->addWidget(ui->lineEdit, 0, 1, 1, 1);

    QStackedLayout *stackedLayout = new QStackedLayout;
    //stackedLayout->setStackingMode(QStackedLayout::StackAll);
    stackedLayout->addWidget(ui->listView_searchAll);
    stackedLayout->addWidget(ui->listView_all);
    stackedLayout->setCurrentIndex(1);

    layout->addLayout(stackedLayout, 1, 1, 1, 1);

    QHBoxLayout *hboxLayout = new QHBoxLayout;
    hboxLayout->addWidget(ui->pushButton);
    hboxLayout->addWidget(ui->pushButton_2);
    hboxLayout->addStretch();
    layout->addLayout(hboxLayout, 2, 0, 1, 1);
    this->setLayout(layout);
}
