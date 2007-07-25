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

#include <QGridLayout>
#include <QVBoxLayout>

ContactWidget::ContactWidget(QWidget *parent, Contact *contact)
               : QFrame(parent) {
  _contact = contact;

  setFrameStyle(QFrame::StyledPanel | QFrame::Plain);

  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->setMargin(0);
  mainLayout->setSpacing(0);
  setLayout(mainLayout);

  QWidget *statusWidget = new QWidget;
  QGridLayout *statusLayout = new QGridLayout;
  statusLayout->setMargin(0);
  statusLayout->setSpacing(0);
  statusWidget->setLayout(statusLayout);
  mainLayout->addWidget(statusWidget);

  _nameLabel = new QLabel(contact->name());
  //_nameLabel->setAlignment(Qt::ElideRight);
  statusLayout->addWidget(_nameLabel, 0, 1, Qt::AlignLeft | Qt::AlignTop);

  _iconLabel = new QLabel("( )");
  statusLayout->addWidget(_iconLabel, 0, 0, Qt::AlignLeft | Qt::AlignTop);

  /*_statusLabel = new QLabel("Available");
  statusLayout->addWidget(_statusLabel, 1, 1, Qt::AlignLeft | Qt::AlignTop);*/
}
