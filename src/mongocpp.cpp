#ifndef MONGOCPP_CPP
#define MONGOCPP_CPP

#include "mongocpp.h"


MongoClient :: MongoClient(string IPAddress,int portNumber)
{
mongoc_init();
bson_error_t error;
this->IPAddress=IPAddress;
this->portNumber=portNumber;
string uri_string="mongodb://"+IPAddress+":"+to_string(portNumber);
this->uri= mongoc_uri_new_with_error(uri_string.c_str(), &error);
if(!(this->uri)) 
{
printf("failed to parse URI: %s\n , error message: %s\n",uri_string,error.message);
return; 
}
client = mongoc_client_new_from_uri (uri);
if(!client) 
{
printf("Unable to Instantiate Mongo Client \n");
return;
}
}

MongoClient :: ~MongoClient()
{
mongoc_uri_destroy(this->uri);
mongoc_client_destroy(this->client);
mongoc_cleanup();
}

DB MongoClient ::  getDB(string databaseName)
{
DB db(this->client,databaseName);
return db;
}


DB::DB(mongoc_client_t *client , string  databaseName)
{
this->databaseName=databaseName;
this->client=client;
this->database=mongoc_client_get_database(client,databaseName.c_str());
}

DB::~DB()
{
mongoc_database_destroy(this->database);
}

DBCollection DB :: getCollection(string collectionName)
{
DBCollection dbCollection(this->client,this->databaseName,collectionName);
return dbCollection;
}


DBCollection :: DBCollection(mongoc_client_t *client,string databaseName,string collectionName)
{
this->collection=mongoc_client_get_collection(client,databaseName.c_str(),collectionName.c_str());
}

DBCollection :: ~DBCollection()
{
mongoc_collection_destroy(collection);
}

void DBCollection ::  insert(DBObject dbObject)
{
bson_error_t error;
if(!mongoc_collection_insert_one(this->collection,dbObject.get(),NULL,NULL,&error))
{
printf("%s\n",error.message);
}
}

void DBCollection ::  insert(DBObject dbObjects[],int size)
{
for(int i=0;i<size;i++)
{
this->insert(dbObjects[i]);
}
}

void DBCollection ::  insert(list<DBObject> dbObjects)
{
for(DBObject odb:dbObjects)  
{
this->insert(odb);
}
}

void DBCollection ::  insert(vector<DBObject> dbObjects)
{
for(DBObject odb:dbObjects)  
{
this->insert(odb);
}
}

void DBCollection ::  remove(DBObject queryObject)
{
bson_error_t error;
if(!mongoc_collection_remove(this->collection,MONGOC_REMOVE_NONE,queryObject.get(),NULL,&error))
{
printf("%s\n",error.message);
}
}

void DBCollection ::  removeAll()
{
bson_error_t error;
bson_t doc=BSON_INITIALIZER;
if(!mongoc_collection_remove(this->collection,MONGOC_REMOVE_NONE,&doc,NULL,&error))
{
printf("%s\n",error.message);
}
}

void DBCollection ::  update(DBObject queryObject,DBObject dbObject)
{
bson_error_t error;
if(!mongoc_collection_update(this->collection,MONGOC_UPDATE_NONE,queryObject.get(),dbObject.get(),NULL,&error))
{
printf("%s\n",error.message);
}
}

DBCursor DBCollection ::   find()
{
DBCursor dbCursor(this->collection);
return dbCursor;
}


BasicDBObjectBuilder::BasicDBObjectBuilder()
{
this->doc=bson_new();
}

BasicDBObjectBuilder::~BasicDBObjectBuilder()
{
bson_destroy(doc);
}

BasicDBObjectBuilder BasicDBObjectBuilder :: start()
{
BasicDBObjectBuilder basicDBObjectBuilder;
return basicDBObjectBuilder;
}

void  BasicDBObjectBuilder ::  append(string key , string value)
{
BSON_APPEND_UTF8(this->doc,key.c_str(),value.c_str());
}

void  BasicDBObjectBuilder ::  append(string key , int value)
{
BSON_APPEND_INT32(this->doc,key.c_str(),value);
}

DBObject BasicDBObjectBuilder ::   get()
{
DBObject dbObject(this->doc);
return dbObject;
}

DBObject ::DBObject(bson_t * object)
{
this->object = object;
}

bson_t * DBObject :: get()
{
return this->object;
}

void DBObject :: put(string key , string value)
{
BSON_APPEND_UTF8(this->object,key.c_str(),value.c_str());
}

void DBObject :: put(string key , int value)
{
BSON_APPEND_INT32(this->object,key.c_str(),value);
}

DBCursor :: DBCursor(mongoc_collection_t *collection)
{
const bson_t queryDoc = BSON_INITIALIZER;
this->cursor= mongoc_collection_find_with_opts(collection,&queryDoc,NULL,NULL);
}

DBCursor :: ~DBCursor()
{
mongoc_cursor_destroy(this->cursor);
}

bool DBCursor :: hasNext()
{
return mongoc_cursor_more(this->cursor);
}

string DBCursor :: next()
{
bson_error_t error;
if(mongoc_cursor_next(this->cursor,&(this->document)))
{
this->ptr=bson_as_json(this->document,NULL);
string str(this->ptr);
return str;
}
if(mongoc_cursor_error(this->cursor,&error))
{
printf("%s\n",error.message);
return "";
}
return "";
}



