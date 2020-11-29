#if !defined(__SCRIPT_FONCTION__)
#define __SCRIPT_FONCTION__

#include <string>
#include <vector>
#include "../inc/ScriptInstruction.hpp"

class ScriptFonction
{
private:
    std::string m_nom;
    std::vector<ScriptInstruction> m_instructions;

public:
    ScriptFonction(std::string const &nom, std::vector<ScriptInstruction> const &instructions);

    void Execute(long delay) const;
    std::string ObtenirNom() const;
};

#endif // __SCRIPT_FONCTION__
