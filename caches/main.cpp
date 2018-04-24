#include <iostream>
#include <string>
#include "lfu_cache.hpp"

int main()
{
  LFUCache<int, std::string> cache(4);
  std::string str;

  cache.insert(1, "element 1", true);
  cache.insert(2, "element 2", true);
  cache.insert(3, "element 3", true);
  cache.insert(4, "element 4", true);
  if (cache.get(1, &str)) std::cout << str << std::endl;
  if (cache.get(1, &str)) std::cout << str << std::endl;
  if (cache.get(1, &str)) std::cout << str << std::endl;
  if (cache.get(2, &str)) std::cout << str << std::endl;
  if (cache.get(2, &str)) std::cout << str << std::endl;

  std::cout << std::endl;

  cache.insert(5, "element 5", true);
  if (cache.get(1, &str)) std::cout << str << std::endl;
  if (cache.get(2, &str)) std::cout << str << std::endl;
  if (cache.get(3, &str)) std::cout << str << std::endl;
  if (cache.get(4, &str)) std::cout << str << std::endl;
  if (cache.get(5, &str)) std::cout << str << std::endl;
}
