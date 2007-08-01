log = {}

function log:error(error_type, msg)
	print('(EE) '..(msg or error_type or 'Unknown error'))
end

function log:warning(msg)
	print('(WW) '..msg)
end

function log:info(msg)
	print('(II) '..msg)
end
