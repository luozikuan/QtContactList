#include <QDebug>
#include <QMouseEvent>
#include <QVariant>
#include <QMenu>
#include <QFontMetricsF>
#include "contactdelegate.h"
#include "contactmodel.h"

static const QMarginsF itemMargins(0, 0, 0, 1);
static const QSizeF avatarSize(50, 50);
static const QSizeF itemSize(100, itemMargins.bottom() + itemMargins.top() + avatarSize.height());

ContactDelegate::ContactDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

void ContactDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->setRenderHint(QPainter::Antialiasing);

    paintBackground(painter, option, index);
    paintAvatar(painter, option, index);
    paintNickname(painter, option, index);
    paintUserSign(painter, option, index);
    //paintUnreadNum(painter, option, index);
}

void ContactDelegate::paintBackground(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);

    QColor bgColor(Qt::transparent);
    if (option.state & QStyle::State_Selected) {
        bgColor = QColor("#ddd");
    } else if (option.state & QStyle::State_MouseOver) {
        bgColor = QColor("#eee");
    }
    painter->setPen(QPen(QColor("#ddd"), 1.0));
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, false);
    painter->drawLine(option.rect.bottomLeft(), option.rect.bottomRight());
    painter->restore();
    painter->fillRect(option.rect.adjusted(itemMargins.left(), itemMargins.top(), -itemMargins.right(), -itemMargins.bottom()), bgColor);
}

void ContactDelegate::paintAvatar(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QRectF avatarRect = QRectF(option.rect.topLeft() + QPointF(itemMargins.left(), itemMargins.top()), avatarSize);
    QColor color = index.data(ContactModel::AvatarRole).value<QColor>();
    //painter->fillRect(avatarRect, color);
    QPainterPath path;
    path.addEllipse(avatarRect - QMarginsF(5, 5, 5, 5));
    painter->fillPath(path, color);
}

void ContactDelegate::paintNickname(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QRectF nicknameRect = option.rect.adjusted(avatarSize.width() + itemMargins.left() + 6,
                                               itemMargins.top(),
                                               -itemMargins.right(),
                                               -itemSize.height() + itemMargins.top() + avatarSize.height() / 2);
    QString nickname = index.data(ContactModel::NicknameRole).toString();
    painter->setPen(Qt::black);
    painter->drawText(nicknameRect, Qt::AlignLeft | Qt::AlignVCenter, nickname);
}

void ContactDelegate::paintUserSign(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QRectF signRect = option.rect.adjusted(avatarSize.width() + itemMargins.left() + 6,
                                           itemMargins.top() + avatarSize.height() / 2 + 1,
                                           -itemMargins.right(),
                                           -itemMargins.bottom());
    QString sign = index.data(ContactModel::UserSignRole).toString();
    painter->drawText(signRect, Qt::AlignLeft | Qt::AlignVCenter, sign);
}

//void ContactDelegate::paintUnreadNum(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
//{
//    QRectF avatarRect = QRectF(option.rect.topLeft() + QPointF(itemMargins.left(), itemMargins.top()), avatarSize);

//    int unread = index.data(UnreadCountRole).toInt();
//    if (unread != 0) {
//        QString num;
//        if (unread > 99)
//            num = QString("99+");
//        else
//            num = QString::number(unread);
//        QFontMetricsF metricF(painter->font());
//        QSizeF unreadTextSize = metricF.size(Qt::TextSingleLine, num);
//        unreadTextSize.setWidth(unreadTextSize.width() + 6);
//        qreal minHeight = 16.0;
//        if (unreadTextSize.height() < minHeight) unreadTextSize.setHeight(minHeight);
//        if (unreadTextSize.width() < unreadTextSize.height()) unreadTextSize.setWidth(unreadTextSize.height());

//        QRectF unreadRect = avatarRect.adjusted(avatarRect.width() - unreadTextSize.width(), 0, 0, unreadTextSize.height() - avatarRect.height());
//        QPainterPath shadowPath;
//        shadowPath.addRoundedRect(unreadRect.adjusted(1,1,1,1), unreadTextSize.height()/2, unreadTextSize.height()/2);
//        painter->fillPath(shadowPath, QColor(0,0,0,200));
//        QPainterPath path;
//        path.addRoundedRect(unreadRect, unreadTextSize.height()/2, unreadTextSize.height()/2);
//        painter->fillPath(path, QColor("#f64"));

//        painter->setPen(Qt::white);
//        painter->drawText(unreadRect, Qt::AlignCenter, num);
//        painter->setPen(Qt::black);
//    }
//}

QSize ContactDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)
    return itemSize.toSize();
}

//bool ContactDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
//{
//    if (event->type() == QEvent::MouseButtonPress) {
//        QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent*>(event);
//        if (mouseEvent) {
//            if (mouseEvent->buttons() & Qt::LeftButton) {
//                QRect avatarRect = QRect(option.rect.topLeft() + QPoint(itemMargins.left(), itemMargins.top()), avatarSize.toSize());
//                if (avatarRect.contains(mouseEvent->pos())) {
//                    qDebug() << "left clicked on avatar of item" << index.data();
//                    model->setData(index, index.data().toString() + tr("changed"), Qt::DisplayRole);
//                } else {
//                    qDebug() << "left clicked on item" << index.data();
//                    model->setData(index, index.data(UserSignRole).toString() + tr("changed"), UserSignRole);
//                }
//            } else if (mouseEvent->buttons() & Qt::RightButton) {
//                qDebug() << "right clicked on item" << index.data();
//                QMenu menu;
//                menu.addAction(tr("delete this contact"));
//                menu.addAction(tr("delete all contact"));
//                menu.exec(QCursor::pos());
//            }
//        }
//    }
//    event->ignore();
//    return false;
//}
