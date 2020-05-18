
/**
 * \ingroup utility
 * @brief contains the class definition of UDPCollector
 * 
 * @file UDPCollector.hpp
 * @author Christopher Sund
 * @date 2018-03-23
 */

#ifndef __UDP_SELECT_H__
#define __UDP_SELECT_H__

#include "prim.h"
#include <errno.h>
#include "lwip/sockets.h"

//#define ASB_UDP_DEBUG

#ifdef ASB_UDP_DEBUG
  #define DEBUG(...) do {log_printf(__VA_ARGS__);} while(0)
#else
  #define DEBUG(...) do {} while(0)
#endif

/**
 * @brief A simple templated UDP monitor that collects datagrams
 * 
 * @tparam S the type of references this collector will fill from datagrams
 * @tparam port_count the number of ports the collector will support
 */
template<typename S, int port_count>
class UDPCollector
{
public:
  /**
   * @brief Construct a new UDPCollector object
   * 
   */
  UDPCollector();

  /**
   * @brief add a port to listen for data on
   * 
   * @param new_port the port to add
   * @return true when successful
   * @return false on failure
   */
  bool add_port_to_monitor(int new_port);

  /**
   * @brief attempt to receive a datagram into the given S instance used
   * as a buffer
   * 
   * @param buffer a pointer to copy into from a received datagram
   * @return int the port received from on success, a value less than zero on
   * failure
   */
  int receive_datagram(S* buffer);

  /**
   * @brief allows for another thread to interrupt a blocking receive call
   * 
   */
  void interrupt_receive();
private:
  /// the socket file descriptor type
  typedef int socket_fd_t;
  /// the listening address type
  typedef struct sockaddr_in ipv4_addr_t;
  /// an array of socket file descriptors to recv on
  socket_fd_t socket_descriptors[port_count];
  /// an array of address to recv from
  ipv4_addr_t socket_addresses[port_count];
  /// then number of ports currently added
  size_t connection_count;
  /// an fd_set instance for use in select
  fd_set udp_recv_set;
};

template<typename S, int port_count>
UDPCollector<S, port_count>::UDPCollector() : connection_count(0)
{

}

template<typename S, int port_count>
bool UDPCollector<S, port_count>::add_port_to_monitor(int port_to_add)
{
  DEBUG("Adding port %d to monitor...\n", port_to_add);
  socket_fd_t new_fd = -1;
  ipv4_addr_t recv_addr;
  //create socket for receiving
  new_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if(new_fd < 0)
  {
    DEBUG("Unable to create socket: %d\n", errno);
    return false;
  }
  recv_addr.sin_family = AF_INET;
  recv_addr.sin_port = htons(port_to_add);
  recv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  DEBUG("binding %d to address %p\n", new_fd, &recv_addr);
  if(bind(new_fd, (struct sockaddr*) &recv_addr, sizeof(recv_addr)) < 0)
  {
    DEBUG("Unable to bind socket to given address: %d\n", errno);
    return false;
  }
  socket_descriptors[connection_count] = new_fd;
  socket_addresses[connection_count] = recv_addr;
  connection_count++;
  DEBUG("port %d successfully added\n", port_to_add);
  return true;
}

template<typename S, int port_count>
int UDPCollector<S, port_count>::receive_datagram(S* buffer)
{
  FD_ZERO(&udp_recv_set);
  socket_fd_t nfds = 0;
  socket_fd_t fd = 0;
  for(size_t idx = 0; idx < connection_count; idx++)
  {
    fd = socket_descriptors[idx];
    //add each socket
    FD_SET(fd, &udp_recv_set);
    if(fd > nfds)
    {
      nfds = fd;
    }
  }
  nfds += 1;
  if(select(nfds, &udp_recv_set, NULL, NULL, NULL) <= 0)
  {
    DEBUG("Encountered an error while using select: %d\n", errno);
    return -1;
  }
  int recv_size;
  for(size_t idx = 0; idx < connection_count; idx++)
  {
    fd = socket_descriptors[idx];
    if(FD_ISSET(fd, &udp_recv_set))
    {
      if((recv_size = recv(fd, buffer, sizeof(S), MSG_DONTWAIT)) < 0)
      {
        DEBUG("encountered error in recv: %d\n", errno);
        return -2;
      }
      int out_port = (int)ntohs(socket_addresses[idx].sin_port);
      return out_port;
    }
  }
  //shouldn't be reachable
  DEBUG("No file descriptor was set even though select returned\n");
  return -3;
}

template<typename S, int port_count>
void UDPCollector<S, port_count>::interrupt_receive()
{
  int err;
  for(size_t idx = 0; idx < connection_count; idx++)
  {
    int fd = socket_descriptors[idx];
    DEBUG("Force closing socket %d\n", socket_descriptors[idx]);
    if((err = shutdown(fd, SHUT_RDWR)))
    {
      DEBUG("Encountered error %d while trying to shutdown socket %d\n", errno, fd);
    }
    if((err = close(fd)))
    {
      DEBUG("Encountered error %d while trying to close socket %d\n", errno, fd);
    }
  }
}

#endif
