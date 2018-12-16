-- main.lua
function ferror(e)
	print("My error:"..e)
	return "lua change error"
end

function event(e)
	print("c++ call lua function")
	print(e)
	return "lua event return"
end