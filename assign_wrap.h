#ifndef ASSIGN_WRAP_H
#define ASSIGN_WRAP_H
#include <memory>
#include <tuple>
#include <map>
#include <vector>

class assign_wrap
{
public:
    ~assign_wrap()
    {
    }
    bool is_read_clause(int index)
    {
        return clause_addr.find(index) != clause_addr.end();
    }
    assign_wrap() = delete;
    void add_pushed_list(int index, int value) { pushed_other_list_items.insert(std::make_pair(index, value)); }
    void add_pushed_addr(int index, unsigned long long addr) { pushed_other_list_addr.insert(std::make_pair(index, addr)); }
    void add_clause_addr(int index, unsigned long long value) { clause_addr.insert(std::make_pair(index, value)); }
    void add_detail(int index, unsigned long long value) { clause_detail[index].push_back(value); }
    const std::vector<unsigned long long> &get_clause_detail(int index) const { return clause_detail.at(index); }
    void set_watcher_size(int size) { watcher_size = size; }
    int get_watcher_size() const { return watcher_size; }
    auto get_pushed(int index) const { return pushed_other_list_items.at(index); }
    auto get_pushed_watcher_list_tail_addr(int index)
    {
        return pushed_other_list_addr.at(index);
    }
    auto get_is_push_to_other(int index) const
    {
        return pushed_other_list_items.find(index) != pushed_other_list_items.end();
    }
    auto get_modified_by_range(int start, int end) const
    {
        auto start_iter = clause_addr.lower_bound(start);
        auto end_iter = clause_addr.lower_bound(end);
        return std::make_pair(start_iter, end_iter);
    }
    unsigned int get_level() const { return level; }
    void set_generated_conf(int conf) { generated_conf = conf; }
    int get_generated_conf() const { return generated_conf; }
    //auto& get_generated_assignments() const { return generated_assignments; }
    bool is_genereated(int index) const { return generated_assignments.find(index) != generated_assignments.end(); }
    assign_wrap *get_generated(int index) const { return is_genereated(index) ? generated_assignments.at(index) : nullptr; }
    void add_generated_assignments(int index, assign_wrap *tgenerated)
    {
        generated_assignments.insert(std::make_pair(index, tgenerated));
    }
    friend class assign_wrap_factory;

    assign_wrap(int value,
                int watcher_size,
                int depend_id,
                assign_wrap *depend_value,
                unsigned level = 0) : value(value),
                                      watcher_size(watcher_size),
                                      depend_id(depend_id),
                                      depend_value(depend_value),
                                      generated_conf(-1),
                                      clause_size(0),
                                      level(level)
    {
    }
    assign_wrap(assign_wrap &other) = default;
    assign_wrap(assign_wrap &&other) = default;
    assign_wrap(const assign_wrap &other) = default;
    int get_value() const { return value; }
    void set_addr(unsigned long long t_addr)
    {
        addr = t_addr;
    }                                                                                              //watcher list addr
    unsigned long long get_addr() const { return addr; }                                           //watcher list addr
    unsigned long long get_clause_addr(int index) const { return clause_addr.at(index); }          //clause addr
    void add_clause_literal(int index, int literal) { clause_literals[index].push_back(literal); } // for read
    auto &get_clause_literal(int index) { return clause_literals[index]; }
    void add_block_addr(int index, uint64_t addr)
    {
        blocker_value_addr[index] = addr;
    }

    uint64_t get_block_addr(int index) const
    {
        return blocker_value_addr.at(index);
    }
    void set_watcher_list_meta_addr(uint64_t addr)
    {
        watcher_list_addr = addr;
    }
    uint64_t get_watcher_list_meta_addr() const
    {
        return watcher_list_addr;
    }

private:
    std::map<int, uint64_t> blocker_value_addr;

    //unsigned long long clause_addr;
    int value;
    int watcher_size;
    int depend_id;
    assign_wrap *depend_value;
    //std::pair<int, assign_wrap*> Depends;
    std::map<int, unsigned long long> clause_addr;
    std::map<int, std::vector<unsigned long long>> clause_detail;
    std::map<int, int> pushed_other_list_items;
    int generated_conf;
    std::map<int, std::vector<int>> clause_literals;
    std::map<int, assign_wrap *> generated_assignments;       // must make the ptr weak here to break circular;
    std::map<int, unsigned long long> pushed_other_list_addr; //the addr of the pushed watcher list
    int clause_size;

    unsigned level;
    unsigned long long addr; //store the data of the start of the watcher list.

    unsigned long long watcher_list_addr = 0; //store the addr of the watcher list meta data.
};

class assign_wrap_factory
{
public:
    assign_wrap *create(int value,
                        int watcher_size,
                        int depend_id,
                        assign_wrap *depend_value,
                        int level = 0)
    {

        auto rt = new assign_wrap(value, watcher_size, depend_id, depend_value, level);
        if (depend_id != -1)
        {
            //std::cout<<"added to the assignement"<<std::endl;
            depend_value->add_generated_assignments(depend_id, rt);
        }
        return rt;
    }
};

#endif