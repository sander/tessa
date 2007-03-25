dofile("utils.lua.inc");

core = { };

function core:error(etype, msg)
	printf("ERROR: %s",msg);
end

dofile("services.lua");
dofile("events.lua");
dofile("plugins.lua");

plugins:loadall();

