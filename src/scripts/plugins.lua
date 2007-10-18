plugins = setmetatable({}, {_loadedplugins = {}})

function plugins:load(name, path)
	local plugincode = loadfile(path)
	local loadedplugins = getmetatable(plugins)._loadedplugins

	if loadedplugins[name] then
		return
	end

	loadedplugins[name] = { name = name, _env = {}}
	plugins:initialise(loadedplugins[name]._env)
	setfenv(plugincode, loadedplugins[name]._env)

	local success, message = pcall(plugincode)
	if not success then
		log:error('Error while loading plugin '..name..': '..message)
	end
end

function plugins:initialise(env)
	-- Probably there is a more efficient alternative to below, but Lua
	-- doesn't have an operator for duplicating tables
	env.math = {}; env.string = {}; env.table = {}
	for k, v in pairs(math) do env.math[k] = v end
	for k, v in pairs(string) do env.string[k] = v end
	for k, v in pairs(table) do env.table[k] = v end

	env.os = {
		clock = os.clock,
		date = os.date,
		time = os.time,
		difftime = os.difftime
	}

	env.table = table
	env.tostring = tostring
	env.tonumber = tonumber
	env.select = select
	env.type = type
	env.unpack = unpack
	env.pairs = pairs
	env.ipairs = ipairs
	env.assert = assert
	env.pcall = pcall
	--env.print = print
	env.require = function (m)
		local env = getfenv(2)	-- Get the plugin's environment
		if _G[m] then
			return _G[m]
		end
		local l = require(m)
		l = package.loaded[m]
		return _G[m]
	end
	env.beep = function (f, l, r)
		os.execute(string.format('beep -f %d -l %d -r %d',
		                         f or 600, l or 75, r or 1))
	end
	--env.GUI_PostEvent = GUI_PostEvent
	--env.FireLuaEvent = FireLuaEvent
	--env.swig_type = swig_type
	env.setmetatable = setmetatable
	env.getmetatable = getmetatable

	--env.services = ro(services)	-- Read-only
	env.events = ro(events)
	--env.configs = ro(configs)
	env.core = ro(core)
	env.log = ro(log)
end

function plugins:loadall()
	plugins:load('Jabber', 'plugins/jabber.lua')

	events:fire('Plugins', 'AllLoaded')
end

events:subscribe('Core', 'Started', plugins.loadall)
