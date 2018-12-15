-- main.lua

-- 普通传参
function test(p1, p2)
	if(p1 == nil) then
		p1 = "001"
	end
	if(p2 == nil) then
		p2 = "002"
	end
	
	print("p1="..p1.." p2="..p2)
	print("in test function")
end

-- 可变参数
function test2(...)
	local len = table.getn(arg)
	print("arg len is "..len)
	for a = 1,len do
		print("arg["..a.."]="..arg[a])
	end
	return 1, "name"
end

-- 函数传变量
local func = test2
local event = function(p1)
	print("event = "..p1)
end
event("key")
local re,n = func(123, "name")
print("re = "..re..", "..n)

-- 函数重载
function test3()
	print("not arg")
end
function test3(...)
	print("new test")
end
function test3(...)
	print("test3 ...")
end
test3()

