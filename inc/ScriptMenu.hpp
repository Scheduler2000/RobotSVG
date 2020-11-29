#if !defined(__SCRIPT_MENU__)
#define __SCRIPT_MENU__

#include <string>
#include <vector>
#include "../inc/ScriptFonction.hpp"

class ScriptMenu
{
private:
    void afficher_menu(std::vector<ScriptFonction> const &fonctions) const;

public:
    void EnterMenu(std::vector<ScriptFonction> const &fonctions) const;
};

#endif // __SCRIPT_MENU__
