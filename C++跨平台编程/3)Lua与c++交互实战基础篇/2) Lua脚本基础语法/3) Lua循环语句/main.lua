-- main.lua

-- while循环语句
--[[
local i = 100
while( not(i < 0) ) do
	print("i = "..i)
	i = i - 1
	if(i == 90) then
		print("break while")
		break
	end
end
--]]

-- repeat循环语句
--[[
local i = 100
repeat
	i = i - 1
	print("i = "..i)
until i<100
--]]

-- for循环语句 - 数值循环
--[[
-- 一次跳2步
for var = 1,5,2 do
	print("var = "..var)
end
print("-----------------")
-- 可以省略最后的步数,默认一次跳1步
for var = 1,5 do
	print("var = "..var);
end
--]]


-- for循环语句 - 范型循环
local days = {"Sun","Mon","Tue"}
for i,v in ipairs(days) do
	print(i..":"..v)
end
for i,v in pairs(days) do
	print(i.."=="..v)
end
local tab = { [1] = "A", [2] = "B", [3] = "C", [5] = "E" }
for i,v in pairs(tab) do
	print(i.."=>"..v)
end
for i,v in ipairs(tab) do
	print(i.."--"..v)
end
