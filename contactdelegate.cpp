#include <QDebug>
#include <QMouseEvent>
#include <QVariant>
#include <QMenu>
#include <QLinearGradient>
#include <QRadialGradient>
#include <QFontMetricsF>
#include "contactdelegate.h"
#include "contactmodel.h"

static const QMarginsF itemMargins(3,2,3,4);
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
    //paintShadow(painter, option, index);
    paintAvatar(painter, option, index);
    paintNickname(painter, option, index);
    paintUserSign(painter, option, index);
    paintUnreadNum(painter, option, index);
}

void ContactDelegate::paintBackground(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);

    QColor bgColor(Qt::white);
    if (option.state & QStyle::State_Selected) {
        bgColor = Qt::blue;
    } else if (option.state & QStyle::State_MouseOver) {
        bgColor = Qt::gray;
    }
    // painter->setPen(QPen(Qt::black, 1.0));
    // painter->drawLine(option.rect.bottomLeft(), option.rect.bottomRight());
    painter->fillRect(option.rect.adjusted(itemMargins.left(), itemMargins.top(), -itemMargins.right(), -itemMargins.bottom()), bgColor);
}

void ContactDelegate::paintShadow(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)
    QRectF itemRect = QRectF(option.rect);
    QRectF contentRect = itemRect - itemMargins;
    // shadow
    QRectF bottomShadowRect(contentRect.bottomLeft(), QSizeF(contentRect.width(), itemMargins.bottom()));
    QLinearGradient bottomLinear(bottomShadowRect.topLeft(), bottomShadowRect.bottomLeft());
    bottomLinear.setColorAt(0.0, QColor(128,128,128,200));
    bottomLinear.setColorAt(1.0, Qt::transparent);
    painter->fillRect(bottomShadowRect, QBrush(bottomLinear));

    QRectF rightShadowRect(contentRect.topRight(), QSizeF(itemMargins.right(), contentRect.height()));
    QLinearGradient rightLinear(rightShadowRect.topLeft(), rightShadowRect.topRight());
    rightLinear.setColorAt(0.0, QColor(128,128,128,200));
    rightLinear.setColorAt(1.0, Qt::transparent);
    painter->fillRect(rightShadowRect, QBrush(rightLinear));

    QRectF leftShadowRect(QPointF(0, itemRect.top() + itemMargins.top()), QSizeF(itemMargins.left(), contentRect.height()));
    QLinearGradient leftLinear(leftShadowRect.topLeft(), leftShadowRect.topRight());
    leftLinear.setColorAt(0.0, Qt::transparent);
    leftLinear.setColorAt(1.0, QColor(128,128,128,200));
    painter->fillRect(leftShadowRect, QBrush(leftLinear));

    QRectF topShadowRect(QPointF(itemMargins.left(), itemRect.top()), QSizeF(contentRect.width(), itemMargins.top()));
    QLinearGradient topLinear(topShadowRect.topLeft(), topShadowRect.bottomLeft());
    topLinear.setColorAt(0.0, Qt::transparent);
    topLinear.setColorAt(1.0, QColor(128,128,128,200));
    painter->fillRect(topShadowRect, QBrush(topLinear));

    QRectF bottomRightRect(contentRect.bottomRight(), itemRect.bottomRight());
    QRadialGradient bottomRightRadial(contentRect.bottomRight(), 4, itemRect.bottomRight());
    bottomRightRadial.setColorAt(0.0, QColor(128,128,128,200));
    bottomRightRadial.setColorAt(1.0, Qt::transparent);
    painter->fillRect(bottomRightRect, QBrush(bottomRightRadial));
}

void ContactDelegate::paintAvatar(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QRectF avatarRect = QRectF(option.rect.topLeft() + QPointF(itemMargins.left(), itemMargins.top()), avatarSize);
    QColor color = index.data(AvatarRole).value<QColor>();
    painter->fillRect(avatarRect, color);
}

void ContactDelegate::paintNickname(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QRectF nicknameRect = option.rect.adjusted(avatarSize.width() + 2 * itemMargins.left(),
                                               itemMargins.top(),
                                               -itemMargins.right(),
                                               -itemSize.height() + itemMargins.top() + avatarSize.height() / 2);
    QString nickname = index.data(NicknameRole).toString();
    painter->setPen(Qt::black);
    painter->drawText(nicknameRect, Qt::AlignLeft | Qt::AlignVCenter, nickname);
}

void ContactDelegate::paintUserSign(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QRectF signRect = option.rect.adjusted(avatarSize.width() + 2 * itemMargins.left(),
                                           itemMargins.top() + avatarSize.height() / 2 + 1,
                                           -itemMargins.right(),
                                           -itemMargins.bottom());
    QString sign = index.data(UserSignRole).toString();
    painter->drawText(signRect, Qt::AlignLeft | Qt::AlignVCenter, sign);
}

void ContactDelegate::paintUnreadNum(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QRectF avatarRect = QRectF(option.rect.topLeft() + QPointF(itemMargins.left(), itemMargins.top()), avatarSize);

    int unread = index.data(UnreadCountRole).toInt();
    if (unread != 0) {
        QString num;
        if (unread > 99)
            num = QString("99+");
        else
            num = QString::number(unread);
        QFontMetricsF metricF(painter->font());
        QSizeF unreadTextSize = metricF.size(Qt::TextSingleLine, num);
        qreal minHeight = 18.0;
        if (unreadTextSize.height() < minHeight) unreadTextSize.setHeight(minHeight);
        if (unreadTextSize.width() < minHeight) unreadTextSize.setWidth(minHeight);
        if (unreadTextSize.width() > unreadTextSize.height()) unreadTextSize.setWidth(unreadTextSize.width() + 6);

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

QSize ContactDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return itemSize.toSize();
}

bool ContactDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent*>(event);
        if (mouseEvent) {
            if (mouseEvent->buttons() & Qt::LeftButton) {
                QRect avatarRect = QRect(option.rect.topLeft() + QPoint(3, 3), QSize(50, 50));
                if (avatarRect.contains(mouseEvent->pos())) {
                    qDebug() << "left clicked on avatar of item" << index.data();
                    model->setData(index, index.data().toString() + tr("changed"), Qt::DisplayRole);
                } else {
                    qDebug() << "left clicked on item" << index.data();
                    model->setData(index, 0, Qt::UserRole + 3);
                }
            } else if (mouseEvent->buttons() & Qt::RightButton) {
                qDebug() << "right clicked on item" << index.data();
                QMenu menu;
                menu.addAction(tr("delete this contact"));
                menu.addAction(tr("delete all contact"));
                menu.exec(QCursor::pos());
            }
        }
    }
    event->ignore();
    return false;
}
