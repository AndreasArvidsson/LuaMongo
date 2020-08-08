#pragma once
#include <string>
#include "LuaDB.h"

class MongoManager;

class LuaManager {
public:
	static LuaManager* getInstance();
	static void destroyInstance();

	MongoManager* getMongo() const;

	void useDatabase(const std::string& name);

	const bool isRunning();
	void setIsRunning(bool isRunning);

	void loadFile(const std::string&path);
	void loadString(const std::string&str);

private:
	static LuaManager *_pInstance;

	std::unordered_map<std::string, LuaDB*> _databases;
	MongoManager *_pMongo;
	LuaDB *_pDB;
	bool _isRunning;
	lua_State *_L;

	LuaManager();
	~LuaManager();

	LuaDB* getDatabase(const std::string& name);
	lua_State* createNewState();
	void printError(lua_State *L);
	void doLoadString(lua_State *L, const std::string& str);
	
	static const luaL_reg _bindFuncs[];
	
	static int lua_help(lua_State *L);
	static int lua_use(lua_State *L);
	static int lua_print(lua_State* L);
	static int lua_printJson(lua_State *L);
	static int lua_toJson(lua_State *L);
	static int lua_time(lua_State *L);
	static int lua_exit(lua_State *L);
	static int lua_getSiblingDB(lua_State *L);
	static int lua_showDatabases(lua_State *L);
	static int lua_showCollections(lua_State *L);
	static int lua_getDatabaseNames(lua_State *L);
	
	static int lua_cTest(lua_State *L);

};
