extern "C"
{
#include <lua/lua.h>
#include <lua/lauxlib.h>
#include <lua/lualib.h>
}

int CTest(lua_State *L)
{
	size_t len;
	const char *name = lua_tolstring(L, 1, &len);
	int age = lua_tonumber(L, 2);
	bool is = lua_toboolean(L, 3);
	printf("name = %s, age = %d is %d\n", name, age, is);
	return 0;
}

int main()
{
	lua_State *lua = lua_open();
	// 打开基本库
	luaopen_base(lua);
	luaopen_string(lua);
	luaopen_table(lua);
	lua_register(lua, "CTest", CTest);

	// 载入脚本
	if (luaL_loadfile(lua, "main.lua"))
	{
		const char *error = lua_tostring(lua, -1);
		printf("lua load error:%s\n", error);
		return -1;
	}

	// 执行脚本
	if (lua_pcall(lua, 0, 0, 0))
	{
		const char *error = lua_tostring(lua, -1);
		printf("lua call error:%s\n", error);
		return -1;
	}

	getchar();
	return 0;
}