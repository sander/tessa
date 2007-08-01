require 'scripts/hooks'

events = {
	-- Example, implementing MyInterface with interface ID 42 and two events:
	--   MyInterface = {42, {
	--       FirstEvent = 1,
	--       SecondEvent = 2
	--   }},
	-- events:fire('MyInterface', 'SecondEvent') will call event (42,2).
	Core = {1, {
		Started = 1,
		Run = 2,
		PreShutdown = 3,
	}},
	Plugins = {2, {
		AllLoaded = 1,
	}},
	Session = {3, {
		StatusChange = 1,
	}},
}

function events:subscribe(interface, event, callback)
	name = interface..'/'..event
	if not events[name] then
		events[name] = hooks:new()
	end
	return events[name]:insert(callback)
	-- The returned handle may be passed to events:unsubscribe()
end

function events:unsubscribe(name, handle)
	if handle then
		events[interface..'/'..event]:remove(handle)
	end
end

function events:fire(interface, event, ...)
	icode = events[interface][1]
	ecode = events[interface][2][event]
	name = interface..'/'..event
	if not icode then
		log:warning('Attempt to fire an event from a non-existing interface: '
		            ..interface)
		return
	elseif not ecode then
		log:warning('Attempt to fire a non-existant event: '..name)
		return
	end
	if not (interface == 'Core' and event == 'Run') then
		log:info('Firing event: '..name)
	end
	if events[name] then
		return events[name](...)
	end
end
