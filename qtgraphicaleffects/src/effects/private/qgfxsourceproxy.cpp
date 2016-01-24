/****************************************************************************
**
** Copyright (C) 2015 Jolla Ltd, author: <gunnar.sletta@jollamobile.com>
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt Graphical Effects module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL21$
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
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** As a special exception, The Qt Company gives you certain additional
** rights. These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qgfxsourceproxy_p.h"

#include <private/qquickshadereffectsource_p.h>
#include <private/qquickitem_p.h>
#include <private/qquickimage_p.h>

QT_BEGIN_NAMESPACE

QGfxSourceProxy::QGfxSourceProxy(QQuickItem *parentItem)
    : QQuickItem(parentItem)
    , m_input(0)
    , m_output(0)
    , m_proxy(0)
    , m_interpolation(AnyInterpolation)
{
}

QGfxSourceProxy::~QGfxSourceProxy()
{
    delete m_proxy;
}

void QGfxSourceProxy::setInput(QQuickItem *input)
{
    if (m_input == input)
        return;
    m_input = input;
    polish();
    emit inputChanged();
}

void QGfxSourceProxy::setOutput(QQuickItem *output)
{
    if (m_output == output)
        return;
    m_output = output;
    emit activeChanged();
    emit outputChanged();
}

void QGfxSourceProxy::setSourceRect(const QRectF &sourceRect)
{
    if (m_sourceRect == sourceRect)
        return;
    m_sourceRect = sourceRect;
    polish();
    emit sourceRectChanged();
}

void QGfxSourceProxy::setInterpolation(Interpolation i)
{
    if (m_interpolation == i)
        return;
    m_interpolation = i;
    polish();
    emit interpolationChanged();
}


void QGfxSourceProxy::useProxy()
{
    if (!m_proxy)
        m_proxy = new QQuickShaderEffectSource(this);
    m_proxy->setSourceRect(m_sourceRect);
    m_proxy->setSourceItem(m_input);
    m_proxy->setSmooth(m_interpolation != NearestInterpolation);
    setOutput(m_proxy);
}

void QGfxSourceProxy::updatePolish()
{
    if (m_input == 0) {
        setOutput(0);
        return;
    }

    QQuickItemPrivate *d = QQuickItemPrivate::get(m_input);
    QQuickImage *image = qobject_cast<QQuickImage *>(m_input);
    QQuickShaderEffectSource *shaderSource = qobject_cast<QQuickShaderEffectSource *>(m_input);
    bool layered = d->extra.isAllocated() && d->extra->transparentForPositioner;

    if (shaderSource) {
        if (layered) {
            shaderSource->setSourceRect(m_sourceRect);
            shaderSource->setSmooth(m_interpolation != NearestInterpolation);
        }
        setOutput(m_input);

    } else if (image && image->fillMode() == QQuickImage::Stretch && m_input->childItems().size() == 0) {
        // item is an image with default tiling, use directly
        setOutput(m_input);

    } else if (!image && m_input->isTextureProvider() && m_input->childItems().size() == 0) {
        // item is a texture provider without children, use directly...
        setOutput(m_input);

    } else {
        useProxy();
    }

    // Remove the proxy if it is not in use..
    if (m_proxy && m_output == m_input) {
        delete m_proxy;
        m_proxy = 0;
    }
}

QT_END_NAMESPACE
