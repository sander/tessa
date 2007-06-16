
#include "gloox.h"
#include "rosterlistener.h"
#include "rostermanager.h"

#include <map>
#include <string>

#include "TessaInterface.h"



class DefaultRosterListener : gloox::RosterListener

{
private:
	FireLuaEventFunction luaCall;

public:
	DefaultRosterListener(long FLE) : luaCall((FireLuaEventFunction)FLE) { printf("Roster listener created (%p)\n", FLE); }

	virtual void handleRoster(const gloox::Roster& rost)
	{
		gloox::Roster::const_iterator it;
		for (it=rost.begin(); it != rost.end(); it++)
		{
			gloox::RosterItem* contact = (*it).second;
			std::map<std::string, LuaValue> m;
			
			m["JID"] = contact->jid();
			m["DisplayName"] = contact->name();
			m["Online"] = contact->online();
			luaCall("Events/Network/Jabber/Roster/Contact", &m);
		}

		luaCall("Events/Network/Jabber/Roster/Retrieved", NULL);
	}
	
	virtual void handleItemAdded  	(  	const gloox::JID &   	 jid  	 ) {}
	virtual void handleItemSubscribed (  	const gloox::JID &   	 jid  	 )  {}
	virtual void handleItemRemoved  	(  	const gloox::JID &   	 jid  	 ) {}
	virtual void handleItemUpdated  	(  	const gloox::JID &   	 jid  	 ) {}
	virtual void handleItemUnsubscribed  (	const gloox::JID &   	 jid  	 ) {}
	virtual void handleRosterPresence(const gloox::RosterItem& contact, const std::string& resource, gloox::Presence presence, const std::string& msg)
	{
		std::map<std::string, LuaValue> m;
		m["JID"] = contact.jid();
		m["DisplayName"] = contact.name();
		m["Online"] = contact.online();
		m["Resource"] = resource;
		m["Status"] = (int)presence;
		m["StatusMsg"] = msg;
		luaCall("Events/Network/Jabber/Roster/Presence", &m);
	}
	
	virtual void handleSelfPresence  	(  	const gloox::RosterItem &   	 item,
		const std::string &  	resource,
		gloox::Presence  	presence,
		const std::string &  	msg	 
	) 	{}
	
	virtual bool handleSubscriptionRequest  	(  	const gloox::JID &   	 jid,
		const std::string &  	msg	 
	)  { return true; }
		
	virtual bool handleUnsubscriptionRequest  	(  	const gloox::JID &   	 jid,
		const std::string &  	msg	 
	)  { return true; }
	
	virtual void handleNonrosterPresence  	(  	gloox::Stanza *   	 stanza  	 ) {}
	virtual void handleRosterError(gloox::Stanza *stanza) {}
	

};

