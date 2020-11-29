#if !defined(__APPLICATION_MENU__)
#define __APPLICATION_MENU__

#include "../inc/Logger.hpp"
#include "../inc/Maillage.hpp"
#include "../inc/ConsoleExtension.hpp"
#include "../inc/SvgFile.hpp"

#include "../inc/FichierLoader.hpp"
#include "../inc/FichierRecorder.hpp"

#include "../inc/ScriptInstruction.hpp"
#include "../inc/ScriptManager.hpp"
#include "../inc/ScriptLoader.hpp"
#include "../inc/ScriptMenu.hpp"

#include <iostream>
#include <chrono>
#include <string>
#include <thread>

class ApplicationMenu
{
private:
    void dessinerAscii() const;
    void afficherChoix() const;
    std::string get_file_name(std::string &filePath) const;

public:
    void Run() const;
};

#endif // __APPLICATION_MENU__
