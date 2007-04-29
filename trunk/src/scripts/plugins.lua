plugins = setmetatable({}, { _loadedplugins = {}} );

function plugins:load(name, path)
	local plugincode = loadfile(path); -- Loads the plugin's code, doesn't run it
	local loadedplugins = getmetatable(plugins)._loadedplugins; 
	
	if loadedplugins[name] then return nil; end
	loadedplugins[name] = { name = name, _env = {}};
	plugins:initialise(loadedplugins[name]._env);
	setfenv(plugincode, loadedplugins[name]._env); -- This sets that _env table as the plugin's environment. Globals will be stored in it.
	local success, message = pcall(plugincode); -- Now we run the code, and catch any errors
	if not success then
		error("PLUGINLOAD: "..name..", "..message);
		return nil;
	end
	return true;
end

function plugins:initialise(env)

	-- Probably there is a more efficient alternative to below, but Lua doesn't have an operator for duplicating tables
	env.math = {}; env.string = {}; env.table = {};
	for k, v in pairs(math) do env.math[k] = v end
	for k, v in pairs(string) do env.string[k] = v end
	for k, v in pairs(table) do env.table[k] = v end
	
	env.os = { clock = os.clock, date = os.date, time = os.time, difftime = os.difftime }

	env.table = table;
	env.tostring = tostring;
	env.tonumber = tonumber;
	env.select = select;
	env.type = type;
	env.unpack = unpack;
	env.pairs = pairs;
	env.ipairs = ipairs;
	env.assert = assert;
	env.pcall = pcall;
	env.print = print;
	env.error = error;
	env.require =	function (m)
					local env = getfenv(2); -- Get the plugin's environment
					if _G[m] then return _G[m]; end
					local l = require(m);
					print("l", type(l));
					l = package.loaded[m];
					print("l2", type(l));
					return _G[m];
				end;
	env.beep = function (f, l, r) os.execute(string.format("beep -f %d -l %d -r %d", f or 600, l or 75, r or 1)); end
	--[[function (m)
					local env = getfenv(2); -- Get the plugin's environment
					local f = package.loadlib (m..".so", "luaopen_"..m)
					env[m] = {};
					setfenv(f, env[m]);
					f();
				end]]
	
	--[[function (m)
					local env = getfenv(2); -- Get the plugin's environment
					require(m);
					setfenv(require, getfenv(0));
				end; ]]
				
	
	env.GUI_PostEvent = GUI_PostEvent;
	env.FireLuaEvent = FireLuaEvent;
	env.swig_type = swig_type;
	env.setmetatable = setmetatable;
	env.getmetatable = getmetatable;
	
	env.services = ro(services); -- Read-only
	env.events = ro(events);
	env.configs = ro(configs);
	env.core = ro(core);

	--env["_G"] = env;
end

function plugins:loadall(folder)
	events:create("Events/Plugins/AllLoaded");
	
	plugins:load("Test plugin", "plugins/testplugin.lua");
	plugins:load("Another plugin", "plugins/otherplugin.lua");
	plugins:load("Jabber", "plugins/jabber.lua");
	--plugins:load("idlebeep", "plugins/idlebeep.lua");
	plugins:load("GUI", "plugins/gui.lua");
	
	events:fire("Events/Plugins/AllLoaded");
end

events:subscribe("Events/Core/Started", plugins.loadall);
