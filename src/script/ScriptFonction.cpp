#include "../inc/ScriptFonction.hpp"
#include "../inc/Logger.hpp"
#include <chrono>
#include <thread>

ScriptFonction::ScriptFonction(std::string const &nom, std::vector<ScriptInstruction> const &instructions)
    : m_nom(nom), m_instructions(instructions) {}

void ScriptFonction::Execute(long delay) const
{
    Logger logger;

    for (auto instruction : m_instructions)
    {
        instruction.Execute();
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }

    logger.Log(m_nom + " function finished ! ", LoggerPriority::Info);
}

std::string ScriptFonction::ObtenirNom() const { return m_nom; }