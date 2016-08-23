#ifndef SEARCHCONTACTRESULTFORM_H
#define SEARCHCONTACTRESULTFORM_H

#include <QWidget>
#include <QAbstractItemModel>
#include <QTimer>

QT_FORWARD_DECLARE_CLASS(ContactFilterProxyModel)
QT_FORWARD_DECLARE_CLASS(NetworkSearchResultModel)

namespace Ui {
class SearchContactResultForm;
}

class SearchContactResultForm : public QWidget
{
    Q_OBJECT
    enum {
        LocalResultPage = 0,
        LabelHintPage,
        NetworkResultPage,
    };
public:
    explicit SearchContactResultForm(QWidget *parent = 0);
    ~SearchContactResultForm();

    void setSearchString(const QString &filter);
    void setLocalSourceModel(QAbstractItemModel *model);

private:
    void doSearch();
    void adjustHeight();

    Ui::SearchContactResultForm *ui;
    ContactFilterProxyModel *contactSearchModel;
    NetworkSearchResultModel *networkResultModel;
    QTimer *searchTimer;

    QString searchKey;

    const int maxVisibleItems = 7;
};

#endif // SEARCHCONTACTRESULTFORM_H
