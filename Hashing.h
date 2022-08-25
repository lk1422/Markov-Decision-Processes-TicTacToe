#include <functional>
#include <utility>
#include <vector>

#ifndef HASHING_H
#define HASHING_H
struct VectorHasher { //Faster than using map becuase our length is O(n) while the amount of permutations is O(n!) 
    long unsigned operator()(const std::vector<int> &V) const {
        int hash = V.size();
        for(auto &i : V) {
            hash ^= i + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        }
        return (long unsigned)hash;
    }
};
struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const std::pair<T1, T2>& p) const
    {
        VectorHasher v;
        auto hash1 = v(p.first);
        auto hash2 = std::hash<T2>{}(p.second);
 
        if (hash1 != hash2) {
            return hash1 ^ hash2;             
        }
         
        // If hash1 == hash2, their XOR is zero.
          return hash1;
    }
};
#endif