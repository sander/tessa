#include "tessacorethread.h"

#include "TessaGUIServices.h"
#include <gloox/TessaInterface.h>

#include <QtCore>

void TessaCoreThread::PostEvent(int eventId, LuaTable *data) {
}

void TessaCoreThread::run() {
  //setPriority(QThread::HighestPriority);
  RunScript("scripts/core.lua");
  exec();
}
