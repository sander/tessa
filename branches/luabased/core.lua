dofile("utils.lua.inc");

core = { };

function core:error(etype, msg)
	printf("ERROR: %s",msg);
end

dofile("services.lua");
dofile("events.lua");

-- Create events
events:create("Events/Core/Started");
events:create("Events/Core/PreShutdown");


dofile("configs.lua");
dofile("plugins.lua");

events:fire("Events/Core/Started");

plugins:loadall();

events:fire("Events/Core/PreShutdown");
