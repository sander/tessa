function ro(t)
	-- Returns a read-only pseudo-table, in which the passed table and all
	-- sub-tables are read-only
	return setmetatable({}, {
		__index=ro_index,
		_orig=t,
		__newindex=function ()
			log:error('Attempt to write to a read-only table')
		end,
		__metatable=nil})
end

function ro_index(t, k)
	-- When used as the __index metamethod of a table, it ensures that table
	-- (and sub-tables) may not be written to. Make sure _orig is set to the
	-- table you want to be read-only, and also set __newindex to prevent new
	-- fields.
	local proxied_t = getmetatable(t)._orig
	if proxied_t and type(proxied_t[k]) == 'table' then
		return setmetatable({}, {
			__index=ro_index,
			_orig=proxied_t[k],
			__newindex=function ()
				log:error('Attempt to write to a read-only table')
			end,
			__metatable=nil})
	else
		return proxied_t[k]
	end
end
