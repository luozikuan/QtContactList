#include <QDebug>
#include "searchcontactresultform.h"
#include "ui_searchcontactresultform.h"
#include "networksearchresultmodel.h"
#include "contactfilterproxymodel.h"

SearchContactResultForm::SearchContactResultForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchContactResultForm),
    networkResultModel(new NetworkSearchResultModel(this)),
    searchTimer(new QTimer(this))
{
    ui->setupUi(this);

    searchTimer->setInterval(300);
    searchTimer->setSingleShot(true);
    connect(searchTimer, &QTimer::timeout, this, &SearchContactResultForm::doSearch);

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
    qDebug() << "searching" << searchKey;
    // 1. if contactModel has result, show local result


    // 2. if contactModel has no result but has this person's data(in group
    //    member, etc), show result in network result page.
    // 3. if contactModel && chatEngine both have no info about this person,
    //    request from server and show it in network result page.
}
