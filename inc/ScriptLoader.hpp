#if !defined(__SCRIPT_LOADER__)
#define __SCRIPT_LOADER__

#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include "../inc/ScriptInstruction.hpp"
#include "../inc/ScriptFonction.hpp"

class ScriptLoader
{
private:
    Maillage *m_scene;
    FILE *m_fichier;

    void parse_instructions(std::vector<ScriptInstruction> &storage);
    CommandeType parse_commandeType(std::string const &input) const;
    Element *parse_target(std::string &input) const;
    std::vector<std::string> parse_action(std::string const &input) const;

    std::vector<std::string> split_robot(std::string const &robot) const;

public:
    ScriptLoader(std::string const &nomFichier, Maillage *scene);
    ~ScriptLoader();

    std::vector<ScriptFonction> Load();
};

#endif // __SCRIPT_LOADER__
