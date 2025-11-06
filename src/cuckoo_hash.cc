#include "cuckoo_hash.h"
#include <iostream>

CuckooHashTable::CuckooHashTable(size_t size)
    : m(size), table1(size), table2(size) {
  h1_func = [this](int key) { return key % m; };
  h2_func = [this](int key) { return (key / m) % m; };
}

bool CuckooHashTable::insert(int key) {
  if (search(key)) return true; //already exist
  const int max= 2 * m;
  int cur_key = key;
  bool in_table1 = true;
  for (int cnt = 0; cnt < max; ++cnt) {
    if (!in_table1) {
      size_t idx = h2_func(cur_key);
      if (!table2[idx].has_value()) {
        table2[idx] = cur_key;
        return true;
      }
      std::swap(cur_key, table2[idx].value());
      in_table1 = true;  
    } else {
      size_t idx = h1_func(cur_key);
      if (!table1[idx].has_value()) {
        table1[idx] = cur_key;
        return true;
      }
      std::swap(cur_key, table1[idx].value());
      in_table1 = false;
}
  }
  rehash();
  return insert(cur_key);
}

bool CuckooHashTable::search(int key) const {
  size_t i1 = h1_func(key);
  size_t i2 = h2_func(key);
  return (table1[i1].has_value() && table1[i1].value() == key) ||
         (table2[i2].has_value() && table2[i2].value() == key);
}

bool CuckooHashTable::remove(int key) {
  size_t i1 = h1_func(key);
  size_t i2 = h2_func(key);
  if (table1[i1].has_value() && table1[i1].value() == key) {
    table1[i1].reset(); //delete
    return true;
  }
  if (table2[i2].has_value() && table2[i2].value() == key) {
    table2[i2].reset();
    return true;
  }
  return false;
}

void CuckooHashTable::rehash() {
  std::vector<std::optional<int>> old1 = table1;
  std::vector<std::optional<int>> old2 = table2;

  size_t new_m = m * 2;
  m = new_m;
  h1_func = [this](int key) { return key % m; }; //new hash function
  h2_func = [this](int key) { return (key / m) % m; };
  
  table1.assign(m, std::nullopt);
  table2.assign(m, std::nullopt);
  for (auto &x : old1)
    if (x.has_value()) insert(x.value());
  for (auto &x : old2)
    if (x.has_value()) insert(x.value());
}
