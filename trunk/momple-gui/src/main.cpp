/*
 * main.cpp is a part of the Momple frontend to Tessa.
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
#include "mainwindow.h"

#include <QApplication>
#include <QFile>

ConnectionManager *cm;
MainWindow *mw;
LuaThread *lt;

int main(int argc, char **argv) {
  QApplication app(argc, argv);

  QFile file(":/styles/default.qss");
  file.open(QFile::ReadOnly);
  QString styleSheet = QString(file.readAll());
  qApp->setStyleSheet(styleSheet);

  cm = new ConnectionManager;
  mw = new MainWindow;
  cm->setParent(mw);
  mw->show();

  return app.exec();
}
