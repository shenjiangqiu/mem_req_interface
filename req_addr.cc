#include <mem_req_interface.h>
#include <memory>
#include <cassert>

uint64_t get_addr_by_req(const std::unique_ptr<cache_interface_req> &req)
{
    uint64_t addr;
    auto type = req->type;
    auto as = req->as;
    auto watcherId = req->watcherId;
    auto clauseId = req->clauseId;
    switch (type)
    {
    case AccessType::ReadClauseData:
        /* code */

        addr = as->get_clause_addr(watcherId);
        addr += clauseId * 4;

        break;
    case AccessType::ReadClauseValue:
        addr = as->get_clause_detail(watcherId)[clauseId];
        break;
    case AccessType::ReadWatcherData:
        assert(as != nullptr);
        addr = as->get_addr();
        addr += 4 * watcherId;
        break;
    case AccessType::ReadWatcherValue:
        assert(as->get_watcher_size() != 0);
        addr = as->get_block_addr(watcherId);

        break;
    case AccessType::WriteClause:
        addr = as->get_clause_addr(watcherId);
        break;
    case AccessType::WriteWatcherList:
        if (as->get_is_push_to_other(watcherId))
            addr = as->get_pushed_watcher_list_tail_addr(watcherId);
        else
        {
            addr = as->get_addr() + as->get_watcher_size() * 8; //current watcher
        }

        break;
    case AccessType::WriteMissRead:
    case AccessType::EvictWrite:
        addr = req->addr;
        break;
    case AccessType::ReadWatcherMetaData:
        addr = req->as->get_watcher_list_meta_addr();
        break;
    case AccessType::ReadOtherWatcherList:
        addr = req->as->get_other_watcher_list_meta_data(req->watcherId);
        break;

    default:
        throw;
        break;
    }
    return addr;
}