#include <cstddef>

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

  public:
    hash_map() {
        bucket_count_ = 8;
        buckets_ = new Node* [bucket_count_] {};
    }
    ~hash_map() { delete[] buckets_; }
};
} // namespace my

int main() {
    my::hash_map<int, int> m;
    return 0;
}
