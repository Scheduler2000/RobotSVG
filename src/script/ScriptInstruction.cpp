#include "../inc/ScriptInstruction.hpp"
#include "../inc/Logger.hpp"
#include <iostream>

ScriptInstruction::ScriptInstruction(Maillage *scene, ScriptInformation informations)
    : m_scene(scene), m_infos(informations) {}

void ScriptInstruction::move()
{
    double valeur = m_scene->ObtenirLargeur() * m_infos.ObtenirValeur();

    Forme *decor = dynamic_cast<Forme *>(m_infos.ObtenirTarget());
    Robot *robot = dynamic_cast<Robot *>(m_infos.ObtenirTarget());
    Logger logger;

    if (robot == nullptr && decor == nullptr)
        logger.Log("Script Instruction : Cible inconnue !", LoggerPriority::Error);
    else
    {
        Svgfile dessinVec;
        if (decor != nullptr)
        {
            decor->Deplacer(valeur);
            for (auto ptrRobot : m_scene->ObtenirRobots())
                if (ptrRobot->ObtenirForme(RobotComposant::Tete) == decor) // input command : bot1.visage ()
                    for (auto ptrForme : ptrRobot->ObtenirVisage())
                        ptrForme->Deplacer(valeur);
        }
        else
            robot->Deplacer(valeur);

        m_scene->Dessiner(dessinVec, false);
    }
}

void ScriptInstruction::rotate()
{
    Forme *decor = dynamic_cast<Forme *>(m_infos.ObtenirTarget());
    Robot *robot = dynamic_cast<Robot *>(m_infos.ObtenirTarget());
    Logger logger;

    if (robot == nullptr && decor == nullptr)
        logger.Log("Script Instruction : Cible inconnue !", LoggerPriority::Error);
    else
    {

        double angle = 360 * m_infos.ObtenirValeur();
        if (decor != nullptr)
        {
            Svgfile dessinVec;
            decor->Rotate(angle);
            for (auto ptrRobot : m_scene->ObtenirRobots())
                if (ptrRobot->ObtenirForme(RobotComposant::Tete) == decor) // input command : bot1.visage ()
                    for (auto ptrForme : ptrRobot->ObtenirVisage())
                        ptrForme->Rotate(angle);

            m_scene->Dessiner(dessinVec, false);
        }
        else
            logger.Log("Rotation non disponible pour un robot !", LoggerPriority::Fatal_Error);
    }
}

void ScriptInstruction::Execute()
{
    Logger logger;

    switch (m_infos.ObtenirAction())
    {
    case CommandeType::Rotate:
        rotate();
        break;
    case CommandeType::Translation:
        move();
        break;
    case CommandeType::None:
        logger.Log("Commande inconnue !", LoggerPriority::Error);
        break;
    }
}
