#if !defined(__SCRIPT_INSTRUCTION__)
#define __SCRIPT_INSTRUCTION__

#include "../inc/Maillage.hpp"
#include "../inc/ScriptInformation.hpp"
#include <string>

class ScriptInstruction
{
private:
    Maillage *m_scene;
    ScriptInformation m_infos;

    void move();
    void rotate();

public:
    ScriptInstruction(Maillage *scene, ScriptInformation informations);
    void Execute();
};

#endif // __SCRIPT_INSTRUCTION__
