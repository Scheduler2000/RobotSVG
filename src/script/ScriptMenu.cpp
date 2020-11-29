#include "../inc/ScriptMenu.hpp"
#include "../inc/Logger.hpp"
#include "../inc/ConsoleExtension.hpp"
#include <iostream>

void ScriptMenu::EnterMenu(std::vector<ScriptFonction> const &fonctions) const
{
    int choix = 0;
    bool quitter = false;
    do
    {
        afficher_menu(fonctions);
        std::cout << "choix : ";
        ConsoleExtension::SetConsoleTextColor(ConsoleExtension::ConsoleColor::Green);
        std::cin >> choix;
        std::cin.ignore();
        ConsoleExtension::SetConsoleTextColor(ConsoleExtension::ConsoleColor::Default_Color);

        if (choix == -1 || choix >= fonctions.size())
            quitter = true;
        else
            fonctions[choix].Execute(1030);
    } while (!quitter);
}

void ScriptMenu::afficher_menu(std::vector<ScriptFonction> const &fonctions) const
{
    Logger logger;
    logger.Log("Script rom loaded.", LoggerPriority::Info);
    std::cout << std::endl;

    std::cout << "-1 > "
              << "quitter" << std::endl;
    for (size_t i = 0; i < fonctions.size(); i++)
        std::cout << " " << i << " " << fonctions[i].ObtenirNom() << std::endl;

    std::cout << std::endl;
    std::cout << fonctions.size() << " functions loaded." << std::endl;
}