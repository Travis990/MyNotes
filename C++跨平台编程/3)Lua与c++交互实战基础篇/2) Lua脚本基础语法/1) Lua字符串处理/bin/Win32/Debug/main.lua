-- main.lua
-- a = 10
local a = 10
dofile("test.lua")
print(a)

-- String字符串处理: 字符串长度 string.len()
local str = "dejan"
print(string.len(str))

-- String字符串处理: 字符串子串 string.sub(str, 3, 5)
str = "HelloLua!"
print(string.sub(str, 3, 5))

-- String字符串处理: 字符串查找 local b, e = string.find(str, "html")支持正则, 一次可以返回两个变量
str = [[
<html>
</html>
]]
local s_start, s_end = string.find(str, "html")
print("s_start = "..s_start.." s_end = "..s_end)

-- String字符串处理: 字符串替换 string.gsub(str, "html", "body")支持正则
local res = string.gsub(str, "html", "body")
print(res)
print(str)






