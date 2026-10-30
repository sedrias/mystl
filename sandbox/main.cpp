#include <cstddef>
#include <functional>
#include <iostream>

namespace my {
template <typename K, typename V> class hash_map {
  private:
    struct Node {
        K key_{};
        V value_{};
        Node* next_{};
    };
    std::size_t size_{};
    std::size_t bucket_count_{};
    Node** buckets_{};

    std::size_t bucket_index(const K& key) const { return std::hash<K>{}(key) % bucket_count_; }

  public:
    hash_map() {
        bucket_count_ = 8;
        buckets_ = new Node* [bucket_count_] {};
    }
    ~hash_map() {
        for (std::size_t i{0}; i < bucket_count_; ++i) {
            Node* cur = buckets_[i];
            while (cur != nullptr) {
                Node* tmp = cur->next_;
                delete cur;
                cur = tmp;
            }
        }
        delete[] buckets_;
    }
    void insert(const K& key, const V& value) {
        V* p{find(key)};
        if (p != nullptr) {
            *p = value;
            return;
        }
        std::size_t index = bucket_index(key);
        Node* node = new Node{key, value, nullptr};
        node->next_ = buckets_[index];
        buckets_[index] = node;
        ++size_;
    }
    V* find(const K& key) {
        std::size_t index = bucket_index(key);
        Node* cur = buckets_[index];
        while (cur != nullptr) {
            if (cur->key_ == key) {
                return &cur->value_;
            }
            cur = cur->next_;
        }
        return nullptr;
    }
};
} // namespace my

int main() {
    my::hash_map<int, int> m;
    m.insert(1, 10);
    m.insert(2, 20);
    m.insert(3, 30);
    std::cout << *m.find(2) << ' ';
    m.insert(2, 99);
    std::cout << *m.find(2) << ' ';
    return 0;
}
