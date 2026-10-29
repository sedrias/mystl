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
};
} // namespace my
