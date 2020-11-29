#include "../inc/ScriptLoader.hpp"
#include "../inc/Logger.hpp"

#include <sstream>
#include <iostream>
#include <cstring>

ScriptLoader::ScriptLoader(std::string const &nomFichier, Maillage *scene) : m_scene(scene), m_fichier(NULL)
{
    Logger logger;
    m_fichier = fopen(nomFichier.c_str(), "r");

    if (m_fichier == NULL)
        logger.Log("Erreur : Impossible d'ouvrir le fichier .script", LoggerPriority::Error);
    else
        logger.Log("Fichier .script ouvert avec succes !", LoggerPriority::Info);
}

ScriptLoader::~ScriptLoader()
{
    Logger logger;
    logger.Log("Script Loader dctor destroyed !", LoggerPriority::Debug);
    logger.Log("Fichier fermer avec succes !", LoggerPriority::Info);
    fclose(m_fichier);
}

std::vector<ScriptFonction> ScriptLoader::Load()
{
    std::vector<ScriptInstruction> instructions;
    std::vector<ScriptFonction> fonctions;

    char ligne[80] = " ";
    std::string nomFunc;

    while (fgets(ligne, 80, m_fichier) != NULL)
    {
        if (ligne[0] == '>')
        {
            nomFunc = ligne;
            nomFunc = nomFunc.substr(0, nomFunc.size() - 1);
            parse_instructions(instructions);
            ScriptFonction fonction(nomFunc, instructions);
            fonctions.push_back(fonction);
            instructions.clear();
        }

        memset(ligne, ' ', 80);
    }
    return fonctions;
}

void ScriptLoader::parse_instructions(std::vector<ScriptInstruction> &storage)
{
    char ligne[80] = " ";
    Element *target;
    Logger logger;

    while (true)
    {
        memset(ligne, ' ', 80);
        fgets(ligne, 80, m_fichier);
        std::string input(ligne);

        if (input.find('@') != std::string::npos)
            target = parse_target(input);

        else if (ligne[0] == 'e')
            break;

        else
        {
            auto splited_action = parse_action(input.erase(0, input.find("-") + 1));

            CommandeType ctype = parse_commandeType(splited_action[0]);
            double valeur = atof(splited_action[1].c_str());

            ScriptInformation infos(target, ctype, valeur);
            ScriptInstruction instruction(m_scene, infos);
            storage.push_back(instruction);
        }
    }
}

Element *ScriptLoader::parse_target(std::string &input) const
{
    auto target = input.erase(0, input.find("@") + 1);
    target = target.substr(0, target.size() - 1);

    if (target.find('.') != std::string::npos) // Si robot
    {
        auto splited_robot = split_robot(target);

        if (splited_robot[1] == "all")
            return m_scene->ObtenirRobot(splited_robot[0]);

        else
            return m_scene->ObtenirRobot(splited_robot[0])
                ->ObtenirForme(splited_robot[1]);
    }
    else
        return m_scene->ObtenirDecor(target);
}

std::vector<std::string> ScriptLoader::split_robot(std::string const &robot) const
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(robot);
    while (std::getline(tokenStream, token, '.'))
        tokens.push_back(token);
    return tokens;
}

std::vector<std::string> ScriptLoader::parse_action(std::string const &input) const
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(input);
    while (std::getline(tokenStream, token, ' '))
        tokens.push_back(token);
    return tokens;
}

CommandeType ScriptLoader::parse_commandeType(std::string const &input) const
{
    if (input == "move")
        return CommandeType::Translation;
    else if (input == "rotate")
        return CommandeType::Rotate;
    else
        return CommandeType::None;
}