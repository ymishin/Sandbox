#ifndef C_LFU_CACHE_HPP__
#define C_LFU_CACHE_HPP__

// ----------------------------------------------------------------------------

#include <list>
#include <unordered_map>

template<typename Key, typename E>
struct FreqNode;

template<typename Key, typename E>
struct CacheElement;

// ----------------------------------------------------------------------------

template<typename Key, typename E>
class LFUCache
{
public:
  typedef typename std::list<CacheElement<Key, E>>::iterator CacheElementIt;
  typedef typename std::list<FreqNode<Key, E>>::iterator FreqNodeIt;

  LFUCache(const int capacity)
  {
    this->size = 0;
    this->capacity = capacity;
  }

  // Get element from cache. Each call increases element usage frequence by 1.
  bool get(const Key &k, E *e)
  {
    if (key2Element.count(k) == 0)
    {
      return false;
    }
    else
    {
      CacheElementIt cacheElementIt = key2Element[k];
      FreqNodeIt freqNodeIt = cacheElementIt->freqNodeIt;
      int freq = freqNodeIt->freq + 1;
      FreqNodeIt nextFreqNodeIt = std::next(freqNodeIt, 1);
      if (nextFreqNodeIt == freqNodes.end() || (nextFreqNodeIt->freq > freq))
      {
        nextFreqNodeIt = freqNodes.insert(nextFreqNodeIt, FreqNode<Key, E>(freq));
      }
      nextFreqNodeIt->cacheElements.splice(
        nextFreqNodeIt->cacheElements.begin(),
        freqNodeIt->cacheElements, cacheElementIt);
      if (freqNodeIt->cacheElements.size() == 0)
      {
        freqNodes.erase(freqNodeIt);
      }
      cacheElementIt->freqNodeIt = nextFreqNodeIt;
      *e = cacheElementIt->e;
      return true;
    }
  }

  // Insert element into cache. Least frequently used element will be removed if maximum capacity is reached.
  void insert(const Key &k, const E &e, bool forceInsert)
  {
    // Remove LFU element from cache if maximum capacity is reached
    if (key2Element.count(k) == 0 && size == capacity)
    {
      auto &frontCacheElements = freqNodes.front().cacheElements;
      key2Element.erase(frontCacheElements.back().k);
      frontCacheElements.pop_back();
      if (frontCacheElements.size() == 0)
      {
        freqNodes.pop_front();
      }
      --size;
    }
    // Remove element with the same key if already in cache
    if (key2Element.count(k) > 0)
    {
      if (!forceInsert) return;
      CacheElementIt cacheElementIt = key2Element[k];      
      FreqNodeIt freqNodeIt = cacheElementIt->freqNodeIt;
      freqNodeIt->cacheElements.erase(cacheElementIt);
      key2Element.erase(k);
      if (freqNodeIt->cacheElements.size() == 0)
      {
        freqNodes.erase(freqNodeIt);
      }
      --size;
    }
    // Insert new element into cache
    FreqNodeIt freqNodeIt = freqNodes.begin();
    if (freqNodeIt == freqNodes.end() || (freqNodeIt->freq > 1))
    {
      freqNodeIt = freqNodes.insert(freqNodeIt, FreqNode<Key, E>(1));
    }
    freqNodeIt->cacheElements.emplace_front(CacheElement<Key, E>(k, e, freqNodeIt));
    key2Element[k] = freqNodeIt->cacheElements.begin();
    ++size;
  }

private:
  int capacity;
  int size;
  std::list<FreqNode<Key, E>> freqNodes;
  std::unordered_map<Key, CacheElementIt> key2Element;
};

// ----------------------------------------------------------------------------

template<typename Key, typename E>
struct CacheElement
{
  typedef typename std::list<FreqNode<Key, E>>::iterator FreqNodeIt;

  CacheElement(const Key &k, const E &e, FreqNodeIt freqNodeIt)
  {
    this->k = k;
    this->e = e;
    this->freqNodeIt = freqNodeIt;
  }

  Key k;
  E e;
  FreqNodeIt freqNodeIt;
};

template<typename Key, typename E>
struct FreqNode
{
  FreqNode(const int freq)
  {
    this->freq = freq;
  }

  int freq;
  std::list<CacheElement<Key, E>> cacheElements;
};

// ----------------------------------------------------------------------------

#endif // C_LFU_CACHE_HPP__