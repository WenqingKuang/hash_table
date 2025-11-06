#pragma once

#include "ihash_table.h"
#include <functional>
#include <optional>
#include <vector>

class CuckooHashTable : public IHashTable {
public:
  explicit CuckooHashTable(size_t size);

  bool insert(int key) override;
  bool search(int key) const override;
  bool remove(int key) override;

private:
  size_t m;
  std::vector<std::optional<int>> table1;
  std::vector<std::optional<int>> table2;

  std::function<size_t(int)> h1_func;
  std::function<size_t(int)> h2_func;

  void rehash();
};
