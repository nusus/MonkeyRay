#ifndef CMRContainerConfig_h__
#define CMRContainerConfig_h__

#include "CMRMemoryAllocatorConfig.h"

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <deque>
#include <forward_list>
#include <list>
#include <queue>
#include <stack>
namespace MR
{
	template <
		typename T,
		typename Alloc = STLAllocator<T>
	>
		using vector = std::vector<T, Alloc>;

	template <
		typename Key,
		typename T,
		typename Hash = hash<Key>,
		typename Pred = equal_to<Key>,
		typename Alloc = STLAllocator<pair<const Key, T> >
	>
		using unordered_map = std::unordered_map<Key, T, Hash, Pred, Alloc>;

	template <
		typename Key,
		typename T,
		typename Hash = hash<Key>,
		typename Pred = equal_to<Key>,
		typename Alloc = STLAllocator<pair<const Key, T> >
	>
		using unordered_multimap = std::unordered_multimap<Key, T, Hash, Pred, Alloc>;

	template <
		typename Key,
		typename Hash = hash<Key>,
		typename Pred = equal_to<Key>,
		typename Alloc = STLAllocator<Key>
	>
		using unordered_set = std::unordered_set<Key, hash, Pred, Alloc>;

	template <
		typename Key,
		typename Hash = hash<Key>,
		typename Pred = equal_to<Key>,
		typename Alloc = STLAllocator<Key>
	>
		using unordered_multiset = std::unordered_multiset<Key, hash, Pred, Alloc>;

	template<
		typename T,
		typename Alloc = STLAllocator<T>
	>
		using list = std::list<T, Alloc>;

	template<
		typename T,
		typename Alloc = STLAllocator<T>
	>
		using forward_list = std::forward_list<T, Alloc>;

	template<
		typename Key,
		typename T,
		typename Compare = less<Key>,
		typename Alloc = STLAllocator<pair<const key, T> >
	>
		using map = std::map<Key, T, Compare, Alloc>;

	template<
		typename Key,
		typename T,
		typename Compare = less<Key>,
		typename Alloc = STLAllocator<pair<const key, T> >
	>
		using multimap = std::multimap<Key, T, Compare, Alloc>;

	template<
		typename T,
		typename Compare = less<T>,
		typename Alloc = STLAllocator<T>
	>
		using set = std::set<T, Compare, Alloc>;

	template<
		typename T,
		typename Compare = less<T>,
		typename Alloc = STLAllocator<T>
	>
		using multiset = std::multiset<T, Compare, Alloc>;

	template<
		typename T,
		typename Container = deque<T>
	>
		using queue = std::queue<T, Container>;

	template <
		typename T,
		typename Container = vector<T>,
		typename Compare = less<typename Container::value_type>
	>
		using priority_queue = std::priority_queue<T, Container, Compare>;

	template <
		typename T,
		typename Container = deque<T>
	>
		using stack = std::stack<T, Container>;
}
#endif // CMRContainerConfig_h__
