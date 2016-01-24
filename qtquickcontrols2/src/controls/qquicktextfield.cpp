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

#include "qquicktextfield_p.h"
#include "qquicktextfield_p_p.h"
#include "qquickcontrol_p.h"
#include "qquickcontrol_p_p.h"

#include <QtCore/qbasictimer.h>
#include <QtQuick/private/qquickitem_p.h>
#include <QtQuick/private/qquicktext_p.h>
#include <QtQuick/private/qquickclipnode_p.h>

QT_BEGIN_NAMESPACE

/*!
    \qmltype TextField
    \inherits TextInput
    \instantiates QQuickTextField
    \inqmlmodule QtQuick.Controls
    \ingroup editors
    \brief A single line text input control.

    TextField is a single line text editor. TextField extends TextInput
    with a \l placeholder text functionality, and adds decoration.

    \table
    \row \li \image qtquickcontrols2-textfield-normal.png
         \li A text field in its normal state.
    \row \li \image qtquickcontrols2-textfield-focused.png
         \li A text field that has active focus.
    \row \li \image qtquickcontrols2-textfield-disabled.png
         \li A text field that is disabled.
    \endtable

    \code
    TextField {
        placeholder.text: qsTr("Enter name")
    }
    \endcode

    \sa TextArea, {Customizing TextField}
*/

/*!
    \qmlsignal QtQuickControls2::TextField::pressAndHold(MouseEvent mouse)

    This signal is emitted when there is a long press (the delay depends on the platform plugin).
    The \l {MouseEvent}{mouse} parameter provides information about the press, including the x and y
    position of the press, and which button is pressed.
*/

void QQuickTextFieldPrivate::resizeBackground()
{
    Q_Q(QQuickTextField);
    if (background) {
        QQuickItemPrivate *p = QQuickItemPrivate::get(background);
        if (!p->widthValid && qFuzzyIsNull(background->x())) {
            background->setWidth(q->width());
            p->widthValid = false;
        }
        if (!p->heightValid && qFuzzyIsNull(background->y())) {
            background->setHeight(q->height());
            p->heightValid = false;
        }
    }
}

QQuickTextField::QQuickTextField(QQuickItem *parent) :
    QQuickTextInput(*(new QQuickTextFieldPrivate), parent)
{
    d_func()->pressAndHoldHelper.control = this;
    setActiveFocusOnTab(true);
}

QQuickTextField::~QQuickTextField()
{
}

/*!
    \internal

    Determine which font is implicitly imposed on this control by its ancestors
    and QGuiApplication::font, resolve this against its own font (attributes from
    the implicit font are copied over). Then propagate this font to this
    control's children.
*/
void QQuickTextFieldPrivate::resolveFont()
{
    Q_Q(QQuickTextField);
    QFont naturalFont = QQuickControlPrivate::naturalControlFont(q);
    QFont resolvedFont = sourceFont.resolve(naturalFont);
    setFont_helper(resolvedFont);
}

QFont QQuickTextField::font() const
{
    Q_D(const QQuickTextField);
    return d->sourceFont;
}

void QQuickTextField::setFont(const QFont &font)
{
    Q_D(QQuickTextField);
    if (d->sourceFont == font)
        return;

    // Determine which font is inherited from this control's ancestors and
    // QGuiApplication::font, resolve this against \a font (attributes from the
    // inherited font are copied over). Then propagate this font to this
    // control's children.
    QFont naturalFont = QQuickControlPrivate::naturalControlFont(this);
    QFont resolvedFont = font.resolve(naturalFont);
    d->setFont_helper(resolvedFont);

    QQuickTextInput::setFont(font);

    emit fontChanged();
}

/*!
    \qmlproperty Item QtQuickControls2::TextField::background

    This property holds the background item.

    \note If the background item has no explicit size specified, it automatically
          follows the control's size. In most cases, there is no need to specify
          width or height for a background item.

    \sa {Customizing TextField}
*/
QQuickItem *QQuickTextField::background() const
{
    Q_D(const QQuickTextField);
    return d->background;
}

void QQuickTextField::setBackground(QQuickItem *background)
{
    Q_D(QQuickTextField);
    if (d->background != background) {
        delete d->background;
        d->background = background;
        if (background) {
            background->setParentItem(this);
            if (qFuzzyIsNull(background->z()))
                background->setZ(-1);
            if (isComponentComplete())
                d->resizeBackground();
        }
        emit backgroundChanged();
    }
}

/*!
    \qmlproperty Text QtQuickControls2::TextField::placeholder

    This property holds the placeholder text item.

    \sa {Customizing TextField}
*/
QQuickText *QQuickTextField::placeholder() const
{
    Q_D(const QQuickTextField);
    return d->placeholder;
}

void QQuickTextField::setPlaceholder(QQuickText *placeholder)
{
    Q_D(QQuickTextField);
    if (d->placeholder != placeholder) {
        delete d->placeholder;
        d->placeholder = placeholder;
        if (placeholder && !placeholder->parentItem())
            placeholder->setParentItem(this);
        emit placeholderChanged();
    }
}

void QQuickTextField::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    Q_D(QQuickTextField);
    QQuickTextInput::geometryChanged(newGeometry, oldGeometry);
    d->resizeBackground();
}

QSGNode *QQuickTextField::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *data)
{
    QQuickDefaultClipNode *clipNode = static_cast<QQuickDefaultClipNode *>(oldNode);
    if (!clipNode)
        clipNode = new QQuickDefaultClipNode(QRectF());

    clipNode->setRect(clipRect().adjusted(leftPadding(), topPadding(), -rightPadding(), -bottomPadding()));
    clipNode->update();

    QSGNode *textNode = QQuickTextInput::updatePaintNode(clipNode->firstChild(), data);
    if (!textNode->parent())
        clipNode->appendChildNode(textNode);

    return clipNode;
}

void QQuickTextField::mousePressEvent(QMouseEvent *event)
{
    Q_D(QQuickTextField);
    d->pressAndHoldHelper.mousePressEvent(event);
    QQuickTextInput::mousePressEvent(event);
}

void QQuickTextField::mouseMoveEvent(QMouseEvent *event)
{
    Q_D(QQuickTextField);
    d->pressAndHoldHelper.mouseMoveEvent(event);
    if (!d->pressAndHoldHelper.timer.isActive())
        QQuickTextInput::mouseMoveEvent(event);
}

void QQuickTextField::mouseReleaseEvent(QMouseEvent *event)
{
    Q_D(QQuickTextField);
    d->pressAndHoldHelper.mouseReleaseEvent(event);
    if (!d->pressAndHoldHelper.longPress)
        QQuickTextInput::mouseReleaseEvent(event);
}

void QQuickTextField::timerEvent(QTimerEvent *event)
{
    Q_D(QQuickTextField);
    if (event->timerId() == d->pressAndHoldHelper.timer.timerId()) {
        d->pressAndHoldHelper.timerEvent(event);
    } else {
        QQuickTextInput::timerEvent(event);
    }
}

QT_END_NAMESPACE
