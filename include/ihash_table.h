#pragma once

class IHashTable {
public:
  virtual bool insert(int key) = 0;
  virtual bool search(int key) const = 0;
  virtual bool remove(int key) = 0;
  virtual ~IHashTable() {}
};
