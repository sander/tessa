/*
 * signinwidget.h is a part of the Momple frontend to Tessa.
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

#ifndef SIGNINWIDGET_H
#define SIGNINWIDGET_H

#include <QLabel>
#include <QLineEdit>
#include <QString>
#include <QWidget>

class SignInWidget : public QWidget
{
	Q_OBJECT

	public:
		SignInWidget(QWidget *parent);
		void setFocusToField();

	private:
		QLabel *errorLabel;
		QLabel *fieldLabel;
		QLineEdit *fieldEdit;
		QLabel *helpLabel;
		QLabel *signingInLabel;
		void enterJidMode();
		void enterPasswordMode();
		void enterSigningInMode();

	private slots:
		void goToNextMode();
		void cm_signInError(QString errorText);
};

#endif
