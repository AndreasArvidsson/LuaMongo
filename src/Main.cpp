#include "MemoryManager.h"
#include "LuaManager.h"
#include "MongoManager.h"
#include "CliArgs.h"
#include <iostream> //getline

#define LUA_DB_VERSION "0.1.0.0"

int run(int argc, char* argv[]) {
    CliArgs args;
    CliArgs::parse(argc, argv, &args);
    const String uri = MongoManager::getUri(args.host, args.port);

    args.database = "test";

    if (!args.quiet) {
        printf("LuaDB shell version: %s\n", LUA_DB_VERSION);
        if (args.database.size()) {
            printf("Connecting to: %s/%s\n", uri.c_str(), args.database.c_str());
        }
        else {
            printf("Connecting to: %s\n", uri.c_str());
        }
    }

    LuaManager* pLua = LuaManager::getInstance();

    bson_t reply;
    if (!pLua->getMongo()->connect(uri, &reply)) {
        printf("Error: couldn't connect to server, connection attempt failed\n");
        return -1;
    }

    if (!args.quiet) {
        bson_iter_t it;
        if (bson_iter_init_find(&it, &reply, "version")) {
            printf("MongoDB server version: %s\n", bson_iter_utf8(&it, nullptr));
        }
        bson_destroy(&reply);
    }

    if (args.database.size()) {
        pLua->useDatabase(args.database);
    }


    //	pLua->loadFile("../test/test_bsonTypes.lua");
    //	pLua->loadFile("../test/test_crud.lua");
        //pLua->loadFile("../test/performance.lua");

    if (args.files.size()) {
        for (int i = 0; i < args.files.size(); ++i) {
            if (!args.quiet) {
                printf("\nLoading file: %s\n\n", args.files[i].c_str());
            }
            pLua->loadFile(args.files[i]);
        }
        if (!args.quiet && args.shell) {
            printf("\n");
        }
        pLua->setIsRunning(args.shell);
    }

    if (pLua->isRunning()) {
        if (!args.quiet) {
            printf("Type \"help()\" for help\n");
        }
        while (pLua->isRunning()) {
            if (!args.quiet) {
                printf("> ");
                fflush(stdout);
            }
            String commandStr;
            String inputStr;
            if (std::getline(std::cin, inputStr)) {
                commandStr += inputStr;
            }
            if (!commandStr.empty()) {
                pLua->loadString(commandStr.c_str());
            }
        }
    }

    return 0;
}

int main(int argc, char* argv[]) {
    //Disable print buffer
    setvbuf(stdout, NULL, _IONBF, BUFSIZ);

    run(argc, argv);
    LuaManager::destroyInstance();
#ifdef DEBUG_MEMORY
    if (MemoryManager::getInstance()->hasLeak()) {
        printf("\n");
        MemoryManager::getInstance()->displayInfo();
        getchar();
        return 1;
    }
#endif
    //getchar();
    return 0;
}