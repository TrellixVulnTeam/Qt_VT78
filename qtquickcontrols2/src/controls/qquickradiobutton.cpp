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

#include "qquickradiobutton_p.h"

QT_BEGIN_NAMESPACE

/*!
    \qmltype RadioButton
    \inherits Checkable
    \instantiates QQuickRadioButton
    \inqmlmodule QtQuick.Controls
    \ingroup buttons
    \brief A radio button control.

    RadioButton presents an option button that can be toggled on (checked) or
    off (unchecked). Radio buttons are typically used to select one option
    from a set of options.

    \table
    \row \li \image qtquickcontrols2-radiobutton-normal.png
         \li A radio button in its normal state.
    \row \li \image qtquickcontrols2-radiobutton-checked.png
         \li A radio button that is checked.
    \row \li \image qtquickcontrols2-radiobutton-focused.png
         \li A radio button that has active focus.
    \row \li \image qtquickcontrols2-radiobutton-disabled.png
         \li A radio button that is disabled.
    \endtable

    \code
    ColumnLayout {
        ExclusiveGroup { id: group }
        RadioButton {
            checked: true
            text: qsTr("First")
            ExclusiveGroup.group: group
        }
        RadioButton {
            text: qsTr("Second")
            ExclusiveGroup.group: group
        }
        RadioButton {
            text: qsTr("Third")
            ExclusiveGroup.group: group
        }
    }
    \endcode

    \sa ExclusiveGroup, {Customizing RadioButton}
*/

QQuickRadioButton::QQuickRadioButton(QQuickItem *parent) :
    QQuickCheckable(parent)
{
    setExclusive(true);
}

QT_END_NAMESPACE
