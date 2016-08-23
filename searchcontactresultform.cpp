#include <QDebug>
#include "searchcontactresultform.h"
#include "ui_searchcontactresultform.h"
#include "networksearchresultmodel.h"
#include "contactfilterproxymodel.h"
#include "contactdelegate.h"

SearchContactResultForm::SearchContactResultForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchContactResultForm),
    contactSearchModel(new ContactFilterProxyModel(this)),
    networkResultModel(new NetworkSearchResultModel(this)),
    searchTimer(new QTimer(this))
{
    ui->setupUi(this);

    searchTimer->setInterval(300);
    searchTimer->setSingleShot(true);
    connect(searchTimer, &QTimer::timeout, this, &SearchContactResultForm::doSearch);

    ui->listView_local->setModel(contactSearchModel);
    ui->listView_local->setItemDelegate(new ContactDelegate(this));
    ui->listView_network->setModel(networkResultModel);
}

SearchContactResultForm::~SearchContactResultForm()
{
    delete ui;
}

void SearchContactResultForm::setSearchString(const QString &filter)
{
    searchKey = filter;
    searchTimer->start();
}

void SearchContactResultForm::setLocalSourceModel(QAbstractItemModel *model)
{
    contactSearchModel->setSourceModel(model);
}

void SearchContactResultForm::doSearch()
{
    this->show();
    qDebug() << "searching" << searchKey;
    // 1. if contactModel has result, show local result
    contactSearchModel->setFilterFixedString(searchKey);
    qDebug() << "searched:" << contactSearchModel->rowCount();

    // 2. if contactModel has no result but has this person's data(in group
    //    member, etc), show result in network result page.
    if (contactSearchModel->rowCount() == 0) {
        if (QRegExp("^(1\\d{10}|236\\d{8})$").exactMatch(searchKey)) {
            // 3. if contactModel && chatEngine both have no info about this person,
            //    request from server and show it in network result page.
            ui->stackedWidget->setCurrentIndex(NetworkResultPage);
        } else {
            ui->stackedWidget->setCurrentIndex(NotFoundPage);
        }
    } else if (contactSearchModel->rowCount() > 0) {
        ui->stackedWidget->setCurrentIndex(LocalResultPage);
    }

}
