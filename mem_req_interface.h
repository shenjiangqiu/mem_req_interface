#ifndef MEM_REQ_I_H
#define MEM_REQ_I_H
#include <deque>

#include <iostream>
#include <map>
#include <vector>
#include <tuple>
#include <assign_wrap.h>

extern unsigned int global_id;
enum class AccessType
{
    ReadWatcherData,
    ReadWatcherValue,
    ReadClauseData,
    ReadClauseValue,
    writeWatcherList,
    writeClause,
    max
};
struct cache_interface_req
{

    unsigned mid;
    cache_interface_req(AccessType t,
                        unsigned w,
                        unsigned cl,
                        unsigned co,
                        assign_wrap *a);
    cache_interface_req(const cache_interface_req &other);
    cache_interface_req(cache_interface_req &&other);
    bool operator==(const cache_interface_req &other) const;
    AccessType type;
    unsigned watcherId;
    unsigned clauseId;
    unsigned ComponentId;
    assign_wrap *as;
    int m_msg_src;
    int m_msg_dst;
    int m_msg_type;
    int m_size;
    /* data */
};
template <typename OSTYPE>
OSTYPE &operator<<(OSTYPE &os, const AccessType &req)
{
    switch (req)
    {
    case AccessType::ReadWatcherData:
        os << "ReadWatcherData";
        break;
    case AccessType::ReadWatcherValue:
        os << "ReadWatcherValue";
        break;
    case AccessType::ReadClauseData:
        os << "ReadClauseData";
        break;
    case AccessType::ReadClauseValue:
        os << "ReadClauseValue";
        break;
    case AccessType::writeWatcherList:
        os << "writeWatcherList";
        break;
    case AccessType::writeClause:
        os << "writeClause";
        break;
    default:
        throw;
        break;
    }
    return os;
}
template <typename OSTYPE>
OSTYPE &operator<<(OSTYPE &os, const cache_interface_req &req)
{
    os << req.mid << "," << req.type << "," << req.watcherId << "," << req.clauseId << "," << req.ComponentId << "," << req.as << ".";
    return os;
}

#endif