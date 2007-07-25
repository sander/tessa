/*
 * connectionmanager.h is a part of the Momple frontend to Tessa.
 * Copyright (C) 2007  Sander Dijkhuis
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include "contact.h"
#include "luathread.h"

#include <QList>
#include <QObject>
#include <QPixmap>
#include <QString>

class Contact;

class ConnectionManager : public QObject {
  Q_OBJECT

  public:
    ConnectionManager(QObject *parent = 0);
    ~ConnectionManager();
    void connectToServer(QString jidText);
    void setPassword(QString passwordText);
    void reset();
    QString ownName();
    QPixmap ownAvatar();
    bool hasOwnAvatar();
    QList<Contact *> getContacts();

  signals:
    void signInError(QString errorText);
    void signedIn();

  private:
    LuaThread *lt;
    void authenticate();
    /*XMPP::ClientStream *stream;
    XMPP::QCATLSHandler *tlsHandler;
    XMPP::Client *client;*/
    bool waitingForPassword;
    QString password;
    QString name;
    QPixmap avatar;
    QList<Contact *> contacts;
    bool gotContactList;
    void areWeReadyYet();

  private slots:
    void cs_needAuthParams();
    void cs_error(int errorCode);
    void cs_warning(int warningCode);
    void cs_authenticated();
    void tls_handshaken();
    void sessionStart_finished();
    void checkOwnVCard_finished();
    void client_rosterRequestFinished(bool success, int statusCode,
                                      const QString &statusString);
    void checkContactVCard_finished();
};

#endif
