#if !defined(__SCRIPT_MANAGER__)
#define __SCRIPT_MANAGER__

#include <string>
#include <vector>
#include "../inc/Element.hpp"
#include "../inc/Maillage.hpp"
#include "../inc/CommandeType.hpp"
#include "../inc/ScriptInformation.hpp"

class ScriptManager
{
private:
    Maillage *m_scene;
    std::vector<std::string> split_input(char *input) const;
    std::vector<std::string> split_robot(std::string const &robot) const;

public:
    ScriptManager(Maillage *scene);
    ~ScriptManager();

     ScriptInformation EntrerCommande();
};

#endif // __SRIPT_FINDER__
