#include "primer/trie.h"
#include <string_view>
#include "common/exception.h"

namespace bustub {

template <class T>
auto Trie::Get(std::string_view key) const -> const T * {
  throw NotImplementedException("Trie::Get is not implemented.");

  // You should walk through the trie to find the node corresponding to the key. If the node doesn't exist, return
  // nullptr. After you find the node, you should use `dynamic_cast` to cast it to `const TrieNodeWithValue<T> *`. If
  // dynamic_cast returns `nullptr`, it means the type of the value is mismatched, and you should return nullptr.
  // Otherwise, return the value.
}

template <class T>
auto Trie::Put(std::string_view key, T value) const -> Trie {
  // Note that `T` might be a non-copyable type. Always use `std::move` when creating `shared_ptr` on that value.
  std::shared_ptr<TrieNode> new_root;
  auto value_ptr = std::make_shared<T>(std::move(value));

  if (root_ != nullptr) {
    new_root = std::make_shared<TrieNode>(root_->children_);
  } else {
    new_root = std::make_shared<TrieNode>();
  }
  
  std::shared_ptr<Trie> new_trie = std::shared_ptr<Trie>((new Trie(new_root)));

  auto cur_node = std::const_pointer_cast<TrieNode>(new_trie->root_);

  for (size_t i = 0; i < key.size(); i++) {
    auto cur_char = key[i];
    if (!cur_node->HasChild(cur_char)) { // does not have the current key char
      if (i != key.size() - 1) { // not the last key char
        // insert node
        auto new_node = std::make_shared<TrieNode>();
        cur_node->children_[cur_char] = new_node;
      } else { // is the last key char
        // insert node with value
        auto new_node = std::make_shared<TrieNodeWithValue<T>>(value_ptr);
        cur_node->children_[cur_char] = new_node;
      }
    } else { // has the current key char
      std::shared_ptr<const TrieNode> child = cur_node->children_[cur_char];
      if (i == key.size() -1) { // last key char
        // insert node with value
        auto new_node = std::make_shared<TrieNodeWithValue<T>>(child->children_, value_ptr);
        cur_node->children_[cur_char] = new_node;
      }
    }
    
    // move to next
    cur_node = std::const_pointer_cast<TrieNode>(cur_node->children_[key[i]]);
  }

  return *new_trie;
  // You should walk through the trie and create new nodes if necessary. If the node corresponding to the key already
  // exists, you should create a new `TrieNodeWithValue`.
}

auto Trie::Remove(std::string_view key) const -> Trie {
  throw NotImplementedException("Trie::Remove is not implemented.");

  // You should walk through the trie and remove nodes if necessary. If the node doesn't contain a value any more,
  // you should convert it to `TrieNode`. If a node doesn't have children any more, you should remove it.
}

// Below are explicit instantiation of template functions.
//
// Generally people would write the implementation of template classes and functions in the header file. However, we
// separate the implementation into a .cpp file to make things clearer. In order to make the compiler know the
// implementation of the template functions, we need to explicitly instantiate them here, so that they can be picked up
// by the linker.

template auto Trie::Put(std::string_view key, uint32_t value) const -> Trie;
template auto Trie::Get(std::string_view key) const -> const uint32_t *;

template auto Trie::Put(std::string_view key, uint64_t value) const -> Trie;
template auto Trie::Get(std::string_view key) const -> const uint64_t *;

template auto Trie::Put(std::string_view key, std::string value) const -> Trie;
template auto Trie::Get(std::string_view key) const -> const std::string *;

// If your solution cannot compile for non-copy tests, you can remove the below lines to get partial score.

using Integer = std::unique_ptr<uint32_t>;

template auto Trie::Put(std::string_view key, Integer value) const -> Trie;
template auto Trie::Get(std::string_view key) const -> const Integer *;

template auto Trie::Put(std::string_view key, MoveBlocked value) const -> Trie;
template auto Trie::Get(std::string_view key) const -> const MoveBlocked *;

}  // namespace bustub
