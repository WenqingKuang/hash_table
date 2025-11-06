#pragma once

#include "ihash_table.h"
#include <functional>
#include <optional>
#include <vector>

class LinearProbingHashTable : public IHashTable {
public:
  explicit LinearProbingHashTable(size_t size, double thresholds = 0.7);

  bool insert(int key) override;
  bool search(int key) const override;
  bool remove(int key) override;

private:
  size_t m;
  double thresholds;
  std::vector<std::optional<int>> table;
  std::vector<bool> deleted;

  std::function<size_t(int)> h_func;

  void rehash();
  double load_factor() const;
};
