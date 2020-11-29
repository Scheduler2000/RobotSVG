#include "../inc/ScriptManager.hpp"
#include "../inc/Logger.hpp"
#include "../inc/ConsoleExtension.hpp"
#include <iostream>
#include <cstring>
#include <sstream>

ScriptManager::ScriptManager(Maillage *scene)
    : m_scene(scene) {}

ScriptManager::~ScriptManager()
{
    Logger logger;
    logger.Log("Script Manager dctor destroyed !", LoggerPriority::Debug);
}

std::vector<std::string> ScriptManager::split_input(char *input) const
{
    std::vector<std::string> result;

    char *tokens = std::strtok(input, " ");
    while (tokens != NULL)
    {
        result.push_back(tokens);
        tokens = std::strtok(NULL, " ");
    }
    return result;
}

std::vector<std::string> ScriptManager::split_robot(std::string const &robot) const
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(robot);
    while (std::getline(tokenStream, token, '.'))
        tokens.push_back(token);
    return tokens;
}

ScriptInformation ScriptManager::EntrerCommande()
{
    char *input = new char[50];

    Element *target = nullptr;
    double valeur;
    CommandeType commande;

    std::cout << "Entrer la commande sous la forme (cible type valeur) : ";
    ConsoleExtension::SetConsoleTextColor(ConsoleExtension::ConsoleColor::Green);
    std::fflush(stdin);
    std::fgets(input, 50, stdin);
    ConsoleExtension::SetConsoleTextColor(ConsoleExtension::ConsoleColor::Default_Color);

    auto splited_input = split_input(input);

    valeur = atof(splited_input[2].c_str());
    if (splited_input[1] == "move")
        commande = CommandeType::Translation;
    else if (splited_input[1] == "rotate")
        commande = CommandeType::Rotate;
    else
        commande = CommandeType::None;

    if (splited_input[0].find('.') != std::string::npos) // Si robot
    {
        auto splited_robot = split_robot(splited_input[0]);
        if (splited_robot[1] == "all")
            target = m_scene->ObtenirRobot(splited_robot[0]);
        else
            target = m_scene->ObtenirRobot(splited_robot[0])
                         ->ObtenirForme(splited_robot[1]);
    }
    else
        target = m_scene->ObtenirDecor(splited_input[0]);

    delete input;

    ScriptInformation info(target, commande, valeur);
    return info;
}
