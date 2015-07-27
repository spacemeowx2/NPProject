#include "clua.h"
#include "packedfile.h"
#include "lua.hpp"
#include "LuaBridge/LuaBridge.h"
#include <string.h>
#include <string>
#include <cstdio>

CLua::CLua()
{
	L = luaL_newstate();
    luaL_openlibs(L);
    //把游戏中的类声明到Lua里
    declareClass2Lua();
    //过滤一些函数....
	//doFile("lua/env.lua");
	//lua_getglobal(L, "env");
	//printf("%d\n", lua_setupvalue(L, -2, 1));
    doFile("lua/class.lua");
}

CLua::~CLua()
{
	lua_close(L);
}

void CLua::doFile(const char* fn)
{
	//luaL_dofile(L, fn);
	doString(pfGetString(fn));
}

void CLua::doString(const char* str)
{
	luaL_dostring(L, str);
}

void CLua::doString(const std::string str)
{
	doString(str.c_str());
}

const char* CLua::getError()
{
	const char* error = lua_tostring(L, -1);
	//printf("%s",error);
	lua_pop(L, 1);
	return error;
}