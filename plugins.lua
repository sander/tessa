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
		core:error("PLUGINLOAD", message);
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
	
	env.setmetatable = setmetatable;
	env.getmetatable = getmetatable;
	
	env.services = ro(services); -- Read-only
	env.events = ro(events);

	env["_G"] = env;
end