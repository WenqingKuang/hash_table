#include "linear_probing.h"
#include <gtest/gtest.h>

TEST(LinearProbing, BasicInsertSearch) {
  LinearProbingHashTable ht(11);
  EXPECT_TRUE(ht.insert(10));
  EXPECT_TRUE(ht.insert(21));
  EXPECT_TRUE(ht.search(10));
  EXPECT_TRUE(ht.search(21));
  EXPECT_FALSE(ht.search(99));
}

TEST(LinearProbing, Remove) {
  LinearProbingHashTable ht(11);
  EXPECT_TRUE(ht.insert(10));
  EXPECT_TRUE(ht.search(10));
  EXPECT_TRUE(ht.remove(10));
  EXPECT_FALSE(ht.search(10));
  EXPECT_TRUE(ht.insert(10));
  EXPECT_TRUE(ht.search(10));
}

TEST(LinearProbing, CollisionHandling) {
  LinearProbingHashTable ht(5);
  EXPECT_TRUE(ht.insert(5));
  EXPECT_TRUE(ht.insert(10));
  EXPECT_TRUE(ht.insert(15));
  EXPECT_TRUE(ht.search(5));
  EXPECT_TRUE(ht.search(10));
  EXPECT_TRUE(ht.search(15));
}

TEST(LinearProbing, Rehash) {
  LinearProbingHashTable ht(5);
  for (int i = 0; i < 10; i++) {
    EXPECT_TRUE(ht.insert(i));
  }
  for (int i = 0; i < 10; i++) {
    EXPECT_TRUE(ht.search(i));
  }
}

TEST(LinearProbing, DuplicateInsert) {
  LinearProbingHashTable ht(11);
  EXPECT_TRUE(ht.insert(42));
  EXPECT_TRUE(ht.insert(42));
  EXPECT_TRUE(ht.search(42));
  EXPECT_TRUE(ht.remove(42));
  EXPECT_FALSE(ht.search(42));
}

TEST(LinearProbing, LargeScale) {
  LinearProbingHashTable ht(101);
  for (int i = 0; i < 5000; i++) {
    EXPECT_TRUE(ht.insert(i));
  }
  for (int i = 0; i < 5000; i++) {
    EXPECT_TRUE(ht.search(i));
  }
}
