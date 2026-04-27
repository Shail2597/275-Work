#ifndef MYMAP_H
#define MYMAP_H

#include <vector>
#include <utility>

template <typename K, typename V>
class Map {
private:
  std::vector<std::pair<K, V>> dataStore;

  // Returns the index of the first element >= key
  std::size_t lowerBound(const K& key) const {
    std::size_t startIdx = 0;
    std::size_t endIdx = dataStore.size();

    while (startIdx < endIdx) {
      std::size_t pivot = startIdx + (endIdx - startIdx) / 2;
      if (dataStore[pivot].first < key) {
        startIdx = pivot + 1;
      } else {
        endIdx = pivot;
      }
    }
    return startIdx;
  }

  // Helper to check equality using only the < operator
  bool keysEqual(const K& a, const K& b) const {
    return !(a < b) && !(b < a);
  }

public:
  Map() = default;
  ~Map() = default;
  Map(const Map&) = default;
  Map(Map&&) = default;
  Map& operator=(const Map&) = default;
  Map& operator=(Map&&) = default;

  V& operator[](const K& key) {
    std::size_t insertIdx = lowerBound(key);
    
    if (insertIdx < dataStore.size() && keysEqual(dataStore[insertIdx].first, key)) {
      return dataStore[insertIdx].second;
    }

    dataStore.insert(dataStore.begin() + insertIdx, std::pair<K, V>(key, V{}));
    return dataStore[insertIdx].second;
  }

  V operator()(const K& key) const {
    std::size_t insertIdx = lowerBound(key);
    
    if (insertIdx < dataStore.size() && keysEqual(dataStore[insertIdx].first, key)) {
      return dataStore[insertIdx].second;
    }

    return V{}; 
  }


  class Iterator {
  private:
    const Map* parentMap;
    std::size_t iterPos;

  public:
    Iterator(const Map* map, std::size_t index) : parentMap(map), iterPos(index) {}

    const K& operator*() const {
      return parentMap->dataStore[iterPos].first;
    }

    Iterator& operator++() {
      iterPos++;
      return *this;
    }

    bool operator!=(const Iterator& other) const {
      return parentMap != other.parentMap || iterPos != other.iterPos;
    }
  };

  Iterator begin() const {
    return Iterator(this, 0);
  }

  Iterator end() const {
    return Iterator(this, dataStore.size());
  }
};

#endif