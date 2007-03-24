dofile("utils.lua.inc");

core = { };

function core:error(etype, msg)
	printf("ERROR: %s",msg);
end

dofile("services.lua");
dofile("events.lua");
dofile("plugins.lua");

plugins:load("Test plugin", "plugins/testplugin.lua");
plugins:load("Another plugin", "plugins/otherplugin.lua");