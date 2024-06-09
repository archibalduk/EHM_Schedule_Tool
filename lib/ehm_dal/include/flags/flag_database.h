#pragma once


// Qt headers
#include <memory>
#include <vector>

namespace ehm_dal::flags {

class FlagTable;
enum class FlagIndex : char;

class FlagDatabase
{
public:
    FlagDatabase();

    // Get data
    static std::shared_ptr<FlagTable> table(const FlagIndex table_id);

    // Initialisation
    void init();

private:
    // Tables
    static std::vector<std::shared_ptr<FlagTable>> table_data_;

    // Initialisation
    static bool is_initialised_;
    inline bool isInitialised() { return is_initialised_; }
};

} // namespace ehm_dal::flags


