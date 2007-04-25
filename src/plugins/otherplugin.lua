
services:call("TestPlugin/HelloWorld");

events:create("Events/Contacts/StatusChanged");

events:subscribe("Events/Plugins/AllLoaded", 
	function ()
		services:call("TestPlugin/GoodbyeWorld");
		events:fire("Events/Contacts/StatusChanged", {string = "Boo!"});
	end);