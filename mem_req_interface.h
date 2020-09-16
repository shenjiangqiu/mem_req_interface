#ifndef MEM_REQ_I_H
#define MEM_REQ_I_H
#include <deque>

#include <iostream>
#include <map>
#include <vector>
#include <tuple>
#include <assign_wrap.h>
enum class AccessType
{
    ReadWatcher,
    WatcherReadValue,
    ReadClauseData,
    ReadClauseValue,
    writeWatcherList,
    writeClause,
    max
};

template <typename OSTYPE>
OSTYPE &operator<<(OSTYPE &os, const AccessType &req)
{
    switch (req)
    {
    case AccessType::ReadWatcher:
        os << "ReadWatcher";
        break;
    case AccessType::WatcherReadValue:
        os << "WatcherReadValue";
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

struct cache_interface_req
{
    cache_interface_req(AccessType t,
                        unsigned w,
                        unsigned cl,
                        unsigned co,
                        assign_wrap *a);
    bool operator==(const cache_interface_req &other) const;
    AccessType type;
    unsigned watcherId;
    unsigned clauseId;
    unsigned ComponentId;
    assign_wrap *as;
    /* data */
};
template <typename OSTYPE>
OSTYPE &operator<<(OSTYPE &os, const cache_interface_req &req)
{
    os << req.type << "," << req.watcherId << "," << req.clauseId << "," << req.ComponentId << "," << req.as << ".";
    return os;
}

#endif