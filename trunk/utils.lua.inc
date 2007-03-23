function printf(...)
	local s = {...};
	local sf = s[1];
	table.remove(s, 1);
	return print(string.format(sf, unpack(s)));
end