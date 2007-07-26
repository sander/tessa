#ifndef TESSACORETHREAD_H
#define TESSACORETHREAD_H

#include "LuaInterface.h"

#include <QThread>

class TessaCoreThread : public QThread, public LuaInterface {
  Q_OBJECT

  public:
    void PostEvent(int eventId, LuaTable *data);
    void run();
    void runCoreScripts();
};

#endif
