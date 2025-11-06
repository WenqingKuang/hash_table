# Hash Table


## Repository Structure
```
hash_assignment/
├── CMakeLists.txt
├── include/
│   ├── ihash_table.h        # Abstract interface
│   ├── cuckoo_hash.h        # Cuckoo Hashing header (skeleton)
│   └── linear_probing.h     # Linear Probing header (skeleton)
├── src/
│   ├── cuckoo_hash.cpp      # Student implementation
│   └── linear_probing.cpp   # Student implementation
├── tests/
│   ├── test_cuckoo.cpp      # 6 unit tests for Cuckoo Hashing
│   └── test_linear.cpp      # 6 unit tests for Linear Probing
└── README.md
```

## Tasks

- **Cuckoo Hashing** 
  - Use two hash tables and two hash functions.
  - Support displacement with a maximum of `2*m` attempts.
  - Trigger rehash if insertion fails.

- **Linear Probing Hashing** :
  - Use a single table with linear probing for collisions.
  - Use lazy deletion for `remove`.
  - Trigger rehash when load factor > 0.7.

## Build Instructions
This project uses **CMake** and **GoogleTest**.

```bash
# Build
cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build build

# Run all tests
ctest --output-on-failure

# Or run specific test executables
./tests/test_cuckoo
./tests/test_linear
```

