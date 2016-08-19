#include <QDebug>
#include <QMouseEvent>
#include <QVariant>
#include <QMenu>
#include <QDateTime>
#include "recentcontactdelegate.h"
#include "datacenter.h"
#include "recentcontactmodel.h"

static const QMarginsF itemMargins(0, 0, 0, 1);
static const QSizeF avatarSize(50, 50);
static const QSizeF itemSize(100, itemMargins.bottom() + itemMargins.top() + avatarSize.height());

RecentContactDelegate::RecentContactDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

void RecentContactDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->setRenderHint(QPainter::Antialiasing);

    paintBackground(painter, option, index);
    paintAvatar(painter, option, index);
    paintNicknameAndMsgTime(painter, option, index);
    paintMsgContent(painter, option, index);
    paintUnreadNum(painter, option, index);
}

void RecentContactDelegate::paintBackground(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
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

void RecentContactDelegate::paintAvatar(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QRectF avatarRect = QRectF(option.rect.topLeft() + QPointF(itemMargins.left(), itemMargins.top()), avatarSize);
    QColor color = index.data(RecentContactModel::AvatarRole).value<QColor>();
    //painter->fillRect(avatarRect, color);
    QPainterPath path;
    path.addEllipse(avatarRect - QMarginsF(5, 5, 5, 5));
    painter->fillPath(path, color);
}

void RecentContactDelegate::paintNicknameAndMsgTime(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    time_t time = index.data(RecentContactModel::LastMsgTimeRole).toULongLong();
    QFontMetricsF metricF(painter->font());
    QString timeStr = QDateTime::fromTime_t(time).toString("MM-dd H:mm");//QString::number(time);//
    QSizeF timeTextSize = metricF.size(Qt::TextSingleLine, timeStr);

    QRectF timeRect = option.rect.adjusted(option.rect.width() - itemMargins.right() - timeTextSize.width() - 5,
                                           itemMargins.top(),
                                           -itemMargins.right(),
                                           -itemSize.height() + itemMargins.top() + avatarSize.height() / 2);
    painter->setPen(QColor("#aaa"));
    painter->drawText(timeRect, Qt::AlignLeft | Qt::AlignVCenter, timeStr);
//--------

    QRectF nicknameRect = option.rect.adjusted(avatarSize.width() + itemMargins.left() + 6,
                                               itemMargins.top(),
                                               -itemMargins.right() - timeTextSize.width() - 5,
                                               -itemSize.height() + itemMargins.top() + avatarSize.height() / 2);
    QString nickname = index.data(RecentContactModel::NicknameRole).toString();
    nickname = metricF.elidedText(nickname, Qt::ElideRight, nicknameRect.width());
    painter->setPen(QColor("#333333"));
    painter->drawText(nicknameRect, Qt::AlignLeft | Qt::AlignVCenter, nickname);
}

void RecentContactDelegate::paintMsgContent(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QRectF signRect = option.rect.adjusted(avatarSize.width() + itemMargins.left() + 6,
                                           itemMargins.top() + avatarSize.height() / 2 + 1,
                                           -itemMargins.right(),
                                           -itemMargins.bottom());
    QString sign = index.data(RecentContactModel::LastMsgContentRole).toString();
    QFontMetricsF metricF(painter->font());
    sign = metricF.elidedText(sign, Qt::ElideRight, signRect.width());
    painter->setPen(QColor("#999"));
    painter->drawText(signRect, Qt::AlignLeft | Qt::AlignVCenter, sign);
}

void RecentContactDelegate::paintUnreadNum(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QRectF avatarRect = QRectF(option.rect.topLeft() + QPointF(itemMargins.left(), itemMargins.top()), avatarSize);

    int unread = index.data(RecentContactModel::UnreadCountRole).toInt();
    if (unread != 0) {
        QString num;
        if (unread > 99)
            num = QString("99+");
        else
            num = QString::number(unread);
        QFontMetricsF metricF(painter->font());
        QSizeF unreadTextSize = metricF.size(Qt::TextSingleLine, num);
        unreadTextSize.setWidth(unreadTextSize.width() + 6);
        qreal minHeight = 16.0;
        if (unreadTextSize.height() < minHeight) unreadTextSize.setHeight(minHeight);
        if (unreadTextSize.width() < unreadTextSize.height()) unreadTextSize.setWidth(unreadTextSize.height());

        QRectF unreadRect = avatarRect.adjusted(avatarRect.width() - unreadTextSize.width(), 0, 0, unreadTextSize.height() - avatarRect.height());
        QPainterPath shadowPath;
        shadowPath.addRoundedRect(unreadRect.adjusted(1,1,1,1), unreadTextSize.height()/2, unreadTextSize.height()/2);
        painter->fillPath(shadowPath, QColor(0,0,0,200));
        QPainterPath path;
        path.addRoundedRect(unreadRect, unreadTextSize.height()/2, unreadTextSize.height()/2);
        painter->fillPath(path, QColor("#f64"));

        painter->setPen(Qt::white);
        painter->drawText(unreadRect, Qt::AlignCenter, num);
        painter->setPen(Qt::black);
    }
}

QSize RecentContactDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)
    return itemSize.toSize();
}

bool RecentContactDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent*>(event);
        if (mouseEvent) {
            if (mouseEvent->buttons() & Qt::LeftButton) {
                if (option.rect.contains(mouseEvent->pos())) {
                    model->setData(index, 0, RecentContactModel::UnreadCountRole);
                }
            } else if (mouseEvent->buttons() & Qt::RightButton) {
                qDebug() << "right clicked on item" << index.data();
                QMenu menu;
                menu.addAction(tr("delete this chat"));
                menu.addAction(tr("delete all chat"));
                menu.exec(QCursor::pos());
            }
        }
    }
    event->ignore();
    return false;
}
