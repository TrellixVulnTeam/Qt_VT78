/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtWebEngine module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
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

#ifndef QWEBENGINECOOKIESTORECLIENT_P_H
#define QWEBENGINECOOKIESTORECLIENT_P_H

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

#include "qtwebenginecoreglobal_p.h"

#include "cookie_monster_delegate_qt.h"
#include "qwebenginecallback_p.h"
#include "qwebenginecookiestoreclient.h"

#include <QList>
#include <QMap>
#include <QNetworkCookie>
#include <QUrl>

QT_BEGIN_NAMESPACE

class QWEBENGINE_PRIVATE_EXPORT QWebEngineCookieStoreClientPrivate {
    struct CookieData {
        quint64 callbackId;
        QNetworkCookie cookie;
        QUrl origin;
    };

public:
    Q_DECLARE_PUBLIC(QWebEngineCookieStoreClient)
    QtWebEngineCore::CallbackDirectory callbackDirectory;
    QList<CookieData> m_pendingUserCookies;
    quint64 m_nextCallbackId;
    bool m_deleteSessionCookiesPending;
    bool m_deleteAllCookiesPending;
    bool m_getAllCookiesPending;

    QtWebEngineCore::CookieMonsterDelegateQt *delegate;
    QWebEngineCookieStoreClient *q_ptr;

    QWebEngineCookieStoreClientPrivate(QWebEngineCookieStoreClient *q);
    ~QWebEngineCookieStoreClientPrivate();

    void processPendingUserCookies();
    void setCookie(const QWebEngineCallback<bool> &callback, const QNetworkCookie &cookie, const QUrl &origin);
    void deleteCookie(const QNetworkCookie &cookie, const QUrl &url);
    void deleteSessionCookies();
    void deleteAllCookies();
    void getAllCookies();

    bool canSetCookie(const QUrl &firstPartyUrl, const QByteArray &cookieLine, const QUrl &url);

    void onGetAllCallbackResult(qint64 callbackId, const QByteArray &cookieList);
    void onSetCallbackResult(qint64 callbackId, bool success);
    void onDeleteCallbackResult(qint64 callbackId, int numCookies);
    void onCookieChanged(const QNetworkCookie &cookie, bool removed);
};

QT_END_NAMESPACE

#endif // QWEBENGINECOOKIESTORECLIENT_P_H
