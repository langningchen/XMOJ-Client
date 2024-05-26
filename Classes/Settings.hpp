#include <Utilities/Database.hpp>

class SETTINGS
{
public:
    static std::string Get(std::string Name);
    static void Set(std::string Name, std::string Value);
};