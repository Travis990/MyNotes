extern "C"
{
#include <lua/lua.h>
#include <lua/lauxlib.h>
#include <lua/lualib.h>
}

int main()
{
	lua_State *L = lua_open();
	luaopen_base(L);
	luaL_loadfile(L, "main.lua");
	lua_pcall(L, 0, 0, 0);

	getchar();
	return 0;
}