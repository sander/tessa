
#include <gloox/gloox.h>
#include <gloox/connectionlistener.h>

#include <map>

#include <string>



#include "TessaInterface.h"


class DefaultConnectionListener : gloox::ConnectionListener

{
private:
	FireLuaEventFunction luaCall;

public:
	DefaultConnectionListener(int FLE) : luaCall((FireLuaEventFunction)FLE) { printf("Listener created (%p)\n", FLE); };

	virtual void onConnect()

	{
		luaCall("Events/Network/Jabber/Connected", NULL);
		printf("Connected\n");
	}

	virtual void onDisconnect( gloox::ConnectionError e )

	{
		printf("Disconnected\n");
		std::map<std::string, LuaValue> m;

        m["ConnectionError"] = e;

		luaCall("Events/Network/Jabber/Disconnected", &m);

	}

	virtual void onResourceBindError( gloox::ResourceBindError error )

	{

		std::map<std::string, LuaValue> m;

		m["ResourceBindError"] = error;

		luaCall("Events/Network/Jabber/ResourceError", &m);

	}

	virtual void onSessionCreateError( gloox::SessionCreateError error )

	{

		std::map<std::string, LuaValue> m;

		m["SessionCreateError"] = error;

		luaCall("Events/Network/Jabber/SessionCreateError", &m);

	}

	virtual bool onTLSConnect( const gloox::CertInfo& info )

	{

		std::map<std::string, LuaValue> m;

		m["CertStatus"] = info.status;

		m["CertChain"] = info.chain;

		m["CertIssuer"] = info.issuer;

		m["CertServer"] = info.server;

		m["CertDateFrom"] = info.date_from;

		m["CertDateTo"] = info.date_to;

		m["CertProtocol"] = info.protocol;

		m["CertCipher"] = info.cipher;

		m["CertMAC"] = info.mac;

		m["CertCompression"] = info.compression;

		luaCall("Events/Network/Jabber/TLSConnect", &m);
		
		return true;

	}



};

