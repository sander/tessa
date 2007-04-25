
events:subscribe("Events/Contacts/StatusChanged", function (e) GUI_PostEvent(1, { contact = e.contact, status = e.status, string = e.string}); end);