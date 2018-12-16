-- main.lua
function event(e)
	print("c++ call lua function")
	print(e)
	return "lua event return"
end