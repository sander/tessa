#ifndef LUATHREAD_H
#define LUATHREAD_H

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#include <string>
#include <gloox/TessaInterface.h>

#include <QMap>
#include <QMutex>
#include <QPair>
#include <QQueue>
#include <QString>
#include <QThread>

typedef QMap<std::string, LuaValue> LuaTable;
typedef QPair<std::string, LuaTable> LuaEvent;

int lcPostEvent(lua_State* L);
void PostLuaEvent(std::string name, LuaTable& data);
int FireLuaEvent(char* name, const LuaTable* m);

class LuaThread : public QThread {
  Q_OBJECT

  public:
    LuaThread();
    virtual ~LuaThread() { };
    void enqueueEvent(LuaEvent event);
    LuaEvent dequeueEvent();
    bool queueIsEmpty();
    virtual void postEvent(int EventID, LuaTable* data) = 0;
    void postLuaEvent(std::string name, LuaTable& data);
    lua_State *L;
    lua_State *getLuaState() { return L; };

  protected:
    void run();
    void runScript(char *fileName);

  private:
    QMutex mutex;
    QQueue<LuaEvent> *eventQueue;
};

#endif
