#include "mongocpp.h"
int main()
{
MongoClient mongoClient("localhost",27017);
DB db=mongoClient.getDB("tmdb");
DBCollection collection=db.getCollection("students");
BasicDBObjectBuilder objectBuilder=BasicDBObjectBuilder::start();
objectBuilder.append("_id",13);
DBObject qdbo=objectBuilder.get();
collection.remove(qdbo);
printf("removed");
return 0;
}