/*
 * contactwidget.cpp is a part of the Momple frontend to Tessa.
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

#include "contactwidget.h"

#include <QApplication>
#include <QGridLayout>
#include <QPainter>
#include <QPixmap>
#include <QStyleOption>

#include <QtCore>

ContactWidget::ContactWidget(QWidget *parent, Contact *contact)
               : QFrame(parent)
{
	_contact = contact;

	setFrameStyle(QFrame::NoFrame | QFrame::Plain);
	setCursor(Qt::PointingHandCursor);

	_mainLayout = new QVBoxLayout;
	_mainLayout->setMargin(0);
	_mainLayout->setSpacing(0);
	setLayout(_mainLayout);

	QWidget *statusWidget = new QWidget;
	QGridLayout *statusLayout = new QGridLayout;
	statusLayout->setMargin(0);
	statusLayout->setSpacing(0);
	statusLayout->setColumnStretch(0, 1);
	statusLayout->setColumnStretch(1, 9);
	statusWidget->setLayout(statusLayout);
	_mainLayout->addWidget(statusWidget);

	_nameLabel = new QLabel(contact->name());
	_nameLabel->setObjectName("nameLabel");
	statusLayout->addWidget(_nameLabel, 0, 1, Qt::AlignLeft | Qt::AlignTop);

	QPixmap statusIcon;
	statusIcon.load(":/icons/status/available.png");
	_iconLabel = new QLabel;
	_iconLabel->setPixmap(statusIcon);
	statusLayout->addWidget(_iconLabel, 0, 0, Qt::AlignLeft | Qt::AlignTop);

	_actionWidget = NULL;

	setOpen(false);
	setFocused(false);
}

bool ContactWidget::open() {
	return _open;
}

void ContactWidget::setOpen(bool isOpen) {
	_open = isOpen;
	qApp->setStyleSheet(qApp->styleSheet());

	if (isOpen) {
		if (_actionWidget == NULL) {
			_actionWidget = new ContactActionWidget(this, _contact);
			_mainLayout->addWidget(_actionWidget);
		} else {
			if (!_actionWidget->isVisible())
				_actionWidget->show();
		}
	} else {
		if (_actionWidget != NULL) {
			_actionWidget->hide();
		}
	}

	setFocused(true);
}

bool ContactWidget::focused() {
	return _focused;
}

void ContactWidget::setFocused(bool isFocused) {
	_focused = isFocused;
	qApp->setStyleSheet(qApp->styleSheet());
}

void ContactWidget::mouseReleaseEvent(QMouseEvent *) {
	setOpen(!_open);
}

void ContactWidget::paintEvent(QPaintEvent *) {
	QStyleOption option;
	option.initFrom(this);
	option.state = QStyle::State_Open;

	QPainter painter(this);
	//style().drawControl(QStyle::CE_Widget, &option, &painter, this);
}
