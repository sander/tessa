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

ConnectionManager::ConnectionManager(QObject *parent) : QObject(parent)
{
	waitingForPassword = false;
	gotContactList = false;
}

ConnectionManager::~ConnectionManager()
{
  qDebug() << "Killing the connection manager.";
}

void ConnectionManager::connectToServer(QString/* jidText*/)
{
}

void ConnectionManager::setPassword(QString/* passwordText*/)
{
}

void ConnectionManager::reset()
{
}

void ConnectionManager::cs_needAuthParams()
{
}

void ConnectionManager::authenticate()
{
}

void ConnectionManager::cs_error(int/* errorCode*/)
{
}

void ConnectionManager::cs_warning(int/* warningCode*/)
{
}

void ConnectionManager::cs_authenticated()
{
}

void ConnectionManager::tls_handshaken()
{
}

void ConnectionManager::sessionStart_finished()
{
}

void ConnectionManager::checkOwnVCard_finished()
{
}

void ConnectionManager::checkContactVCard_finished()
{
}

void ConnectionManager::client_rosterRequestFinished(bool /*success*/, int,
                                                     const QString &)
{
}

void ConnectionManager::areWeReadyYet()
{
}

QList<Contact *> ConnectionManager::getContacts()
{
	return contacts;
}

QString ConnectionManager::ownName()
{
	return name;
}

bool ConnectionManager::hasOwnAvatar()
{
	if (!avatar.isNull())
		return true;
	else
		return false;
}

QPixmap ConnectionManager::ownAvatar()
{
	return avatar;
}
