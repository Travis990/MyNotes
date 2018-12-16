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

int CTestArr(lua_State *L)
{
	int len = luaL_getn(L, 1);
	for (int i = 1; i <= len; i++)
	{
		lua_pushnumber(L, i); // 2
		lua_gettable(L, 1); // pop index push table[i]
		size_t size;
		printf("%s\n", lua_tolstring(L, -1, &size));
		lua_pop(L, 1);
	}
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
	lua_register(lua, "CTestArr", CTestArr);

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