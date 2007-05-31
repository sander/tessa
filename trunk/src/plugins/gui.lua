
events:subscribe("Events/Contacts/StatusChanged", function (e) GUI_PostEvent(1, { contact = e.contact, status = e.status, string = e.string}); end);
events:subscribe("Events/Network/Jabber/Roster/Presence", function (e) --[[if not e.Online then return; end ]] print("New contact:", e.DisplayName); e.string = e.DisplayName; GUI_PostEvent(1, { contact = e.DisplayName, jid = e.JID, status = e.status, string = e.DisplayName }); end);
