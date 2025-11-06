#include "cuckoo_hash.h"
#include <gtest/gtest.h>

TEST(CuckooHash, BasicInsertSearch) {
  CuckooHashTable ht(11);
  EXPECT_TRUE(ht.insert(10));
  EXPECT_TRUE(ht.insert(21));
  EXPECT_TRUE(ht.search(10));
  EXPECT_TRUE(ht.search(21));
  EXPECT_FALSE(ht.search(99));
}

TEST(CuckooHash, Remove) {
  CuckooHashTable ht(11);
  EXPECT_TRUE(ht.insert(10));
  EXPECT_TRUE(ht.search(10));
  EXPECT_TRUE(ht.remove(10));
  EXPECT_FALSE(ht.search(10));
}

TEST(CuckooHash, Displacement) {
  CuckooHashTable ht(3);
  EXPECT_TRUE(ht.insert(1));
  EXPECT_TRUE(ht.insert(4));
  EXPECT_TRUE(ht.search(1));
  EXPECT_TRUE(ht.search(4));
}

TEST(CuckooHash, Rehash) {
  CuckooHashTable ht(2);
  for (int i = 0; i < 20; i++) {
    EXPECT_TRUE(ht.insert(i));
  }
  for (int i = 0; i < 20; i++) {
    EXPECT_TRUE(ht.search(i));
  }
}

TEST(CuckooHash, DuplicateInsert) {
  CuckooHashTable ht(11);
  EXPECT_TRUE(ht.insert(42));
  EXPECT_TRUE(ht.insert(42));
  EXPECT_TRUE(ht.search(42));
  EXPECT_TRUE(ht.remove(42));
  EXPECT_FALSE(ht.search(42));
}

TEST(CuckooHash, LargeScale) {
  CuckooHashTable ht(101);
  for (int i = 0; i < 5000; i++) {
    EXPECT_TRUE(ht.insert(i));
  }
  for (int i = 0; i < 5000; i++) {
    EXPECT_TRUE(ht.search(i));
  }
}
