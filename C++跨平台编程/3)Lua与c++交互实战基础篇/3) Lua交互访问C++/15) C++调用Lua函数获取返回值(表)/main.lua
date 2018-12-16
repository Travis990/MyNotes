-- main.lua
function ferror(e)
	print("My error:"..e)
	return "lua change error"
end

function event(e, obj)
	print("c++ call lua function")
	print(e)
	print(obj.name)
	--return "lua event return"
	local re = {id = 123}
	return re
end