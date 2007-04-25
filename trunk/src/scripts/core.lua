dofile("scripts/utils.lua.inc");

core = { };

function core:error(etype, msg)
	--printf("ERROR: %s",msg);
	print("ERROR: " ..(msg or etype or "Unknown error"));
end

function core:run()
	print("Core running...");
	events:fire("Events/Core/Started");
	events:fire("Events/Protocols/Global/StatusChange", {status = "chat", msg = "Hello from Tessa!!!"});
	while 1 do
		events:fire("Events/Core/Run");
	end
end


dofile("scripts/services.lua");
dofile("scripts/events.lua");

-- Create events
events:create("Events/Core/Started");
events:create("Events/Core/Run");
events:create("Events/Core/PreShutdown");


dofile("scripts/configs.lua");
dofile("scripts/network.lua");
dofile("scripts/plugins.lua");

events:fire("Events/Core/Started");

plugins:loadall();

core:run();

events:fire("Events/Core/PreShutdown");
