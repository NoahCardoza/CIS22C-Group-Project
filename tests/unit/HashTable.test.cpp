#include <string>
#include <assert.h>

#include "../../src/HashTable.h"
#include "../../src/Patient.h"

void test_insert(HashTable<Patient> &ht);
void test_synonyms(HashTable<Patient> &ht);
void test_delete(HashTable<Patient> &ht);
void test_rehash(HashTable<Patient> &ht);
void test_rejection(HashTable<Patient> &ht);

int main(void)
{
    HashTable<Patient> ht(7);

    test_insert(ht);

    assert(ht.getSize() == 7);  // make sure size it set properly
    assert(ht.getCount() == 3); // number of buckets used not records

    test_synonyms(ht);
    test_delete(ht);
    test_rejection(ht);
    test_rehash(ht);

    return 0;
}

void test_synonyms(HashTable<Patient> &ht)
{
    Patient query1;
    Patient query2;
    Patient *result1 = nullptr;
    Patient *result2 = nullptr;

    // create queries for synonymous keys
    query1.setId("1e41cf38-8ff1-456f-9f7b-381aa18ce938");
    query2.setId("1e41cf38-8ff1-456f-9f7b-938381aa18ce");

    // confirm both both ids were resolved
    assert(ht.search(&query1, &result1));
    assert(ht.search(&query2, &result2));

    // make sure the pointers point to differnet memory
    assert(*result1 != *result2);

    // // confirm the right records were returned
    assert(result1->getName() == "Hebai David");
    assert(result2->getName() == "Tannaz Tu");
}

void test_delete(HashTable<Patient> &ht)
{
    Patient query1;
    Patient query2;
    Patient *result1 = nullptr;
    Patient *result2 = nullptr;

    // create queries for synonymous keys
    query1.setId("3a09b33c-1c3a-450d-a4e9-ca5ce80aad91"); // points to a bucket with one item
    query2.setId("1e41cf38-8ff1-456f-9f7b-938381aa18ce"); // points to a multi-item bucket

    // confirm both both ids were resolved
    assert(ht.remove(&query1, &result1));
    assert(ht.remove(&query2, &result2));

    assert(ht.getCount() == 2);

    // // confirm the right records were returned
    assert(result1->getName() == "Noah Taylor");
    assert(result2->getName() == "Tannaz Tu");
}

void test_insert(HashTable<Patient> &ht)
{
    ht.insert(new Patient("3a09b33c-1c3a-450d-a4e9-ca5ce80aad91", "Noah Taylor"));
    ht.insert(new Patient("9f66924a-74c4-48c5-907c-gg02cc611192", "Giovany Pham"));
    ht.insert(new Patient("1e41cf38-8ff1-456f-9f7b-381aa18ce938", "Hebai David")); // synonyms
    ht.insert(new Patient("1e41cf38-8ff1-456f-9f7b-938381aa18ce", "Tannaz Tu"));   // synonyms
}

void test_rejection(HashTable<Patient> &ht)
{
    assert(!ht.insert(new Patient("1e41cf38-8ff1-456f-9f7b-381aa18ce938", "Hebai David")));
    assert(!ht.insert(new Patient("9f66924a-74c4-48c5-907c-gg02cc611192", "Giovany Pham")));
}

void test_rehash(HashTable<Patient> &ht)
{
    ht.insert(new Patient("885da398-e134-41ed-8c3b-7a8159f06427", "Chanakarn Kim"));
    ht.insert(new Patient("188076f5-f7c2-4b95-a69f-3431014c98cc", "Joash Lian"));
    ht.insert(new Patient("ffd19c56-e516-4576-90f5-e95cbed7f1b5", "Bradley Karki"));
    ht.insert(new Patient("07458113-f049-4bac-8fa3-3c8b7f14fdc5", "Steven Hui"));
    ht.insert(new Patient("4b735b15-80bb-4f14-80d3-825e23bb0359", "Christian Singh"));
    ht.insert(new Patient("4b735b15-80bb-4f14-80d3-825e23bb0358", "Christian Singh"));
    ht.insert(new Patient("4b735b15-80bb-4f14-80d3-825e23bb0357", "Christian Singh"));
    ht.insert(new Patient("dc406211-6a2d-46fb-bcab-26d16e1795ac", "Isha Pham"));

    assert(ht.getSize() == 17);
}