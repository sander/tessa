configs = setmetatable({}, { configs = {} } );



function configs:set(pref, value)
	getmetatable(configs).configs[pref] = value;
end

function configs:get(pref)
	return getmetatable(configs).configs[pref];
end

function configs:load(file)
	local c = loadfile("configs.dat");
	if not c then return nil; end
	local s, r = pcall(c);
	if not s then return nil; end
	getmetatable(configs).configs = r or {};
	return true;
end

function configs:save()
	local oldhandle = io.output();
	local hcfg = io.open("configs.dat", "w+");
	if not hcfg then return nil; end
	io.output(hcfg);
	io.write("return ");
	serialize(getmetatable(configs).configs);
	io.output(oldhandle);
	hcfg:close();
	return true;
end

events:subscribe("Events/Core/Started", configs.load);
events:subscribe("Events/Core/PreShutdown", configs.save);