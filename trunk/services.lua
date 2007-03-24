
services = { };

function services:create(name, func, docstring)
	assert(type(name) == "string");
	services[name] = func;
end

function services:delete(name)
	assert(type(name) == "string");
	services[name] = nil;
end

function services:call(name, ...)
	if not services[name] then return nil; end
	services[name](...);
end

function services:pcall(name, ...)
	if type(services[name]) ~= "function" then core:error("NOSERVICE", string.format("Attempt to call non-existant service %s", name)); return nil; end
	local res = { pcall(services[name], ...) };
	if not res[1] then
		--Error
		table.remove(res, 1);
		return unpack(res);
	end
end