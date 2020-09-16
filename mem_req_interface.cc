#include "mem_req_interface.h"
cache_interface_req::cache_interface_req(AccessType t,
                                         unsigned w,
                                         unsigned cl,
                                         unsigned co,
                                         assign_wrap *a) : type(t),
                                                           watcherId(w),
                                                           clauseId(cl),
                                                           ComponentId(co),
                                                           as(a) {}
bool cache_interface_req::operator==(const cache_interface_req &other) const
{
    return type == other.type and
           watcherId == other.watcherId and
           clauseId == other.clauseId and
           ComponentId == other.ComponentId and
           as == other.as;
}