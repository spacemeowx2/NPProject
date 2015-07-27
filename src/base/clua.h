#ifndef CLUA_H
#define CLUA_H
#include <string>
struct lua_State;

class CLua
{
	//#include "lua.hpp"
	private:
		lua_State* L;
		void declareClass2Lua();
	public:
		CLua();
		~CLua();
		void doFile(const char* fn);
		void doString(const char* str);
		void doString(const std::string str);

		lua_State* getState() { return L; }
		const char* getError();
};

#endif // CLUA_H