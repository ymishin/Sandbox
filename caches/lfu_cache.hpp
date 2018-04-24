#ifndef C_LFU_CACHE_HPP__
#define C_LFU_CACHE_HPP__

#include <list>
#include <unordered_map>

template<typename Key, typename E>
class FreqNode;

template<typename Key, typename E>
class CacheElement
{
public:
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
class FreqNode
{
public:
  FreqNode(const int freq)
  {
    this->freq = freq;
  }

  int freq;
  std::list<CacheElement<Key, E>> cacheElements;
};

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
      freqNodeIt++;
      if (freqNodeIt == freqNodes.end() || (freqNodeIt->freq > freq))
      {
        freqNodeIt = freqNodes.insert(freqNodeIt, FreqNode<Key, E>(freq));
      }
      freqNodeIt->cacheElements.splice(
        freqNodeIt->cacheElements.begin(),
        cacheElementIt->freqNodeIt->cacheElements,
        cacheElementIt);
      if (cacheElementIt->freqNodeIt->cacheElements.size() == 0)
      {
        freqNodes.erase(cacheElementIt->freqNodeIt);
      }
      cacheElementIt->freqNodeIt = freqNodeIt;
      *e = cacheElementIt->e;
      return true;
    }
  }

  void insert(const Key &k, const E &e, bool resetFreq)
  {
    if (key2Element.count(k) == 0 && size == capacity)
    {
      key2Element.erase(freqNodes.front().cacheElements.back().k);
      freqNodes.front().cacheElements.pop_back();
      if (freqNodes.front().cacheElements.size() == 0)
      {
        freqNodes.pop_front();
      }
      --size;
    }
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

#endif // C_LFU_CACHE_HPP__