#include "mem_req_interface.h"
unsigned global_id = 0;

cache_interface_req::cache_interface_req(AccessType t,
                                         unsigned w,
                                         unsigned cl,
                                         unsigned co,
                                         assign_wrap *a) : mid(global_id++),
                                                           type(t),
                                                           watcherId(w),
                                                           clauseId(cl),
                                                           ComponentId(co),
                                                           as(a) {}
bool cache_interface_req::operator==(const cache_interface_req &other) const
{
    return mid == other.mid and
           type == other.type and
           watcherId == other.watcherId and
           clauseId == other.clauseId and
           ComponentId == other.ComponentId and
           as == other.as;
}
cache_interface_req::cache_interface_req(const cache_interface_req &other) : mid(global_id++),
                                                                             type(other.type),
                                                                             watcherId(other.watcherId),
                                                                             clauseId(other.clauseId),
                                                                             ComponentId(other.ComponentId),
                                                                             as(other.as)
{
}
cache_interface_req::cache_interface_req(cache_interface_req &&other) : mid(global_id++),
                                                                        type(other.type),
                                                                        watcherId(other.watcherId),
                                                                        clauseId(other.clauseId),
                                                                        ComponentId(other.ComponentId),
                                                                        as(other.as)
{
}
