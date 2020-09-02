#ifndef MEM_REQ_I_H
#define MEM_REQ_I_H
#include <deque>

#include <iostream>
#include <map>
#include <vector>
#include <tuple>
#include <assign_wrap.h>
enum class ReadType
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
OSTYPE &operator<<(OSTYPE &os, const ReadType &req)
{
    switch (req)
    {
    case ReadType::ReadWatcher:
        os << "ReadWatcher";
        break;
    case ReadType::WatcherReadValue:
        os << "WatcherReadValue";
        break;
    case ReadType::ReadClauseData:
        os << "ReadClauseData";
        break;
    case ReadType::ReadClauseValue:
        os << "ReadClauseValue";
        break;
    case ReadType::writeWatcherList:
        os << "writeWatcherList";
        break;
    case ReadType::writeClause:
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
    cache_interface_req(ReadType t,
                        unsigned w,
                        unsigned cl,
                        unsigned co,
                        assign_wrap *a);
    bool operator==(const cache_interface_req &other) const;
    ReadType type;
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