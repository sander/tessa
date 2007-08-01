/*
 * mainwindow.cpp is a part of the Momple frontend to Tessa.
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

#include "mainwindow.h"

#include "accountwidget.h"
#include "contact.h"
#include "contactwidget.h"
#include "signinwidget.h"

#include <QApplication>
#include <QFrame>
#include <QIcon>
#include <QScrollArea>
#include <QtCore>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
  setWindowIcon(QIcon(":/icons/momple-16x16.png"));
  setWindowTitle("Momple");

  resize(240, 360);

  mainLayout = new QVBoxLayout;
  mainLayout->setMargin(6);
  mainLayout->setSpacing(6);
  setLayout(mainLayout);

  //accountWidget = new SignInWidget(this, cm);
  //accountWidget = new QWidget;
  AccountWidget *accountWidget = new AccountWidget;
  QFrame *accountFrame = new QFrame;
  accountFrame->setObjectName("accountFrame");
  accountFrame->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
  //accountFrame->setLineWidth(0);
  accountFrameLayout = new QVBoxLayout;
  accountFrameLayout->setMargin(3);
  accountFrameLayout->setSpacing(3);
  accountFrame->setLayout(accountFrameLayout);
  accountFrame->layout()->addWidget(accountWidget); 
  mainLayout->addWidget(accountFrame, 0, Qt::AlignTop);

  connect(cm, SIGNAL(signedIn()), SLOT(cm_signedIn()));

  // Temporary: immediately show the roster window
  cm_signedIn();
}

void MainWindow::closeEvent(QCloseEvent *) {
}

void MainWindow::cm_signedIn() {
  /*delete accountWidget;
  accountWidget = new AccountWidget;
  accountWidget->show();
  accountFrameLayout->addWidget(accountWidget);*/

  contactList = new QWidget;
  QVBoxLayout *contactListLayout = new QVBoxLayout;
  contactListLayout->setMargin(0);
  contactListLayout->setSpacing(0);
  contactList->setLayout(contactListLayout);
  QScrollArea *contactArea = new QScrollArea;
  contactArea->setBackgroundRole(QPalette::Base);
  contactArea->setAutoFillBackground(true);
  contactArea->setObjectName("contactArea");
  contactArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  contactArea->setWidgetResizable(true);

  Contact *contact;
  ContactWidget *contactWidget;
  foreach (contact, cm->getContacts()) {
    contactWidget = new ContactWidget(0, contact);
    contactListLayout->addWidget(contactWidget, 0, Qt::AlignTop);
  }

  Contact *testContact = new Contact(0, "test@example", "Test");
  ContactWidget *testContactWidget = new ContactWidget(0, testContact);
  contactListLayout->addWidget(testContactWidget, 0, Qt::AlignTop);

  contactArea->setWidget(contactList);
  mainLayout->addWidget(contactArea, 1);
}
