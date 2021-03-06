# LuaDB
Lua CLI client for MongoDB

## Background
I use MongoDB extensively and quite often with the Mongo CLI and JavaScript to do more complex data aggregations and migrations.
On large collections this takes a long time and JavaScript is a huge bottleneck so I started looking for something faster.

## Why Lua?
Pure and simple: with [LuaJIT](http://luajit.org/), Lua is the fastests scripting language available.     

LuaJIT is in most scenarios on par or at most a few percent behind pure C code. For a scripting language that is amazing.


## Setup
**Dependencies**
* [LuaJIT](http://luajit.org/)
* [MongoDB C Driver](http://mongoc.org/)
* [CoreLib](https://github.com/AndreasArvidsson/CoreLib)

**Include directories**
* $(ProjectRoot)/include
* $(CoreLibRoot)/src

**Linker library directories**
* $(ProjectRoot)/lib/lua51
* $(ProjectRoot)/lib/mongoc
* $(ProjectRoot)/lib/bson

