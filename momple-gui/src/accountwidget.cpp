/*
 * accountwidget.cpp is a part of the Momple frontend to Tessa.
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

#include "accountwidget.h"

#include <QImage>
#include <QPixmap>
#include <QtCore>
#include <QGridLayout>

AccountWidget::AccountWidget(QWidget *parent) : QWidget(parent) {
  QGridLayout *mainLayout = new QGridLayout;
  mainLayout->setMargin(0);
  mainLayout->setSpacing(0);
  setLayout(mainLayout);

  nameLabel = new QLabel(cm->ownName());
  nameLabel->setObjectName("nameLabel");
  mainLayout->addWidget(nameLabel, 0, 0, Qt::AlignLeft | Qt::AlignTop);

  /*statusLabel = new QLabel("Available");
  statusLabel->setObjectName("statusLabel");
  statusLabel->setForegroundRole(QPalette::Dark);
  mainLayout->addWidget(statusLabel, 1, 0, Qt::AlignLeft | Qt::AlignTop);*/
  statusWidget = new StatusWidget;
  mainLayout->addWidget(statusWidget, 1, 0, Qt::AlignLeft | Qt::AlignTop);

  avatarLabel = new QLabel;
  /*QImage avatar = *cm->ownAvatar();
  QImage scaledAvatar = avatar.scaled(32, 32, Qt::KeepAspectRatio,
                                      Qt::SmoothTransformation);
  avatarLabel->setPixmap(QPixmap(scaledAvatar));*/
  mainLayout->addWidget(avatarLabel, 0, 2, 2, 1,
                        Qt::AlignRight | Qt::AlignTop);
}
