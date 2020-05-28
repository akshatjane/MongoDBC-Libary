#include "mongocpp.h"
int main()
{
MongoClient mongoClient("localhost",27017);
DB db=mongoClient.getDB("tmdb");
DBCollection collection=db.getCollection("students");
collection.removeAll();
printf("All Removed");
return 0;
}