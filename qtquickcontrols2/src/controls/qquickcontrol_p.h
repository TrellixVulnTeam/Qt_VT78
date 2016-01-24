/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Quick Controls module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL3$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPLv3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or later as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file. Please review the following information to
** ensure the GNU General Public License version 2.0 requirements will be
** met: http://www.gnu.org/licenses/gpl-2.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QQUICKCONTROL_P_H
#define QQUICKCONTROL_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtQuick/qquickitem.h>
#include <QtQuickControls/private/qtquickcontrolsglobal_p.h>

QT_BEGIN_NAMESPACE

class QQuickControlPrivate;

class Q_QUICKCONTROLS_EXPORT QQuickControl : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QFont font READ font WRITE setFont RESET resetFont NOTIFY fontChanged)
    Q_PROPERTY(qreal availableWidth READ availableWidth NOTIFY availableWidthChanged FINAL)
    Q_PROPERTY(qreal availableHeight READ availableHeight NOTIFY availableHeightChanged FINAL)
    Q_PROPERTY(qreal padding READ padding WRITE setPadding RESET resetPadding NOTIFY paddingChanged FINAL)
    Q_PROPERTY(qreal topPadding READ topPadding WRITE setTopPadding RESET resetTopPadding NOTIFY topPaddingChanged FINAL)
    Q_PROPERTY(qreal leftPadding READ leftPadding WRITE setLeftPadding RESET resetLeftPadding NOTIFY leftPaddingChanged FINAL)
    Q_PROPERTY(qreal rightPadding READ rightPadding WRITE setRightPadding RESET resetRightPadding NOTIFY rightPaddingChanged FINAL)
    Q_PROPERTY(qreal bottomPadding READ bottomPadding WRITE setBottomPadding RESET resetBottomPadding NOTIFY bottomPaddingChanged FINAL)
    Q_PROPERTY(qreal spacing READ spacing WRITE setSpacing RESET resetSpacing NOTIFY spacingChanged FINAL)
    Q_PROPERTY(Qt::LayoutDirection layoutDirection READ layoutDirection WRITE setLayoutDirection NOTIFY layoutDirectionChanged FINAL)
    Q_PROPERTY(Qt::LayoutDirection effectiveLayoutDirection READ effectiveLayoutDirection NOTIFY effectiveLayoutDirectionChanged FINAL)
    Q_PROPERTY(bool mirrored READ isMirrored NOTIFY mirroredChanged FINAL)
    Q_PROPERTY(QQuickItem *background READ background WRITE setBackground NOTIFY backgroundChanged FINAL)
    Q_PROPERTY(QQuickItem *contentItem READ contentItem WRITE setContentItem NOTIFY contentItemChanged FINAL)

public:
    explicit QQuickControl(QQuickItem *parent = Q_NULLPTR);

    QFont font() const;
    void setFont(const QFont &);
    void resetFont();

    qreal availableWidth() const;
    qreal availableHeight() const;

    qreal padding() const;
    void setPadding(qreal padding);
    void resetPadding();

    qreal topPadding() const;
    void setTopPadding(qreal padding);
    void resetTopPadding();

    qreal leftPadding() const;
    void setLeftPadding(qreal padding);
    void resetLeftPadding();

    qreal rightPadding() const;
    void setRightPadding(qreal padding);
    void resetRightPadding();

    qreal bottomPadding() const;
    void setBottomPadding(qreal padding);
    void resetBottomPadding();

    qreal spacing() const;
    void setSpacing(qreal spacing);
    void resetSpacing();

    Qt::LayoutDirection layoutDirection() const;
    Qt::LayoutDirection effectiveLayoutDirection() const;
    void setLayoutDirection(Qt::LayoutDirection direction);

    bool isMirrored() const;

    QQuickItem *background() const;
    void setBackground(QQuickItem *background);

    QQuickItem *contentItem() const;
    void setContentItem(QQuickItem *item);

Q_SIGNALS:
    void fontChanged();
    void availableWidthChanged();
    void availableHeightChanged();
    void paddingChanged();
    void topPaddingChanged();
    void leftPaddingChanged();
    void rightPaddingChanged();
    void bottomPaddingChanged();
    void spacingChanged();
    void layoutDirectionChanged();
    void effectiveLayoutDirectionChanged();
    void mirroredChanged();
    void backgroundChanged();
    void contentItemChanged();

protected:
    QQuickControl(QQuickControlPrivate &dd, QQuickItem *parent);

    void itemChange(ItemChange change, const ItemChangeData &value) Q_DECL_OVERRIDE;

    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry) Q_DECL_OVERRIDE;

    virtual void mirrorChange();
    virtual void paddingChange(const QMarginsF &newPadding, const QMarginsF &oldPadding);
    virtual void contentItemChange(QQuickItem *newItem, QQuickItem *oldItem);

private:
    Q_DISABLE_COPY(QQuickControl)
    Q_DECLARE_PRIVATE(QQuickControl)
};

Q_DECLARE_TYPEINFO(QQuickControl, Q_COMPLEX_TYPE);

QT_END_NAMESPACE

#endif // QQUICKCONTROL_P_H
