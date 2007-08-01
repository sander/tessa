/*
 * connectionmanager.cpp is a part of the Momple frontend to Tessa.
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

#include "connectionmanager.h"

#include <QByteArray>
#include <QStringList>
#include <QtCore>

ConnectionManager::ConnectionManager(QObject *parent) : QObject(parent) {
  waitingForPassword = false;
  gotContactList = false;

  /*client = new XMPP::Client(this);
  client->setClientName("Momple");
  client->setClientVersion("0.1-dev");
  QStringList features;
  client->setFeatures(XMPP::Features(features));

  XMPP::AdvancedConnector *conn = new XMPP::AdvancedConnector(this);

  QCA::TLS *tls = new QCA::TLS(this);
  tlsHandler = new XMPP::QCATLSHandler(tls);
  connect(tlsHandler, SIGNAL(tlsHandshaken()), SLOT(tls_handshaken()));

  stream = new XMPP::ClientStream(conn, tlsHandler, this);
  stream->setAllowPlain(XMPP::ClientStream::AllowPlainOverTLS);
  connect(stream, SIGNAL(needAuthParams(bool, bool, bool)),
          SLOT(cs_needAuthParams()));
  connect(stream, SIGNAL(authenticated()), SLOT(cs_authenticated()));
  connect(stream, SIGNAL(error(int)), SLOT(cs_error(int)));
  connect(stream, SIGNAL(warning(int)), SLOT(cs_warning(int)));

  connect(client, SIGNAL(rosterRequestFinished(bool, int, const QString &)),
          SLOT(client_rosterRequestFinished(bool, int, const QString &)));*/
}

ConnectionManager::~ConnectionManager() {
  qDebug() << "Killing the connection manager.";
}

void ConnectionManager::connectToServer(QString/* jidText*/) {
  /*XMPP::Jid jid = XMPP::Jid(jidText);
  client->connectToServer(stream, jid);*/
}

void ConnectionManager::setPassword(QString/* passwordText*/) {
  /*password = passwordText;
  if (waitingForPassword)
    authenticate();*/
}

void ConnectionManager::reset() {
  //waitingForPassword = false;
}

void ConnectionManager::cs_needAuthParams() {
  /*if (password != "")
    authenticate();
  else
    waitingForPassword = true;*/
}

void ConnectionManager::authenticate() {
  /*stream->setUsername(stream->jid().node());
  stream->setRealm(stream->jid().domain());
  stream->setPassword(password);
  stream->continueAfterParams();*/
}

void ConnectionManager::cs_error(int/* errorCode*/) {
  //qDebug() << "error" << errorCode;
}

void ConnectionManager::cs_warning(int/* warningCode*/) {
  /*if (warningCode == XMPP::ClientStream::WarnNoTLS)
    stream->continueAfterWarning();
  else
    qDebug() << "warning" << warningCode;*/
}

void ConnectionManager::cs_authenticated() {
  /*client->start(stream->jid().host(), stream->jid().user(), password,
                stream->jid().resource());

  XMPP::JT_Session *j = new XMPP::JT_Session(client->rootTask());
  connect(j, SIGNAL(finished()), SLOT(sessionStart_finished()));
  j->go(true);

  client->setPresence(XMPP::Status());*/
}

void ConnectionManager::tls_handshaken() {
  //tlsHandler->continueAfterHandshake();
}

void ConnectionManager::sessionStart_finished() {
  /*XMPP::JT_Session *j = (XMPP::JT_Session *)sender();
  if (j->success()) {
    client->rosterRequest();

    XMPP::JT_VCard *task = new XMPP::JT_VCard(client->rootTask());
    connect(task, SIGNAL(finished()), SLOT(checkOwnVCard_finished()));
    task->get(client->jid());
    task->go(true);
  } else {
    cs_error(-1);
  }*/
}

void ConnectionManager::checkOwnVCard_finished() {
  /*XMPP::JT_VCard *j = (XMPP::JT_VCard *)sender();
  if (j->vcard().isEmpty() ||
      (j->vcard().nickName().isEmpty() && j->vcard().fullName().isEmpty())) {
    name = client->jid().user();
  } else {
    if (!j->vcard().nickName().isEmpty())
      name = j->vcard().nickName();
    else
      name = j->vcard().fullName();
    if (!j->vcard().photo().isEmpty())
      avatar = new QImage(j->vcard().photo());
  }
  areWeReadyYet();*/
}

void ConnectionManager::checkContactVCard_finished() {
    /*XMPP::JT_VCard *j = (XMPP::JT_VCard *)sender();
    //qDebug() << j->vcard().nickName();*/
}

void ConnectionManager::client_rosterRequestFinished(bool /*success*/, int,
                                                     const QString &) {
  /*if (success) {
    XMPP::JT_VCard *task;
    QString name;
    XMPP::LiveRoster roster = client->roster();
    for (XMPP::LiveRoster::Iterator it = roster.begin();
         it != roster.end();
         ++it) {
      XMPP::LiveRosterItem &item = *it;
      if (!item.name().isEmpty())
        name = item.name();
      else
        name = item.jid().user();
      Contact *contact = new Contact(this, this, item.jid().bare(), name);
      contacts << contact;
      task = new XMPP::JT_VCard(client->rootTask());
      //connect(task, SIGNAL(finished()), SLOT(checkContactVCard_finished()));
      task->get(item.jid());
      //task->go(true);
    }
    gotContactList = true;
    areWeReadyYet();
  }*/
}

void ConnectionManager::areWeReadyYet() {
  /*if (!name.isEmpty() && gotContactList)
    emit signedIn();*/
}

QList<Contact *> ConnectionManager::getContacts() {
  return contacts;
}

QString ConnectionManager::ownName() {
  return name;
}

bool ConnectionManager::hasOwnAvatar() {
  if (!avatar.isNull())
    return true;
  else
    return false;
}

QPixmap ConnectionManager::ownAvatar() {
  return avatar;
}
