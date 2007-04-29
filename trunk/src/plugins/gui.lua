
events:subscribe("Events/Contacts/StatusChanged", function (e) GUI_PostEvent(1, { contact = e.contact, status = e.status, string = e.string}); end);
events:subscribe("Events/Network/Jabber/RosterContact", function (e) print("New contact:", e.DisplayName); e.string = e.DisplayName; GUI_PostEvent(1, { contact = e.DisplayName, jid = e.JID, status = e.status, string = e.string}); end);