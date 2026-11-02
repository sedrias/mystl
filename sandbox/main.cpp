#include <cstddef>
#include <functional>

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

    void rehash(const std::size_t new_count) {
        Node** new_buckets = new Node* [new_count] {};
        for (std::size_t i{0}; i < bucket_count_; ++i) {
            Node* cur = buckets_[i];
            while (cur != nullptr) {
                Node* tmp = cur->next_;
                std::size_t new_index = std::hash<K>{}(cur->key_) % new_count;
                cur->next_ = new_buckets[new_index];
                new_buckets[new_index] = cur;
                cur = tmp;
            }
        }
        delete[] buckets_;
        buckets_ = new_buckets;
        bucket_count_ = new_count;
    }

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
        if (size_ > bucket_count_) {
            rehash(bucket_count_ * 2);
        }
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
    [[nodiscard]] std::size_t size() const { return size_; }
    [[nodiscard]] bool empty() const { return size_ == 0; }
    bool erase(const K& key) {
        std::size_t index = bucket_index(key);
        Node* cur = buckets_[index];
        Node* prev = nullptr;
        while (cur != nullptr) {
            if (cur->key_ == key) {
                break;
            }
            prev = cur;
            cur = cur->next_;
        }
        if (cur == nullptr) {
            return false;
        }
        if (prev == nullptr) {
            buckets_[index] = cur->next_;
        } else {
            prev->next_ = cur->next_;
        }
        delete cur;
        --size_;
        return true;
    }
};
} // namespace my

int main() { return 0; }
