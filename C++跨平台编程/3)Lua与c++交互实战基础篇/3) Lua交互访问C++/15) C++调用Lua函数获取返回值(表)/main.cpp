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

	printf("top is %d\n", lua_gettop(lua));
	int errfunc = lua_gettop(lua);
	lua_getglobal(lua, "ferror");
	errfunc++;
	lua_getglobal(lua, "event");
	lua_pushstring(lua, "key");
	
	lua_newtable(lua);
	lua_pushstring(lua, "name");
	lua_pushstring(lua, "Dejan");
	lua_settable(lua, -3);

	if (lua_pcall(lua, 2, 1, errfunc) != 0)
	{
		printf("call event failed %s\n", lua_tostring(lua, -1));
		lua_pop(lua, 1);
	}
	else
	{
		lua_getfield(lua, -1, "id");
		printf("return table id is %d\n", (int)lua_tonumber(lua, -1));
		lua_pop(lua, 2);
	}
	lua_pop(lua, 1);
	printf("top is %d\n", lua_gettop(lua));

	lua_close(lua);
	getchar();
	return 0;
}