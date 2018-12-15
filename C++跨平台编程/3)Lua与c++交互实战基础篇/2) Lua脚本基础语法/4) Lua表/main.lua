-- main.lua
--[[
-- 数组表
local tab1 = {"001","002","003"}
for i,v in ipairs(tab1) do
	print("value = "..v)
end

print("========= insert =========")

table.insert(tab1, 3, "002-2")
for i,v in ipairs(tab1) do
	print("value = "..v)
end

print("========= push_back =========")

table.insert(tab1, "004")
for i,v in ipairs(tab1) do
	print("value = "..v)
end

print("========= remove =========")

table.remove(tab1, 3)
for i,v in ipairs(tab1) do
	print("value = "..v)
end

print("========= pop_back =========")

table.remove(tab1)
for i,v in ipairs(tab1) do
	print("value = "..v)
end


-- 哈希表
local tab2 = {id=2, arg=20}
tab2["name"] = "dejan"
tab2["id"] = nil
for k,v in pairs(tab2) do
	print(k.." : "..v)
end
--]]

-- 二维表
local tab3 = {}
tab3[1] = {"name1", "name2"}
tab3[2] = {"value1", "value2"}

for k,v in pairs(tab3) do
	for k2,v2 in pairs(v) do
		print("k2 = "..k2, " v2 = "..v2)
	end
end


