#ifndef INC_LUAVALUE
#define INC_LUAVALUE
class LuaValue

{

	int type;

	int ival;

	bool bval;

	std::string sval;

public:

	enum {STRING, NUMBER, BOOLEAN};

	LuaValue() {}

	LuaValue(int a) : type(NUMBER), ival(a) { }

	LuaValue(std::string& a) : type(STRING), sval(a) { }

	LuaValue(char* a)   :   type(STRING), sval(a) { }

	LuaValue(bool a) : type(BOOLEAN), bval(a) { }

	int GetType() {return type;}

	bool GetBool() {return bval;}

	std::string GetString() { return sval;}

	int GetNumber() {return ival;}

};

typedef int (*FireLuaEventFunction)(char*, std::map<std::string, LuaValue>*);
#endif
