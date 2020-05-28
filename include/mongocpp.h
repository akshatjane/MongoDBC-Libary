#ifndef MONGOCPP_H
#define MONGOCPP_H 

#include<mongoc.h>
#include<iostream>
#include<vector>
#include<list>

using namespace std;

class MongoClient;
class DB;
class DBCollection;
class BasicDBObjectBuilder;
class DBObject;
class DBCursor;

class MongoClient
{
private:
string IPAddress;
int portNumber;
mongoc_client_t *client;
mongoc_uri_t *uri;
public:
MongoClient(string IPAddress,int portNumber);
DB getDB(string databaseName);
~MongoClient();
};

class DB
{
private:
mongoc_database_t *database;
mongoc_client_t *client;
string databaseName;
DB(mongoc_client_t *client , string  databaseName);
public:
DBCollection getCollection(string collectionName);
~DB();
friend class MongoClient;
};	

class DBCollection
{
private:
mongoc_collection_t *collection;
DBCollection(mongoc_client_t *client,string databaseName,string collectionName);
public:
~DBCollection();
void insert(DBObject dbObject);
void insert(DBObject dbObjects[],int size);
void insert(list<DBObject> dbObjects);
void insert(vector<DBObject> dbObjects);
void remove(DBObject queryObject);
void removeAll();
void update(DBObject queryObject,DBObject dbObject);
DBCursor find();
friend class DB;
};

class BasicDBObjectBuilder
{
private:
bson_t * doc; 
BasicDBObjectBuilder();
public:
~BasicDBObjectBuilder();
static BasicDBObjectBuilder start();
void append(string key , string value);
void append(string key , int value);
DBObject get();
};

class DBObject
{
private:
bson_t *object;
DBObject(bson_t * object);
bson_t * get();
public:
void put(string key , string value);
void put(string key , int value);
friend class BasicDBObjectBuilder;
friend class DBCollection;
};

class DBCursor
{
private :
mongoc_cursor_t *cursor;
const bson_t *document;
char * ptr;
DBCursor(mongoc_collection_t *collection);
public:
~DBCursor();
bool hasNext();
string next();
friend class DBCollection;
};

#endif