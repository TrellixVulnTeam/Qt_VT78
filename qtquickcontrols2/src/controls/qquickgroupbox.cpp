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

#include "qquickgroupbox_p.h"
#include "qquickframe_p_p.h"

QT_BEGIN_NAMESPACE

/*!
    \qmltype GroupBox
    \inherits Frame
    \instantiates QQuickGroupBox
    \inqmlmodule QtQuick.Controls
    \ingroup containers
    \brief A group box control.

    GroupBox is used to layout a logical group of controls together, within
    a titled visual frame. GroupBox does not provide a layout of its own, but
    requires you to position its contents, for instance by creating a \l RowLayout
    or a \l ColumnLayout.

    If only a single item is used within a GroupBox, it will resize to fit the
    implicit size of its contained item. This makes it particularly suitable
    for use together with layouts.

    ### TODO: screenshot

    \code
    GroupBox {
        title: qsTr("Synchronize")
        ColumnLayout {
            anchors.fill: parent
            CheckBox { text: qsTr("E-mail") }
            CheckBox { text: qsTr("Calendar") }
            CheckBox { text: qsTr("Contacts") }
        }
    }
    \endcode

    \sa {Customizing GroupBox}
*/

class QQuickGroupBoxPrivate : public QQuickFramePrivate
{
public:
    QQuickGroupBoxPrivate() : label(Q_NULLPTR) { }

    QString title;
    QQuickItem *label;
};

QQuickGroupBox::QQuickGroupBox(QQuickItem *parent) :
    QQuickFrame(*(new QQuickGroupBoxPrivate), parent)
{
}

/*!
    \qmlproperty string QtQuickControls2::GroupBox::title

    This property holds the title.
*/
QString QQuickGroupBox::title() const
{
    Q_D(const QQuickGroupBox);
    return d->title;
}

void QQuickGroupBox::setTitle(const QString &title)
{
    Q_D(QQuickGroupBox);
    if (d->title != title) {
        d->title = title;
        emit titleChanged();
    }
}

/*!
    \qmlproperty Item QtQuickControls2::GroupBox::label

    This property holds the label item that visualizes \l title.

    \sa {Customizing GroupBox}
*/
QQuickItem *QQuickGroupBox::label() const
{
    Q_D(const QQuickGroupBox);
    return d->label;
}

void QQuickGroupBox::setLabel(QQuickItem *label)
{
    Q_D(QQuickGroupBox);
    if (d->label != label) {
        delete d->label;
        d->label = label;
        if (label && !label->parentItem())
            label->setParentItem(this);
        emit labelChanged();
    }
}

QT_END_NAMESPACE
