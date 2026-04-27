#ifndef MYMAP_H
#define MYMAP_H

#include <utility>
#include <vector>

template <typename K, typename V>
class Map {
public:
  Map() = default;
  ~Map() = default;
  Map(const Map&) = default;
  Map(Map&&) = default;
  Map& operator=(const Map&) = default;
  Map& operator=(Map&&) = default;

  class Iterator {
  public:
    Iterator() = default;

    const K& operator*() const {
      return currIter_->first;
    }

    Iterator& operator++() {
      ++currIter_;
      return *this;
    }

    bool operator!=(const Iterator& other) const {
      return currIter_ != other.currIter_;
    }

  private:
    using BaseIter = typename std::vector<std::pair<K, V>>::const_iterator;

    explicit Iterator(BaseIter iter) : currIter_(iter) {}

    BaseIter currIter_{};

    friend class Map;
  };

  V& operator[](const K& key) {
    using VecDiffType =
        typename std::vector<std::pair<K, V>>::difference_type;

    std::size_t idx = findLocation(key);
    if (idx < vecData_.size() && !(key < vecData_[idx].first) &&
        !(vecData_[idx].first < key)) {
      return vecData_[idx].second;
    }

    vecData_.insert(vecData_.begin() + static_cast<VecDiffType>(idx),
                    std::pair<K, V>(key, V{}));
    return vecData_[idx].second;
  }

  V operator()(const K& key) const {
    std::size_t idx = findLocation(key);
    if (idx < vecData_.size() && !(key < vecData_[idx].first) &&
        !(vecData_[idx].first < key)) {
      return vecData_[idx].second;
    }

    return V{};
  }

  Iterator begin() const {
    return Iterator(vecData_.begin());
  }

  Iterator end() const {
    return Iterator(vecData_.end());
  }

private:
  std::size_t findLocation(const K& key) const {
    std::size_t low = 0;
    std::size_t high = vecData_.size();

    while (low < high) {
      std::size_t center = low + (high - low) / 2;
      if (vecData_[center].first < key) {
        low = center + 1;
      } else {
        high = center;
      }
    }

    return low;
  }

  std::vector<std::pair<K, V>> vecData_;
};

#endif
