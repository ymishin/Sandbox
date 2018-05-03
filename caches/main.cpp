#include <iostream>
#include <string>
#include "lfu_cache.hpp"

// ----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
  LFUCache<int, std::string> cache(3);
  std::string elem1 = "element 1";
  std::string elem2 = "element 2";
  std::string elem3 = "element 3";
  std::string elem4 = "element 4";
  std::string error = "Error !!!";
  std::string str;
  
  cache.insert(1, elem1, false);
  cache.insert(2, elem2, false);
  cache.insert(3, elem3, false);
  if (!cache.get(1, &str) || str != elem1) std::cout << error << std::endl;
  if (!cache.get(2, &str) || str != elem2) std::cout << error << std::endl;
  if (!cache.get(3, &str) || str != elem3) std::cout << error << std::endl;

  cache.insert(4, elem4, false);
  if (cache.get(1, &str)) std::cout << error << std::endl;
  if (!cache.get(2, &str) || str != elem2) std::cout << error << std::endl;
  if (!cache.get(3, &str) || str != elem3) std::cout << error << std::endl;
  if (!cache.get(4, &str) || str != elem4) std::cout << error << std::endl;  

  cache.insert(1, elem1, false);
  if (!cache.get(1, &str) || str != elem1) std::cout << error << std::endl;
  if (!cache.get(2, &str) || str != elem2) std::cout << error << std::endl;
  if (!cache.get(3, &str) || str != elem3) std::cout << error << std::endl;
  if (cache.get(4, &str)) std::cout << error << std::endl;

  auto elem1_ = elem1 + "_";
  cache.insert(1, elem1_, false);
  if (!cache.get(1, &str) || str != elem1) std::cout << error << std::endl;
  cache.insert(1, elem1_, true);
  if (!cache.get(1, &str) || str != elem1_) std::cout << error << std::endl;
}
