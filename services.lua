
services = { };

function services:create(name, func, docstring)
	services[name] = func;
end

function services:delete(name)
	services[name] = nil;
end

function services:call(name, ...)
	if not services[name] then return nil; end
	services[name](...);
end

function services:pcall(name, ...)
	if not services[name] then core:raiserror(string.format("Attempt to call non-existant service %s", name)); return nil; end
	local res = { pcall(services[name], ...) };
	if not res[1] then
		--Error
		table.remove(res, 1);
		return unpack(res);
	end
end