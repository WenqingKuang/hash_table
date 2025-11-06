#include "linear_probing.h"
#include <cmath>

LinearProbingHashTable::LinearProbingHashTable(size_t size, double thresholds)
    : m(size), thresholds(thresholds), table(size), deleted(size, false) {
  h_func = [this](int key) { return key % m; };
}

double LinearProbingHashTable::load_factor() const {
  size_t count = 0;
  for (const auto &x : table)
    if (x.has_value())
      count++;
  return static_cast<double>(count) / m;
}

bool LinearProbingHashTable::insert(int key) {
  if (search(key)) 
    return true;
  if (load_factor() > thresholds)
    rehash();

  size_t idx = h_func(key);
  for (size_t i = 0; i < m; ++i) {
    size_t probe = (idx + i) % m;
    if (!table[probe].has_value() || deleted[probe]) {
      table[probe] = key;
      deleted[probe] = false;
      return true;
    }
  }
  rehash();
  return insert(key);
}

bool LinearProbingHashTable::search(int key) const {
  size_t idx = h_func(key);
  for (size_t i = 0; i < m; ++i) {
    size_t probe = (idx + i) % m;
    if (!table[probe].has_value() && !deleted[probe])
      return false;
    if (table[probe].has_value() && table[probe].value() == key)
      return true;
  }
  return false;
}

bool LinearProbingHashTable::remove(int key) {
  size_t idx = h_func(key);
  for (size_t i = 0; i < m; ++i) {
    size_t probe = (idx + i) % m;
    if (!table[probe].has_value() && !deleted[probe])
      return false;
    if (table[probe].has_value() && table[probe].value() == key) {
      table[probe].reset();
      deleted[probe] = true;
      return true;
    }
  }
  return false;
}

void LinearProbingHashTable::rehash() {
  size_t new_size = m * 2;
  std::vector<std::optional<int>> old_table = table;
  std::vector<bool> old_deleted = deleted;

  m = new_size;
  table.assign(m, std::nullopt);
  deleted.assign(m, false);
  h_func = [this](int key) { return key % m; };
  for (size_t i = 0; i < old_table.size(); ++i) {
    if (old_table[i].has_value() && !old_deleted[i])
      insert(old_table[i].value());
  }
}

