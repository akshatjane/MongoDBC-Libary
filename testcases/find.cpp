#include "mongocpp.h"
int main()
{
MongoClient mongoClient("localhost",27017);
DB db=mongoClient.getDB("tmdb");
DBCollection collection=db.getCollection("students");
DBCursor cursor=collection.find();
while(cursor.hasNext())
{
printf("%s\n",cursor.next().c_str());
}
return 0;
}
