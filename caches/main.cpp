#include <iostream>
#include <string>
#include "lfu_cache.hpp"

int main()
{
  LFUCache<int, std::string> cache(3);
  std::string elem1 = "element 1";
  std::string elem2 = "element 2";
  std::string elem3 = "element 3";
  std::string elem4 = "element 4";
  std::string error = "Error !!!";
  std::string str;
  
  cache.insert(1, elem1, true);
  cache.insert(2, elem2, true);
  cache.insert(3, elem3, true);
  if (!cache.get(1, &str) || str != elem1) std::cout << error << std::endl;
  if (!cache.get(2, &str) || str != elem2) std::cout << error << std::endl;
  if (!cache.get(3, &str) || str != elem3) std::cout << error << std::endl;

  cache.insert(4, elem4, true);
  if (cache.get(1, &str)) std::cout << error << std::endl;
  if (!cache.get(2, &str) || str != elem2) std::cout << error << std::endl;
  if (!cache.get(3, &str) || str != elem3) std::cout << error << std::endl;
  if (!cache.get(4, &str) || str != elem4) std::cout << error << std::endl;  

  cache.insert(1, elem1, true);
  if (!cache.get(1, &str) || str != elem1) std::cout << error << std::endl;
  if (!cache.get(2, &str) || str != elem2) std::cout << error << std::endl;
  if (!cache.get(3, &str) || str != elem3) std::cout << error << std::endl;
  if (cache.get(4, &str)) std::cout << error << std::endl;
}
