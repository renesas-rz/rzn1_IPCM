
/**
 * \defgroup task_system ASB Task System
 * \brief Generic task system for application tasks
 * 
 * The ASBRTTask class serves as a base for a generified task management and
 * inter-task communication system. A "task" under this system should be a
 * fully specialized implementation of the ASBRTTask base and optionally 
 * inherit a number of specializations of ASBRTReceiver and ASBRTProducer.
 * Such instances can then be initialzed, started and interconnected in a
 * uniform way. The key classes for an implementer include:
 *   - ASBRTTask: base task class
 *   - ASBRTReceiver: abstract base class for other receiver types
 *   - ASBRTQueuedReceiver: reciever that uses a backing queue
 *   - ASBRTEventReceiver: receiver that uses an event for synchronization
 *   - ASBRTProducer: base class for tasks that produce a given type
 * 
 * All of these types are templated for specialzation with the implementer's 
 * needed type. For tasks this allows for uniform initialization and easily 
 * implementation of task management. For inter-task communication, classes 
 * that inherit one of the Producer or Receiver types specialized for the 
 * same data type may be easily connected with \ref TASK_CONNECT(). A simple 
 * example may be seen below:
 * 
 * \code
 * #include "ASBRTTask.hpp"
 *
 * class ConcreteTask1 :
 *    public ASBRTTask<void*, ConcreteTask1>,
 *    public ASBRTProducer<float>
 *  {
 *  private:
 *    static void task1_func(ConcreteTask1* instance);
 *
 *  public:
 *    ConcreteTask1() :
 *      ASBRTTask<void*, ConcreteTask1>(ASBRTTaskConfig("Task 1"),
 *                                      ConcreteTask1::task1_func)
 *    {
 *    }
 * };
 *
 *
 * class ConcreteTask2 :
 *    public ASBRTTask<void*, ConcreteTask2>,
 *    public ASBRTQueuedReceiver<float>
 *  {
 *  private:
 *    static void task2_func(ConcreteTask2* instance);
 *    int init_data;
 *  public:
 *    ConcreteTask2(int init) :
 *      ASBRTTask<void*, ConcreteTask2>(ASBRTTaskConfig("Task 2"),
 *                                      ConcreteTask2::task2_func),
 *      ASBRTQueuedReceiver<float>("receiver_queue", 10),
 *      init_data(init)
 *    {
 *    }
 *
 * };
 *
 *
 * void ConcreteTask1::task1_func(ConcreteTask1* instance)
 * {
 *
 *   float var = 1.0;
 *
 *   while(instance->task_running)
 *   {
 *     instance->produce(var);
 *     rt_task_sleep(100000000LL);
 *   }
 * }
 *
 * void ConcreteTask2::task2_func(ConcreteTask2* instance)
 * {
 *
 *   while(instance->task_running)
 *   {
 *
 *      float data;
 *      instance->retrieve(data);
 *   }
 *
 * }
 *
 *
 * int main(int argc, char** argv)
 * {
 *   ConcreteTask1 t1;
 *   ConcreteTask2 t2(100);
 *   TASK_CONNECT(&t1, &t2, float);
 *   t1.init_task();
 *   t2.init_task();
 *   t1.start_task();
 *   t2.start_task();
 *
 *   while(1)
 *   {
 *     rt_task_sleep(100000000LL);
 *   }
 * }
 * \endcode
 */

/**
 * \defgroup task_instance ASB Task Instances
 * \brief Tasks that make up the runtime of the ASB application
 * 
 * Documentation of ASB task layout can go here?
 * 
 */

/**
 * \ingroup task_system
 * @brief A generic task base class and inter-task communcation
 * base classes.
 * 
 * @file ASBRTTask.hpp
 * @author Christopher Sund
 * @date 2018-03-22
 */

#ifndef _ASB_RT_TASK_H
#define _ASB_RT_TASK_H

#include "kernel.h"
#include "BufferPool.hpp"
#include "prim.h"
#include <list>
#include <stdexcept>
#include "eth/eth_hwfnc.h"
#include "serial_log.h"

/// stack size of created tasks
#define DEFAULT_STACK_SIZE  0x2000
/// default task priority
#define DEFAULT_TASK_PRIO   10


/**
 * @brief Registers \e receiver to receive all output of type \e Type produced 
 * by \e producer.
 * 
 */
#define TASK_CONNECT(producer, receiver, Type) do {\
    (producer)->ASBRTProducer<Type>::register_receiver( \
      dynamic_cast< ASBRTReceiver<Type>* >(receiver)); \
    } while(0)

/// amount of time to sleep when printing an error message
#define TASK_OUTPUT(...) do {log_printf((char *)__VA_ARGS__);} while(0)
#define TASK_ERROR(...) do {log_printf((char *)__VA_ARGS__);} while(0)


typedef struct
{
  unsigned char ptrData[100];
} ITC_MSG;

/**
 * @brief A configuratin struct for ASBRTTasks; passes the given parameters on
 * to task creation.
 */
struct ASBRTTaskConfig
{
  /**
   * @brief Construct a new ASBRTTaskConfig object
   * 
   */
  ASBRTTaskConfig() : 
    task_name(NULL), 
    stack_size(DEFAULT_STACK_SIZE),
    task_priority(DEFAULT_TASK_PRIO)
  {

  }

  /**
   * @brief Construct a new ASBRTTaskConfig object
   * 
   * @param task_name the name to use
   */
  ASBRTTaskConfig(const char* task_name) : 
    task_name(task_name), 
    stack_size(DEFAULT_STACK_SIZE),
    task_priority(DEFAULT_TASK_PRIO)
  {
    this->task_name = task_name;
  }

  /// the name of the task to create
  const char* task_name;
  /// the stack size in bytes to allocate for this task
  int stack_size;
  /// the priority to assign this task
  int task_priority;
};

/**
 * \ingroup task_system
 * @brief A templated abstract base class that serves as an interface for 
 * the receive side of inter-task communication.
 * 
 * @tparam InDataType the data-type fully specialized subclasses of this type
 * are capable of receiving.
 */
template<typename InDataType>
class ASBRTReceiver
{
public:
  /**
   * @brief Pushes a message to this receiver to be later retrieved.
   * 
   * @param message the message to receive that may be later retrieved
   * @return int 0 on success, an error code on failure
   */
  virtual int receive(InDataType& message) = 0;
  
protected:
  /**
   * @brief Retrieves a previously received message with implementation 
   * defined semantics. 
   * 
   * This function may block if desired.
   * 
   * @param message a reference to a message to output on
   * @return int 0 on success, an error code on failure
   */
  virtual int retrieve(InDataType& message) = 0;

  /**
   * @brief Attempts to retreive a previously received message with
   * implementation defined semantics. 
   * 
   * This is meant to be the non-blocking counterpart to retreive.
   * 
   * @param message a reference to a message to output on
   * @return int 0 on success, an error code on failure
   */
  virtual int try_retrieve(InDataType& message) = 0;
};

/**
 * @brief A utility class that stores a single RT_Event and manages it.
 * 
 * This class is meant to be virtually inherited so that inheritance of
 * such a subclass will only generate once instance of RTEventSharer.
 * 
 */
class RTEventSharer
{
protected:
  /**
   * @brief Construct a new RTEventSharer object
   * 
   */
  RTEventSharer()
  {
    ER rc;
    
    shared_event = 0;
    if(hwrtos_prim_get_flg(&shared_event))
    {
      TASK_ERROR("Unable to create shared event: %d\r\n", rc);
      throw std::runtime_error("Unable to create shared event");
    }
  }

  /**
   * @brief Waits of the internal event to be signalled on any bit mask.
   * 
   * @param out_mask the resulting mask that has the signalled bits set to 1
   * @return int 0 on success, an error code on failure.
   */
  int wait_for_message(unsigned long& out_mask)
  {
    // waits for any of the events to be set
    return (int)wai_flg(shared_event, (FLGPTN)all_events, TWF_ORW, (FLGPTN*)&out_mask);
  }

  /// the shared event
  ID shared_event;
private:
  /// a word containing all 1's
  static const unsigned long all_events = 0xFFFF; // 
};

/**
 * \ingroup task_system
 * @brief An implementation of ASBRTReceiver based on Xenomai events.
 * 
 * This implementation of ASBRTReceiver is a virtual subclass of RTEventSharer,
 * so all inheriting subclasses will contain only one instance of RTEventSharer
 * and by extension only one shared_event. A class that specialzes this 
 * templated type for multiple InDataType's can then use that event as a 
 * notification of the availability of a message of any of those types. This
 * implementation is more "light weight" than ASBRTQueuedReceiver, but it does 
 * not provide any buffering of messages and currently does not prevent data
 * races between producer and receiver. InDataType must have a default
 * constructor and a copy constuctor.
 * 
 * @tparam InDataType The data type a fully specialzed subclass is capable of
 * receiving.
 */
template<typename InDataType>
class ASBRTEventReceiver : 
  public ASBRTReceiver<InDataType>,
  public virtual RTEventSharer
{
public:
  /**
   * @brief receive an InDataType message and notify on the shared_event.
   * 
   * This function receives an InDataType message by copying its content to the
   * internal buffer. It then signals on the relevant event mask bit that a 
   * message has arrived. This message should be retrieved before another
   * subsequent call to receive, or the message may be lost/ a data race may 
   * occur.
   * 
   * @param message the message to receive
   * @return int 0 on success, an error code on failure
   */
  int receive(InDataType& message)
  {
    int rc;
    unsigned long mask_out = 0;
    if(reject_overwrite && (mask_out & event_mask))
    {
      TASK_ERROR("mask_out & event_mask: %u\n", mask_out & event_mask);
      return 1;
    }
    signal_buffer = message;
    if((rc = set_flg(shared_event, (FLGPTN)event_mask)) < 0)
    {
      TASK_ERROR("got signal error on event: %p\n", (void*)&shared_event);
      return rc;
    }
    return 0;
  }

protected:
  /**
   * @brief Construct a new ASBRTEventReceiver object
   * 
   * Signal mask must be unique among a given concrete class's specializaitons 
   * of ASBRTEventReceiver and have only a single bit be 1, e.g.
   * 
   * \code
   * class ExampleReceiver: 
   *   public ASBRTEventReceiver<int>,
   *   public ASBRTEventReceiver<float>
   * {
   * public:
   *   ExampleReceiver() : 
   *     ASBRTEventReceiver<int>(0x1)
   *     ASBRTEventReceiver<float>(0x2)
   *   {
   *     ...
   *   }
   *   ...
   * };
   * \endcode
   * 
   * @param signal_mask the bitmask that corresponds to the datatype of this
   * ASBRTEventReceiver specialization.
   * @param reject_overwrite curently unimplemented; no effect
   */
  ASBRTEventReceiver(unsigned long signal_mask,
                     bool reject_overwrite = true) : 
    event_mask(signal_mask),
    reject_overwrite(reject_overwrite)
  {
    // TODO: possibly add checking that only one bit is set to 1 in event_mask
  }

  /**
   * @brief Retrieves a previously recieved message.
   * 
   * This function may block if no message is available. Any available message
   * will be copies to the given InDataType reference and the event mask will
   * be cleared.
   * 
   * @param message the message reference to copy into
   * @return int int 0 on success, an error code on failure
   */
  virtual int retrieve(InDataType& message)
  {
    ER rc;
    // have to have an out mask, cannot use NULL;
    FLGPTN out_mask = 0;
    if((rc = wai_flg(shared_event, event_mask, TWF_ANDW, &out_mask)))
    {
      return rc;
    }
    message = signal_buffer;
    clr_flg(shared_event, ~event_mask);
    return 0;
  }

  /**
   * @brief Attempts to retreive a previously received message if available.
   * 
   * This function is the non-blocking counterpart to retrieve. If no message
   * is available, E_TMOUT will be returned.
   * 
   * @param message the message reference to copy into
   * @return int 0 on success, E_TMOUT if no message is present, a 
   * different error code on failure.
   */
  virtual int try_retrieve(InDataType& message)
  {
    ER rc;
    FLGPTN out_mask = 0;
    if((rc = pol_flg(shared_event, event_mask, TWF_ANDW, &out_mask)))
    {
      return rc;
    }
    message = signal_buffer;
    clr_flg(shared_event, ~event_mask);
    return 0;
  }

private:
  /// declared private to prevent use
  ASBRTEventReceiver();
  /// the event mask for this instantiation 
  FLGPTN event_mask;
  /// a flag determining if overwrites should be allowed; currently unused
  bool reject_overwrite;
  /// a single instance of InDataType to act as a buffer for messages
  InDataType signal_buffer;
};

/**
 * \ingroup task_system
 * @brief An implementation of ASBRTReceiver based on Xenomai Queues.
 * 
 * This implementation of ASBRTReceiver contains an internal RT_QUEUE that
 * buffers received messages. The queue is currently FIFO only. 
 * 
 * @tparam InDataType The data type a fully specialzed subclass is capable of
 * receiving.
 */
template<typename InDataType>
class ASBRTQueuedReceiver : public ASBRTReceiver<InDataType>
{
public:
  /**
   * @brief receive an InDataType message and push it into the queue. If the 
   * received message would exceed the queue capacity, an error is returned.
   * 
   * 
   * @param message the message to enqueue
   * @return int 0 on success, an error code on failure
   */
  int receive(InDataType& message)
  {
   ITC_MSG *pBuffer;


    pBuffer = (ITC_MSG *)hwfnc_longbuffer_get(sizeof(InDataType));

    if(pBuffer == NULL)
    {
      return -1;
    }
    memcpy(pBuffer->ptrData, (void*)&message, sizeof(InDataType));
    return snd_mbx(internal_mailbox, (T_MSG*)pBuffer);
  }

protected:
  /**
   * @brief Construct a new ASBRTQueuedReceiver object
   * 
   * @param queue_name the name to provide the internal queue
   * @param max_queue_length the maximum buffered message count the queue
   * should allow.
   */
  ASBRTQueuedReceiver(const char* queue_name, size_t max_queue_length)
  {
    pool_size = max_queue_length * sizeof(InDataType);
    //check return value
    
    internal_mailbox = 0;
    if(hwrtos_prim_get_mbx(&internal_mailbox))
    {
      throw std::runtime_error("unable to allocate mailbox for queued receiver");
    }
  }

  /**
   * @brief retrieve a message from the message queue
   * 
   * Blocks if no message is yet available.
   * 
   * @param message a reference to output the message on
   * @return int 0 on success, an error code on failure
   */
  virtual int retrieve(InDataType& message)
  {
    int rc;
    ITC_MSG* pBuffer;
    if((rc = rcv_mbx(internal_mailbox, (T_MSG**)&pBuffer)))
    {
      return rc;
    }
    memcpy((void*)&message, pBuffer->ptrData, sizeof(InDataType));

    rc = hwfnc_buffer_free((unsigned int)pBuffer);

    if (rc != 0)
    {
      TASK_ERROR("HW buf free error #1: %x", rc);
      return rc;
    }

    return 0;
  }

  /**
   * @brief attempts to retrieve a message if one is available
   * 
   * If no message is available, E_TMOUT is returned.
   * 
   * @param message 
   * @return int 0 on success, E_TMOUT if no message, another error code on failure
   */
  virtual int try_retrieve(InDataType& message)
  {
    int rc;
    ITC_MSG *pBuffer;
    if((rc = prcv_mbx(internal_mailbox, (T_MSG**)&pBuffer)))
    {
      return rc;
    }
    memcpy((void*)&message, pBuffer->ptrData, sizeof(InDataType));
    rc = hwfnc_buffer_free((unsigned int)pBuffer);

    if (rc != 0)
    {
      TASK_ERROR("HW buf free error #2: %x", rc);
      return rc;
    }

    return 0;
  }
  
private:
  /// declared private to prevent use
  ASBRTQueuedReceiver();
  /// the size of the queue backing buffer in bytes
  size_t pool_size;
  // mailbox used for storing pointers to allocated buffers
  ID internal_mailbox;
  BufferPool<InDataType>* queue_buffer_pool;
};

/**
 * \ingroup task_system
 * @brief A base class that indicates the inheriting subclass will generate
 * messages of OutDataType.
 * 
 * This base class functions as the producer side of the inter-task 
 * communication system, operating in conjunction with ASBRTReceiver instances.
 * Such instances may be "registered" with register_receiver() such that 
 * messages produced with produce() will subsequencly pass to all registered
 * receivers' ASBRTReceiver::receive() functions.
 * 
 * @tparam OutDataType 
 */
template<typename OutDataType>
class ASBRTProducer
{
public:
  /**
   * @brief registers the given receiver under this producer
   * 
   * A registered receiver will have its ASBRTReceiver::receive() function
   * called with each subsequent call to produce() on this instance.
   * 
   * @param receiver the receiver instance to register
   */
  void register_receiver(ASBRTReceiver<OutDataType>* receiver)
  {
    receiver_list.push_back(receiver);
  }

protected:
  /// declared protected to prevent direct instantiation
  ASBRTProducer() 
  {

  }

  /**
   * @brief broadcasts the given message to all registered receivers
   * 
   * @param message the message to produce
   * @return int 0 on success, an error code if any of the registered receivers
   * returned a non-zero value for receive (fails fast)
   */
  int produce(OutDataType& message) 
  {
    int err;
    typename std::list< ASBRTReceiver<OutDataType>* >::iterator receiver = receiver_list.begin();
    ASBRTReceiver<OutDataType>* current_receiver = NULL;
    for(; receiver != receiver_list.end(); ++receiver)
    {
      current_receiver = *receiver;
      if((err = current_receiver->receive(message)) != 0)
      {
        return err;
      }
    }
    return 0;
  }

  /**
   * @brief gets the number of registered receivers for this instance
   * 
   * @return size_t the number of registered receivers
   */
  size_t receiver_count()
  {
    return receiver_list.size();
  }
private:
  /// the internal list or registered receivers to produce to
  std::list< ASBRTReceiver<OutDataType>* > receiver_list;
};

/**
 * \ingroup task_system
 * @brief A base class intended for subclassing that presents a generalized
 * interface for managing tasks.
 * 
 * @tparam InitDataType the type passed to init_task by default.
 * @tparam StartDataType the type passed to start_task and the type of which
 * a pointer is passed to the given task_function
 */
template<typename InitDataType, typename StartDataType>
class ASBRTTask
{
public:
  /// A convenience typedef of the function pointer type this task will run
  typedef void (*Callback)(StartDataType*);

  /**
   * @brief Construct a new ASBRTTask object
   * 
   * @param config the task configuration to pass onto task creation
   * @param task_function the function that will serve as the task's
   * callback
   */
  ASBRTTask(ASBRTTaskConfig config, Callback task_function) : 
    config(config),task_function(task_function)
  {

  }

  /**
   * @brief default implementation of task initialization
   * 
   * Creates the underlying task instance
   * 
   * @param init_data initialization data (currently unus)
   * @return int 0 on success, an error code on failure
   */
  virtual int init_task(InitDataType& init_data)
  {
    (void)init_data;
    return 0;
  }

  /**
   * @brief default implementation of task initialization
   * 
   * Creates the underlying task instance
   * 
   * @return int 0 on success, an error code on failure
   */
  virtual int init_task()
  {
    return 0;
  }

  /**
   * @brief starts the intenral task with the given start data
   * 
   * @param start_data the data to pass to the task_function
   * @return int 0 on success, an error code otherwise
   */
  virtual int start_task(const char *name, StartDataType& start_data)
  {
    return start_task_internal(name, &start_data);
  }

  /**
   * @brief starts the intenral task using a pointer to this instance as 
   * the start data.
   * 
   * The this pointer of this instance will be cast to a StartDataType* and
   * passed to the task_function.
   * 
   * @return int 0 on success, an error code otherwise
   */
  virtual int start_task(const char *name)
  {
    return start_task_internal(name, dynamic_cast<StartDataType*>(this));
  }

protected:
  /**
   * @brief starts the internal xenomai task with the given data.
   * 
   * @param start_data the start data pointer to pass to the task_function
   * @param replacement_function an optional replacement function that will
   * be used in place of the previously provided task_function
   * @return int 
   */
  virtual int start_task_internal(const char *name, StartDataType* start_data, Callback replacement_function = NULL)
  {
    int err;
    Callback callback = task_function;
    if(replacement_function)
    {
      callback = task_function;
    }
    err = hwrtos_prim_get_task(name, &internal_task,
                               (VoidIntCallback)callback,
                               NULL,
                               0,
                               config.task_priority,
                               config.stack_size);
    if(err)
    {
      return err;
    }
    if((err = sta_tsk(internal_task, (VP)((void*)start_data))))
    {
      return err;
    }
    return 0;
  }

public:
  /// the task configuration for this instance
  ASBRTTaskConfig config;

private:
  /// the intenral Xenomai task this instnace manages
  ID internal_task;
  /// the function pointer the intenal task runs
  Callback task_function;
  // a convenience typedef for use in internal_task_start
  typedef void (*VoidIntCallback)(int);
};

#endif
