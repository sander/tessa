/*
 * contactwidget.h is a part of the Momple frontend to Tessa.
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

#ifndef CONTACTWIDGET_H
#define CONTACTWIDGET_H

#include "contact.h"
#include "contactactionwidget.h"

#include <QFrame>
#include <QLabel>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QWidget>

class ContactWidget : public QFrame
{
	Q_OBJECT
	Q_PROPERTY(bool open READ open WRITE setOpen)
	Q_PROPERTY(bool focused READ focused WRITE setFocused)

	public:
		ContactWidget(QWidget *parent, Contact *contact);

		bool open();
		void setOpen(bool isOpen);

		bool focused();
		void setFocused(bool isFocused);

	private:
		Contact *_contact;
                QVBoxLayout *_mainLayout;
		QLabel *_nameLabel;
		QLabel *_iconLabel;
		QLabel *_statusLabel;
		ContactActionWidget *_actionWidget;
		bool _open;
		bool _focused;
		void mouseReleaseEvent(QMouseEvent *event);
		void paintEvent(QPaintEvent *event);
		void setupOpened();
};

#endif
