extern "C"
{
#include <lua/lua.h>
#include <lua/lauxlib.h>
#include <lua/lualib.h>
}


int main()
{
	lua_State *lua = lua_open();
	// 打开基本库
	luaopen_base(lua);
	luaopen_string(lua);
	luaopen_table(lua);

	// C++给lua传递表
	lua_newtable(lua);
	lua_pushstring(lua, "name");
	lua_pushstring(lua, "Dejan");
	lua_settable(lua, -3);

	lua_pushstring(lua, "age");
	lua_pushnumber(lua, 20);
	lua_settable(lua, -3);

	lua_setglobal(lua, "user");

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

	

	lua_close(lua);
	getchar();
	return 0;
}