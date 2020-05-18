
/**
 * \defgroup utility Utility
 * \brief Various utility classes and methods
 * 
 */

/**
 * \ingroup utility
 * @brief The definition and implementation of the BufferPool class
 * 
 * The BufferPool provides a low-overhead pool of pre-allocated buffers
 * that may be used in a 'single-producer, multiple-consumer' model. 
 * 
 * @file BufferPool.hpp
 * @author Christopher Sund
 * @date 2018-03-23
 */

#ifndef _BUFFER_POOL_H
#define _BUFFER_POOL_H

#include <cstddef>
#include <list>
#include <stdexcept>
#include "prim.h"

/**
 * \ingroup utility
 * @brief A templated buffer pool manager
 * 
 * BufferPool provides a templated class for management of an arbitrary
 * number of buffers of a particular type of identical size. This allows for
 * a simplified use of "dynamic" allocation without actually involving any
 * on the fly allocation. This is accomplished through allocating a backing
 * buffer that is large enough for all preconfigured demand and issuing 
 * \ref PoolElement instances to wrap sections of that backing buffer. Simple
 * reference tracking is also managed internally so that an allocating call
 * may specify how many times a specific buffer should be "free'd" before it 
 * actually becomes available again in the pool. This allows for a 'single 
 * producer, multiple consumer' model that is free from worries about data
 * races or dynamic allocation overhead.
 * 
 * @tparam T the storage type of the managed buffers
 */
template<typename T>
class BufferPool
{
public:
  /**
   * @brief The read-only base class that wraps issued buffers
   * 
   * This class acts as the read-only interface and base class to buffers that
   * have been acquired. The buffer is contained internally as a pointer and 
   * is accessable only through const functions. An internal reference count
   * is also traced so users that release control of the buffer will eventually
   * return the element to the pool once all other users have released it.
   */
  class PoolElement
  {
  public:
    /**
     * @brief the index operation is forwarded to the internal buffer
     * 
     * This function provides the user with an array style, but read-only
     * interface into the internal buffer of this element.
     * 
     * @param idx the index of the element desired
     * @return const T& a reference to the contained element
     */
    const T& operator[] (int idx) const
    {
      return buffer[idx];
    }

    /**
     * @brief copies from the internal buffer into the given buffer
     * 
     * This function provides an interface to copy the content of the internal
     * buffer into another buffer. Using this operation for more than one 
     * element will be faster than copying each element using the operator[]
     * accessor.
     * 
     * @param other_buffer the buffer to copy into
     * @param copy_count the number of elements to copy; n.b. NOT the number 
     * of bytes
     */
    void copy_to(T* other_buffer, size_t copy_count) const
    {
      memcpy(other_buffer, buffer, sizeof(T)*copy_count);
    }

    /**
     * @brief Releases ownership of this pool element
     * 
     * When a pool element is released, the internal reference count is 
     * decremented by one. If this internal count has reached zero, the
     * PoolElement is returned to the pool and the data within becomes
     * invalid.
     * 
     */
    virtual void release()
    {
      reference_count--;
      if(reference_count == 0)
      {
        pool->release(this);
      }
    }
  protected:
    /// protected to avoid instantiation outside WritablePoolElement
    PoolElement() {}
    /// an internal reference count that must be specified on write
    size_t reference_count;
    /// the buffer that this element wraps
    T* buffer;
    // a reference to the pool that this element must be returned to
    BufferPool<T>* pool;
  };

  /**
   * @brief A writable interface to a PoolElement
   * 
   * This class provides the writable variant of a PoolElement. The content
   * of the buffer may be modified via the array style accessor and the
   * reference count may be set.
   * 
   */
  class WritablePoolElement : public PoolElement
  {
  public:
    /**
     * @brief Construct a new Writable Pool Element object
     * 
     */
    WritablePoolElement() {}

    /**
     * @brief array-style accessor forwards to the internal buffer
     * 
     * @param idx the index to access within the buffer
     * @return T& a modifiable reference to the stored value
     */
    T& operator[] (int idx)
    {
      return this->buffer[idx];
    }

    /**
     * @brief Set the reference count of this element
     * 
     * @param new_count the new count to set to
     */
    void set_reference_count(size_t new_count)
    {
      this->reference_count = new_count;
    }
  };

private:
  /**
   * @brief The internal interface to PoolElements 
   * 
   * This class provides one additional method for internal use within a 
   * BufferPool, the ability to set the buffer and pool references.
   * 
   */
  class ConfigurablePoolElement : public WritablePoolElement
  {
  public:
    void set_content(T* buffer, BufferPool<T>* pool)
    {
      this->buffer = buffer;
      this->pool = pool;
    }
  };

public:
  /**
   * @brief Construct a new Buffer Pool object
   * 
   * Initializes the internal sychronization mutex and throws a runtime_error
   * on failure.
   * 
   */
  BufferPool()
  {
    pool_mutex = 0;
    // search for free mutex
    if(hwrtos_prim_get_mtx(&pool_mutex))
    {
      throw std::runtime_error("Unable to initialize BufferPool mutex");
    }
  }

  /**
   * @brief allocates the internal backing buffer that will hold data
   * 
   * Initializes this BufferPool by allocating space for the given number
   * of buffers of the given size. 
   * 
   * @param buffer_size the size of each buffer as the number of T's it can 
   * contain
   * @param buffer_count the number of buffers of size buffer_size to support
   */
  void allocate(std::size_t buffer_size, std::size_t buffer_count)
  {
    //using configuous memory here for access efficiency by users
    backing_buffer = new T[buffer_size * buffer_count];
    if(backing_buffer == NULL)
    {
      throw std::runtime_error("Failed to allocate backing_buffer in BufferPool::allocate");
    }
    element_buffer = new ConfigurablePoolElement[buffer_count];
    if(element_buffer == NULL)
    {
      throw std::runtime_error("Failed to allocate element_buffer in BufferPool::allocate");
    }
    T* single_buffer = backing_buffer;
    for(size_t i = 0; i < buffer_count; i++)
    {
      element_buffer[i].set_content(single_buffer, this);
      buffer_pool.push_back(&element_buffer[i]);
      single_buffer += buffer_size;
    }
  }

  /**
   * @brief provides a usable element if any are available.
   * 
   * This operation is thread-safe.
   * 
   * @param reference_count the number of times this element can be released
   * before it is returned to the pool; 1 by default
   * @return WritablePoolElement* the issued pool element, or NULL if none are 
   * available or an error occurred
   */
  WritablePoolElement* acquire(size_t reference_count = 1)
  {
    if(buffer_pool.empty())
    {
      return NULL;
    }
    if(loc_mtx(pool_mutex))
    {
      return NULL;
    }
    WritablePoolElement* ret = buffer_pool.back();
    buffer_pool.pop_back();
    if(unl_mtx(pool_mutex))
    {
      throw std::runtime_error(
        "Encountered error while releasing mutex in BufferPool::acquire()");
    }
    ret->set_reference_count(reference_count);
    return ret;
  }

private:
  /**
   * @brief returns the given pool element to this pool
   * 
   * A released element becomes eligable to be issued in a subsequent acquire()
   * call. This operation is thread-safe.
   * 
   * @param to_release the pool element to release
   */
  void release(PoolElement* to_release)
  {
    if(loc_mtx(pool_mutex))
    {
      throw std::runtime_error(
        "Encountered error while acquiring mutex in BufferPool::release()");
    }
    buffer_pool.push_back(dynamic_cast<ConfigurablePoolElement*>(to_release));
    if(unl_mtx(pool_mutex))
    {
      throw std::runtime_error(
        "Encountered error while releasing mutex in BufferPool::release()");
    }
  }

  /// the internal list of pool elements
  std::list<ConfigurablePoolElement*> buffer_pool;
  /// the internal reference to the allocated backing buffer
  T* backing_buffer;
  /// the internal reference to the element buffer
  ConfigurablePoolElement* element_buffer;
  /// the internal synchronization mutex
  ID pool_mutex;
};

#endif
