function printf(...)
	local s = {...};
	local sf = s[1];
	table.remove(s, 1);
	return print(string.format(sf, unpack(s)));
end

function table.fieldcount(t)
	local c = 0;
	local t = (getmetatable(t) and getmetatable(t)._orig) or t; -- If t is a read-only copy, then use the original to count fields
	for k,v in pairs(t) do c = c +1; end
	return c;
end
  
  -- Returns a read-only pseudo-table, in which the passed table, and all sub-tables are read-only
function ro(t)
	return setmetatable({}, { __index =  ro_index, _orig = t, __newindex = function () error("Attempt to write to a read-only table",0); end, __metatable = nil });
end

--- When used as the __index metamethod of a table, it ensures that table (and sub-tables) may not be written to. Make sure _orig is set to the table you want to be read-only, and also set __newindex to prevent new fields
function ro_index(t, k)
	local proxied_t = getmetatable(t)._orig;
	if proxied_t and type(proxied_t[k]) == "table" then
		return setmetatable({}, { __index = ro_index, _orig = proxied_t[k], __newindex = function () error("Attempt to write to a read-only table",0); end, __metatable = nil });
	else
		return proxied_t[k];
	end
end