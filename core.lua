dofile("utils.lua.inc");

core = { };

function core:raiserror(msg)
	printf("ERROR: %s",msg);
end

dofile("services.lua");
dofile("events.lua");

dofile("plugins/testplugin.lua");
dofile("plugins/otherplugin.lua");