/*
 * signinwidget.cpp is a part of the Momple frontend to Tessa.
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

#include "signinwidget.h"

#include <QVBoxLayout>

SignInWidget::SignInWidget(QWidget *parent,
                           ConnectionManager *connectionManager)
  : QWidget(parent) {
  cm = connectionManager;

  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->setMargin(0);
  mainLayout->setSpacing(3);
  setLayout(mainLayout);

  errorLabel = new QLabel;
  errorLabel->setObjectName("errorLabel");
  errorLabel->setWordWrap(true);
  errorLabel->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
  errorLabel->hide();
  mainLayout->addWidget(errorLabel);

  fieldLabel = new QLabel;
  fieldLabel->hide();
  mainLayout->addWidget(fieldLabel);

  fieldEdit = new QLineEdit;
  fieldEdit->setObjectName("fieldEdit");
  fieldEdit->hide();
  fieldLabel->setBuddy(fieldEdit);
  mainLayout->addWidget(fieldEdit);

  helpLabel = new QLabel;
  helpLabel->setObjectName("helpLabel");
  helpLabel->setAlignment(Qt::AlignTop | Qt::AlignRight);
  helpLabel->hide();
  mainLayout->addWidget(helpLabel);

  signingInLabel = new QLabel(tr("Signing in..."));
  signingInLabel->setObjectName("signingInLabel");
  signingInLabel->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
  mainLayout->addWidget(signingInLabel);

  connect(fieldEdit, SIGNAL(returnPressed()), SLOT(goToNextMode()));
  connect(cm, SIGNAL(signInError(QString)), SLOT(cm_signInError(QString)));

  //enterJidMode();
}

void SignInWidget::setFocusToField() {
  fieldEdit->setFocus();
}

void SignInWidget::enterJidMode() {
  fieldLabel->setText(tr("Your ID:"));
  fieldLabel->show();

  fieldEdit->setText("");
  fieldEdit->setEchoMode(QLineEdit::Normal);
  fieldEdit->show();

  helpLabel->setText(tr("Example: user@gmail.com"));
  helpLabel->show();

  signingInLabel->hide();
}

void SignInWidget::enterPasswordMode() {
  errorLabel->hide();

  fieldLabel->setText(tr("Password:"));

  fieldEdit->setText("");
  fieldEdit->setEchoMode(QLineEdit::Password);

  helpLabel->hide();

  setFocusToField();
}

void SignInWidget::enterSigningInMode() {
  fieldLabel->hide();
  fieldEdit->hide();
  signingInLabel->show();
}

void SignInWidget::goToNextMode() {
  errorLabel->hide();

  if (fieldEdit->echoMode() == QLineEdit::Normal) {
    cm->connectToServer(fieldEdit->text());
    enterPasswordMode();
  } else {
    enterSigningInMode();
    cm->setPassword(fieldEdit->text());
  }
}

void SignInWidget::cm_signInError(QString errorText) {
  errorLabel->setText(errorText);
  errorLabel->show();
  enterJidMode();
}
