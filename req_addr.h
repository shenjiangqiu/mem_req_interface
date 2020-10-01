#ifndef REQ_ADDR_H
#define REQ_ADDR_H

#include <mem_req_interface.h>
#include <memory>

uint64_t get_addr_by_req(const std::unique_ptr<cache_interface_req> &req);
#endif