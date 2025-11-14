# ttl

A simple implementation of a dynamic array (`vector`) in C++.

---

## Purpose

This project was created for **learning and understanding** how a dynamic array works internally.  
It is intended for educational purposes and to help grasp concepts similar to `std::vector`.

---

## Features

- Basic dynamic array supporting:
  - `push_back`, `pop_back`, `clear`
  - `resize`, `reserve`
  - `front`, `back`, `at`, and `operator[]`
- Iterators:
  - `begin()` / `end()`
  - `cbegin()` / `cend()` for const access
- Safe access with range checking
- Compatible with range-based for loops

---

## Example Usage

```cpp
#include "vector.hpp"
#include <iostream>

int main() {
    tt::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    std::cout << "Vector contents: ";
    for (auto &x : v) {
        std::cout << x << " ";
    }
    std::cout << "\nSize: " << v.size() << "\n";

    return 0;
}
