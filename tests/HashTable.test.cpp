#include <string>
#include <assert.h>

#include "../src/HashTable.h"
#include "../src/Patient.h"

void populate_hashtable(HashTable<Patient *> &ht);

void test_synonyms(HashTable<Patient *> &ht);

int main(void)
{
    HashTable<Patient *> ht;

    populate_hashtable(ht);

    // TODO: test_insert

    // test size it properly tracked
    assert(ht.getCount() == 4);

    test_synonyms(ht);

    // TODO: test_rehash
    // TODO: test_remove

    return 0;
}

void test_synonyms(HashTable<Patient *> &ht)
{
    Patient query1;
    Patient query2;
    Patient *result1 = nullptr;
    Patient *result2 = nullptr;

    // create queries for synonymous keys
    query1.setId("1e41cf38-8ff1-456f-9f7b-381aa18ce938");
    query2.setId("1e41cf38-8ff1-456f-9f7b-938381aa18ce");

    // confirm both both ids were resolved
    assert(ht.search(&query1, result1));
    assert(ht.search(&query2, result1));

    // make sure the pointers point to differnet memory
    assert(result1 != result2);

    // confirm the right records were returned
    assert(result1->getAge() == 3);
    assert(result2->getAge() == 4);
}

void populate_hashtable(HashTable<Patient *> &ht)
{
    Patient *record;

    record = new Patient();
    record->setId("3a09b33c-1c3a-450d-a4e9-ca5ce80aad91");
    record->setAge(1);

    ht.insert(record);

    record = new Patient();
    record->setId("9f66924a-74c4-48c5-907c-bb02cc611192");
    record->setAge(2);

    ht.insert(record);

    record = new Patient();
    record->setId("1e41cf38-8ff1-456f-9f7b-381aa18ce938");
    record->setAge(3);

    ht.insert(record);

    // insert an id that whill hash to the same bucket as
    // the record above
    record = new Patient();
    record->setId("1e41cf38-8ff1-456f-9f7b-938381aa18ce");
    record->setAge(4);

    ht.insert(record);
}