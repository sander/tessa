require "hooks"; -- Thanks to Joshua Wise for this, though I have thought of an even better way...

events = {};

function events:create(name)
	events[name] = hooks:new();
end

function events:subscribe(name, callback)
	return events[name]:insert(callback); -- Returns a handle, that may be passed to :unsubscribe()
end

function events:unsubscribe(handle)
	if handle then
		events[name]:remove(handle);
	end
end

function events:fireevent(name, ...)
	return events[name](...);
end