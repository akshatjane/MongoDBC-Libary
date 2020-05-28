#include "mongocpp.h"
int main()
{
MongoClient mongoClient("localhost",27017);
DB db=mongoClient.getDB("tmdb");
DBCollection dbCollection=db.getCollection("students");
BasicDBObjectBuilder objectBuilder=BasicDBObjectBuilder::start();
objectBuilder.append("_id",1);
objectBuilder.append("firstName","Akshat");
objectBuilder.append("lastName","Jane");
DBObject dbo=objectBuilder.get();
BasicDBObjectBuilder objectBuilder_=BasicDBObjectBuilder::start();
objectBuilder_.append("_id",1);
DBObject qdbo=objectBuilder_.get();
dbCollection.update(qdbo,dbo);
printf("updated");
return 0;
}