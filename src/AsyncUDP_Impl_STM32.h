/****************************************************************************************************************************
  AsyncUdp_Impl_STM32.h
  
  For STM32 with built-in LAN8742A Ethernet (Nucleo-144, DISCOVERY, etc)
  
  AsyncUDP_STM32 is a Async UDP library for the STM32 using built-in LAN8742A Ethernet
  
  Based on and modified from ESPAsyncUDP Library (https://github.com/me-no-dev/ESPAsyncUDP)
  Built by Khoi Hoang https://github.com/khoih-prog/AsyncUDP_STM32
  Licensed under MIT license
  
  Version: 1.3.0
  
  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.1.0   K Hoang      03/09/2020 Initial coding for STM32 for built-in Ethernet (Nucleo-144, DISCOVERY, etc).
                                  Bump up version to v1.1.0 to sync with ESPAsyncUDP v1.1.0
  1.2.0   K Hoang      11/04/2021 Add support to LAN8720 using STM32F4 or STM32F7
  1.2.1   K Hoang      09/10/2021 Update `platform.ini` and `library.json`
  1.3.0   K Hoang      21/06/2022 Fix multiple-definitions linker error. Update for STM32 core v2.3.0 
 *****************************************************************************************************************************/

#pragma once

#ifndef ASYNCUDP_IMPL_STM32_H
#define ASYNCUDP_IMPL_STM32_H

/////////////////////////////////////////////////////////////////////////////

AsyncUDPMessage::AsyncUDPMessage(size_t size)
{
  _index = 0;
  
  if (size > TCP_MSS) 
  {
    size = TCP_MSS;
  }
  
  _size = size;
  _buffer = (uint8_t *)malloc(size);
}

///////////////////////////////////////////////////

AsyncUDPMessage::~AsyncUDPMessage()
{
  if (_buffer) 
  {
    free(_buffer);
  }
}

///////////////////////////////////////////////////

size_t AsyncUDPMessage::write(const uint8_t *data, size_t len)
{
  if (_buffer == NULL) 
  {
    return 0;
  }
  
  size_t s = space();
  
  if (len > s) 
  {
    len = s;
  }
  
  memcpy(_buffer + _index, data, len);
  _index += len;
  
  return len;
}

///////////////////////////////////////////////////

size_t AsyncUDPMessage::write(uint8_t data)
{
  return write(&data, 1);
}

///////////////////////////////////////////////////

size_t AsyncUDPMessage::space()
{
  if (_buffer == NULL) 
  {
    return 0;
  }
  
  return (_size - _index);
}

uint8_t * AsyncUDPMessage::data()
{
  return _buffer;
}

size_t AsyncUDPMessage::length()
{
  return _index;
}

void AsyncUDPMessage::flush()
{
  _index = 0;
}

/////////////////////////////////////////////////////////////////////////////

AsyncUDPPacket::AsyncUDPPacket(AsyncUDP *udp, ip_addr_t *localIp, uint16_t localPort, ip_addr_t *remoteIp, 
                                uint16_t remotePort, uint8_t *data, size_t len)
{
  _udp = udp;
  _localIp = localIp;
  _localPort = localPort;
  _remoteIp = remoteIp;
  _remotePort = remotePort;
  _data = data;
  _len = len;
}

///////////////////////////////////////////////////

AsyncUDPPacket::~AsyncUDPPacket()
{

}

///////////////////////////////////////////////////

uint8_t * AsyncUDPPacket::data()
{
  return _data;
}

///////////////////////////////////////////////////

size_t AsyncUDPPacket::length()
{
  return _len;
}

///////////////////////////////////////////////////

IPAddress AsyncUDPPacket::localIP()
{
  return IPAddress(_localIp->addr);
}

///////////////////////////////////////////////////

uint16_t AsyncUDPPacket::localPort()
{
  return _localPort;
}

///////////////////////////////////////////////////

IPAddress AsyncUDPPacket::remoteIP()
{
  return IPAddress(_remoteIp->addr);
}

///////////////////////////////////////////////////

uint16_t AsyncUDPPacket::remotePort()
{
  return _remotePort;
}

///////////////////////////////////////////////////

bool AsyncUDPPacket::isBroadcast()
{
  return _localIp->addr == 0xFFFFFFFF || _localIp->addr == (uint32_t)(0);
}

///////////////////////////////////////////////////

bool AsyncUDPPacket::isMulticast()
{
  return ip_addr_ismulticast(_localIp);
}

///////////////////////////////////////////////////

size_t AsyncUDPPacket::write(const uint8_t *data, size_t len)
{
  return _udp->writeTo(data, len, _remoteIp, _remotePort);
}

///////////////////////////////////////////////////

size_t AsyncUDPPacket::write(uint8_t data)
{
  return write(&data, 1);
}

///////////////////////////////////////////////////

size_t AsyncUDPPacket::send(AsyncUDPMessage &message)
{
  return write(message.data(), message.length());
}

/////////////////////////////////////////////////////////////////////////////

AsyncUDP::AsyncUDP()
{
  _pcb = NULL;
  _connected = false;
  _handler = NULL;
}

///////////////////////////////////////////////////

AsyncUDP::~AsyncUDP()
{
  close();
}

///////////////////////////////////////////////////

AsyncUDP::operator bool()
{
  return _connected;
}

///////////////////////////////////////////////////

bool AsyncUDP::connected()
{
  return _connected;
}

///////////////////////////////////////////////////

void AsyncUDP::onPacket(AuPacketHandlerFunctionWithArg cb, void * arg)
{
  onPacket(std::bind(cb, arg, std::placeholders::_1));
}

///////////////////////////////////////////////////

void AsyncUDP::onPacket(AuPacketHandlerFunction cb)
{
  _handler = cb;
}

///////////////////////////////////////////////////

void AsyncUDP::_recv(udp_pcb *upcb, pbuf *pb, ip_addr_t *addr, uint16_t port)
{
  (void)upcb; // its unused, avoid warning
  
  while (pb != NULL) 
  {
    if (_handler) 
    {
      uint8_t * data = (uint8_t*)((pb)->payload);
      size_t len = pb->len;

      ip_hdr* iphdr = reinterpret_cast<ip_hdr*>(data - UDP_HLEN - IP_HLEN);
      ip_addr_t daddr;
      daddr.addr = iphdr->dest.addr;

      udp_hdr* udphdr = reinterpret_cast<udp_hdr*>(((uint8_t*)((pb)->payload)) - UDP_HLEN);
      uint16_t dport = ntohs(udphdr->dest);

      AsyncUDPPacket packet(this, &daddr, dport, addr, port, data, len);
      
      UDP_LOGDEBUG3("_recv: Call packetHandler with packet from remoteIP =", IPAddress(addr->addr), ", remotePort =", port);
      UDP_LOGDEBUG3("To destIP =", IPAddress(daddr.addr), ", destPort =", dport);
      UDP_LOGDEBUG1("Packet len =", len);
      
      _handler(packet);
    }
    else
    {
      UDP_LOGDEBUG("_recv: No packetHandler");
    }

    pbuf * this_pb = pb;
    pb = pb->next;
    this_pb->next = NULL;
    pbuf_free(this_pb);
  }
}

///////////////////////////////////////////////////

#if LWIP_VERSION_MAJOR == 1
void AsyncUDP::_s_recv(void *arg, udp_pcb *upcb, pbuf *p, ip_addr_t *addr, uint16_t port)
#else
void AsyncUDP::_s_recv(void *arg, udp_pcb *upcb, pbuf *p, const ip_addr_t *addr, uint16_t port)
#endif
{
  reinterpret_cast<AsyncUDP*>(arg)->_recv(upcb, p, (ip_addr_t *)addr, port);
}

///////////////////////////////////////////////////

bool AsyncUDP::listen(ip_addr_t *addr, uint16_t port)
{
  close();
  _pcb = udp_new();
  
  if (_pcb == NULL) 
  {
    UDP_LOGDEBUG("listen: Error NULL pcb");
    
    return false;
  }
  
  err_t err = udp_bind(_pcb, addr, port);
  
  if (err != ERR_OK) 
  {
    close();
    
    UDP_LOGDEBUG1("listen: Can't bind UDP, error =", err);
    
    return false;
  }
  
  udp_recv(_pcb, &_s_recv, (void *) this);
  _connected = true;
  
  return true;
}

///////////////////////////////////////////////////

bool AsyncUDP::listenMulticast(ip_addr_t *addr, uint16_t port, uint8_t ttl)
{
  close();
  
  if (!ip_addr_ismulticast(addr)) 
  {
    return false;
  }

  ip_addr_t multicast_if_addr;

  // KH, Get localIP into multicast_if_addr
  IPAddress thisIPAddress = Ethernet.localIP();

  IP_ADDR4(&multicast_if_addr, thisIPAddress[0], thisIPAddress[1], thisIPAddress[2], thisIPAddress[3]);
  //////

  // KH, you have to modify line 1070 of "lwip/opt.h" in STM32duino_LwIP library to use multicast feature
  // From #define LWIP_IGMP     0
  // to   #define LWIP_IGMP     1
  // 
  // Otherwise, you'll get error "undefined reference to `igmp_joingroup(ip4_addr const*, ip4_addr const*)`
  //
  // Just old design not permitting the definitions here to affect deeply into underlying files
  // Even #define LWIP_IPV4         1 and #define LWIP_IGMP         1
  // didn't solve the issue

  
  // err_t  igmp_joingroup(const ip4_addr_t *ifaddr, const ip4_addr_t *groupaddr)
  if ( (igmp_joingroup(&multicast_if_addr, addr) != ERR_OK) )
  {
    return false;
  }
  
  if (!listen(IPADDR_ANY, port)) 
  {
    return false;
  }

#if LWIP_VERSION_MAJOR == 1
  udp_set_multicast_netif_addr(_pcb, multicast_if_addr);
#else
  udp_set_multicast_netif_addr(_pcb, &multicast_if_addr);
#endif

  udp_set_multicast_ttl(_pcb, ttl);

  ip_addr_copy(_pcb->remote_ip, *addr);
  _pcb->remote_port = port;
  
  return true;
}

///////////////////////////////////////////////////

bool AsyncUDP::connect(ip_addr_t *addr, uint16_t port)
{
  close();
  
  _pcb = udp_new();
  
  if (_pcb == NULL) 
  {
    UDP_LOGDEBUG("connect: Error NULL pcb");
    
    return false;
  }
  
  err_t err = udp_connect(_pcb, addr, port);
  
  if (err != ERR_OK) 
  {
    close();
    
    UDP_LOGDEBUG1("connect: Can't connect, error =", err);
    
    return false;
  }
  
  udp_recv(_pcb, &_s_recv, (void *) this);
  _connected = true;
  
  return true;
}

///////////////////////////////////////////////////

void AsyncUDP::close()
{
  if (_pcb != NULL) 
  {
    if (_connected) 
    {
      udp_disconnect(_pcb);
    }
    
    udp_remove(_pcb);
    _connected = false;
    _pcb = NULL;
  }
}

///////////////////////////////////////////////////

size_t AsyncUDP::writeTo(const uint8_t *data, size_t len, ip_addr_t *addr, uint16_t port)
{
  if (!_pcb && !connect(addr, port)) 
  {
    UDP_LOGDEBUG("writeTo: NULL pcb and Can't connect. No write");
    
    return 0;
  }
  
  if (len > TCP_MSS) 
  {
    len = TCP_MSS;
  }
  
  pbuf* pbt = pbuf_alloc(PBUF_TRANSPORT, len, PBUF_RAM);
  
  if (pbt != NULL) 
  {
    uint8_t* dst = reinterpret_cast<uint8_t*>(pbt->payload);
    memcpy(dst, data, len);
    err_t err = udp_sendto(_pcb, pbt, addr, port);
    pbuf_free(pbt);
    
    if (err < ERR_OK) 
    {
      UDP_LOGDEBUG1("writeTo: UDP send error =", err);
      
      return 0;
    }
    
    return len;
  }
  
  return 0;
}

///////////////////////////////////////////////////

bool AsyncUDP::listen(const IPAddress addr, uint16_t port)
{
  ip_addr_t laddr;
  laddr.addr = addr;
  return listen(&laddr, port);
}

///////////////////////////////////////////////////

bool AsyncUDP::listen(uint16_t port)
{
  return listen(IPAddress((uint32_t)INADDR_ANY), port);
}

///////////////////////////////////////////////////

bool AsyncUDP::listenMulticast(const IPAddress addr, uint16_t port, uint8_t ttl)
{
  ip_addr_t laddr;
  laddr.addr = addr;
  
  return listenMulticast(&laddr, port, ttl);
}

///////////////////////////////////////////////////

bool AsyncUDP::connect(const IPAddress addr, uint16_t port)
{
  ip_addr_t daddr;
  daddr.addr = addr;
  
  return connect(&daddr, port);
}

///////////////////////////////////////////////////

size_t AsyncUDP::writeTo(const uint8_t *data, size_t len, const IPAddress addr, uint16_t port)
{
  ip_addr_t daddr;
  daddr.addr = addr;
  
  return writeTo(data, len, &daddr, port);
}

///////////////////////////////////////////////////

size_t AsyncUDP::write(const uint8_t *data, size_t len)
{
  if (_pcb) 
  {
    return writeTo(data, len, &(_pcb->remote_ip), _pcb->remote_port);
  }
  
  UDP_LOGDEBUG("write: NULL pcb. No write");
  
  return 0;
}

///////////////////////////////////////////////////

size_t AsyncUDP::write(uint8_t data)
{
  return write(&data, 1);
}

///////////////////////////////////////////////////

size_t AsyncUDP::broadcastTo(uint8_t *data, size_t len, uint16_t port)
{
  ip_addr_t daddr;
  daddr.addr = 0xFFFFFFFF;
  
  return writeTo(data, len, &daddr, port);
}

///////////////////////////////////////////////////

size_t AsyncUDP::broadcastTo(const char * data, uint16_t port)
{
  return broadcastTo((uint8_t *)data, strlen(data), port);
}

///////////////////////////////////////////////////

size_t AsyncUDP::broadcast(uint8_t *data, size_t len)
{
  if (_pcb->local_port != 0) 
  {
    return broadcastTo(data, len, _pcb->local_port);
  }
  
  UDP_LOGDEBUG("broadcast: NULL local_port. No broadcast");
  
  return 0;
}

///////////////////////////////////////////////////

size_t AsyncUDP::broadcast(const char * data)
{
  return broadcast((uint8_t *)data, strlen(data));
}

///////////////////////////////////////////////////

size_t AsyncUDP::sendTo(AsyncUDPMessage &message, ip_addr_t *addr, uint16_t port)
{
  if (!message) 
  {
    UDP_LOGDEBUG("sendTo: NULL message. No sendTo");
    
    return 0;
  }
  
  return writeTo(message.data(), message.length(), addr, port);
}

///////////////////////////////////////////////////

size_t AsyncUDP::sendTo(AsyncUDPMessage &message, const IPAddress addr, uint16_t port)
{
  if (!message) 
  {
    UDP_LOGDEBUG("sendTo: NULL message. No sendTo");
    
    return 0;
  }
  
  return writeTo(message.data(), message.length(), addr, port);
}

///////////////////////////////////////////////////

size_t AsyncUDP::send(AsyncUDPMessage &message)
{
  if ((!message) || (!_pcb)) 
  {
    UDP_LOGDEBUG("sendTo: NULL message or pcb. No send");
    
    return 0;
  }
  
  return writeTo(message.data(), message.length(), &(_pcb->remote_ip), _pcb->remote_port);
}

///////////////////////////////////////////////////

size_t AsyncUDP::broadcastTo(AsyncUDPMessage &message, uint16_t port)
{
  if (!message) 
  {
    UDP_LOGDEBUG("broadcastTo: NULL message. No broadcast");
    
    return 0;
  }
  
  return broadcastTo(message.data(), message.length(), port);
}

///////////////////////////////////////////////////

size_t AsyncUDP::broadcast(AsyncUDPMessage &message)
{
  if (!message) 
  {
    UDP_LOGDEBUG("broadcast: NULL message. No broadcast");
    
    return 0;
  }
  
  return broadcast(message.data(), message.length());
}

///////////////////////////////////////////////////

#endif    // ASYNCUDP_IMPL_STM32_H
