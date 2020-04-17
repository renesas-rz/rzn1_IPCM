// SyncObject.h
//
// (c) 2010-2011 by Pivotal Systems Corp
// All rights reserved.  Company Confidential.
//
// This file defines SyncObject class that implements the mutex protection
// for accessing the data that the object contains.
//
// Created by: Abhijit Majumdar, Jiuyi Cheng
//
//   $Author: jcheng $
// $Revision: 1.1 $

#ifndef SYNC_OBJECT_H_
#define SYNC_OBJECT_H_

#include <pthread.h>
#include <stdarg.h>

template<class T> struct SyncObject {

  // data in this object
  T value;

  /**
   * Constructor
   *
   * param   arg_init_valuei
   *         Initial value for this object
   */
  SyncObject(T arg_init_value) : value (arg_init_value){

    pthread_mutexattr_t mutexAttr;
    
    pthread_mutexattr_init(&mutexAttr);
    pthread_mutexattr_setprotocol(&mutexAttr, PTHREAD_PRIO_INHERIT);

    memset( & mutex.__data, '\0', __SIZEOF_PTHREAD_MUTEX_T );    
    pthread_mutex_init(&mutex, &mutexAttr);
    
    pthread_mutexattr_destroy(&mutexAttr);
  }


  /**
   * Function to lock the mutex
   */
  void lock() {    
    pthread_mutex_lock(&mutex);
  }


  /**
   * Function to lock the mutex
   */
  void unlock() {
    pthread_mutex_unlock(&mutex);
  }


  /**
   * Function to set the value in thread-safe way
   *
   * param  arg_new value
   *        This is a const reference otherwise
   *        we will not be able to pass constants like enum
   */
  virtual void set(const T & arg_new_value) {
    lock();
    this->value = arg_new_value;
    unlock();
  }


  /**
   * Function to get the latest value in thread-safe way
   *
   * return  T
   *         Value of the synchronized object
   */
  virtual T get() {
    lock();
    T ret = this->value;
    unlock();
    return ret;
  }


  /**
   * Function to get the latest value in thread-safe way
   *
   * param   arg_ret
   *         Argument object to be populated passed by reference.
   * return  T
   *         Value of the synchronized object
   */  
  virtual void get(T & arg_ret) {
    lock();
    arg_ret = this->value;
    unlock();
  }  
  
private:

  pthread_mutex_t mutex;// mutex to protect the value of the object
  
};


// This is a child class of SynObject to  specially streat C-style strings
struct SyncString : SyncObject<char *> {

 /**
  * Constructor
  *
  * param   init_value
  *         Initial string value for this object
  */
 SyncString(const char *init_value = ""): SyncObject<char *>((char *) init_value){
  value = new char[256];
  strcpy(value, init_value);
 }


  /**
   * Function to set the value in thread-safe way.
   * This function has the same syntax as C printf.
   * param  msg_format
   *      Same as C printf format
   * param  variable number of optional parameters
   *
   */
  void set(const char *msg_format, ...){
    lock();
    va_list msg_list;
    va_start(msg_list, msg_format);
    vsnprintf(value, 256, msg_format, msg_list);
    va_end(msg_list);
    unlock();
  }

  /**
   * This is used to know if the underlying string is empty or not.
   * return bool
   *        true if the string is empty i.e. "", false otherwise
   */
  bool isEmpty(){
    return (strlen(value) == 0);
  }

};// end of structure SyncString


#endif /* SYNC_OBJECT_H_ */

