#include "mongocpp.h"
int main()
{
MongoClient mongoClient("localhost",27017);
DB db=mongoClient.getDB("tmdb");
DBCollection dbCollection=db.getCollection("students");
BasicDBObjectBuilder objectBuilder=BasicDBObjectBuilder::start();
objectBuilder.append("_id",13);
objectBuilder.append("firstName","jim");
objectBuilder.append("lastName","moriarty");
DBObject dbo=objectBuilder.get();
dbCollection.insert(dbo);
printf("inserted");
return 0;
}