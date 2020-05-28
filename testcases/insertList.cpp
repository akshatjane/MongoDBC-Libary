#include "mongocpp.h"
int main()
{
//same can be done for vector and array .
MongoClient mc("localhost",27017);
DB db=mc.getDB("tmdb");
DBCollection students=db.getCollection("students");
BasicDBObjectBuilder objectBuilder=BasicDBObjectBuilder::start();
list<DBObject> dbobjects;
objectBuilder.append("_id",809);
objectBuilder.append("firstName","Sherlock");
objectBuilder.append("lastName","Holmes");
dbobjects.push_back(objectBuilder.get());
BasicDBObjectBuilder objectBuilder1=BasicDBObjectBuilder::start(); 
objectBuilder1.append("_id",810);
objectBuilder1.append("firstName","John");
objectBuilder1.append("lastName","Watson");
dbobjects.push_back(objectBuilder1.get());
BasicDBObjectBuilder objectBuilder2=BasicDBObjectBuilder::start();
objectBuilder2.append("_id",811);
objectBuilder2.append("firstName","Jhon");
objectBuilder2.append("lastName","Wick");
dbobjects.push_back(objectBuilder2.get());
students.insert(dbobjects);
cout<<"done done"<<endl;
return 0;
}