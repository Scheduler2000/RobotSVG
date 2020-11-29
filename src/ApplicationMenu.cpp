#include "../inc/ApplicationMenu.hpp"

void ApplicationMenu::dessinerAscii() const
{

    ConsoleExtension::SetConsoleTextColor(ConsoleExtension::ConsoleColor::Blue);

    std::cout
        << "      :::::::::   ::::::::  :::::::::   :::::::: ::::::::::: ::::::::::: ::::::::          ::::::::    :::   ::: \n"
        << "     :+:    :+: :+:    :+: :+:    :+: :+:    :+:    :+:         :+:    :+:    :+:        :+:    :+:  :+:+: :+:+: \n"
        << "   + :+    +:+ +:+    +:+ +:+    +:+ +:+    +:+    +:+         +:+    +:+               +:+    +:+ +:+ +:+:+ +:+ \n";

    ConsoleExtension::SetConsoleTextColor(ConsoleExtension::ConsoleColor::Default_Color);

    std::cout
        << "   +#++:++#:  +#+    +:+ +#++:++#+  +#+    +:+    +#+         +#+    +#+               +#+    +:+ +#+  +:+  +#+  \n"
        << "  +#+    +#+ +#+    +#+ +#+    +#+ +#+    +#+    +#+         +#+    +#+               +#+    +#+ +#+       +#+   \n";

    ConsoleExtension::SetConsoleTextColor(ConsoleExtension::ConsoleColor::Red);

    std::cout
        << " #+#    #+# #+#    #+# #+#    #+# #+#    #+#    #+#         #+#    #+#    #+#        #+#    #+# #+#       #+#    \n"
        << "###    ###  ########  #########   ########     ###     ########### ########          ########  ###       ###     \n\n";

    ConsoleExtension::SetConsoleTextColor(ConsoleExtension::ConsoleColor::Default_Color);
}

void ApplicationMenu::afficherChoix() const
{

    dessinerAscii();

    std::cout << "0. exit" << std::endl;
    std::cout << "1. load fichier.rom" << std::endl;
    std::cout << "2. reload" << std::endl;
    std::cout << "3. enter debugging mode" << std::endl;
    std::cout << "4. store" << std::endl;
    std::cout << "5. restore" << std::endl;
    std::cout << "6. save & close scene" << std::endl;
    std::cout << "7. enter script mode" << std::endl;
    std::cout << "8. load script" << std::endl
              << std::endl;
}

std::string ApplicationMenu::get_file_name(std::string &filePath) const // juste pour le fichier.rom ><
{
    auto dotPos = filePath.rfind('.');
    auto sepPos = filePath.rfind('\\');

    if (sepPos != std::string::npos)
        return filePath.substr(sepPos + 1, filePath.size() - (true || dotPos != std::string::npos ? 1 : dotPos));

    return "";
}

void ApplicationMenu::Run() const
{
    int choix;
    std::string fichier = " ";
    Maillage *storage = nullptr;
    Maillage *scene = nullptr;
    Logger logger;

    do
    {
        ConsoleExtension::ClearConsole();
        afficherChoix();

        std::cout << "Choix menu : ";
        ConsoleExtension::SetConsoleTextColor(ConsoleExtension::ConsoleColor::Green);
        std::cin >> choix;
        ConsoleExtension::SetConsoleTextColor(ConsoleExtension::ConsoleColor::Default_Color);
        std::cout << std::endl;

        switch (choix)
        {
        case 0:
        {
            std::cout << "Fermeture de l'application." << std::endl;
            delete scene;
            delete storage;

            scene = nullptr;
            storage = nullptr;
        }
        break;
        case 1:
        {
            if (scene == nullptr && fichier == " ")
            {
                std::cout << "Entrer le chemin d'acces au fichier .rom : ";
                ConsoleExtension::SetConsoleTextColor(ConsoleExtension::ConsoleColor::Green);
                std::cin >> fichier;
                ConsoleExtension::SetConsoleTextColor(ConsoleExtension::ConsoleColor::Default_Color);

                FichierLoader fl(fichier);
                scene = new Maillage(fl.Load());
                Svgfile dessinVec;
                scene->Dessiner(dessinVec, false);
            }
            else
                logger.Log("Veuillez d'abord quitter votre scene actuelle !", LoggerPriority::Error);
        }
        break;
        case 2:
        {
            if (fichier == " ")
                logger.Log("Impossible de reload, fichier inconnue !", LoggerPriority::Error);
            else
            {
                Svgfile dessinVec;
                FichierLoader fl(fichier);
                delete scene;
                scene = new Maillage(fl.Load());
                scene->Dessiner(dessinVec, false);
                logger.Log("Reload termine !", LoggerPriority::Info);
            }
        }
        break;
        case 3:
        {
            if (scene != nullptr)
            {
                Svgfile dessinVec;
                scene->Dessiner(dessinVec, true);
                logger.Log("Entrer en mode debug !", LoggerPriority::Info);
            }
            else
                logger.Log("Impossible de rentrer en mode debug, scene null !", LoggerPriority::Error);
        }
        break;
        case 4:
        {
            if (scene != nullptr)
            {
                if (storage != nullptr)
                {
                    char rep;
                    logger.Log("Attention, il existe déja une version de storage en memoire, voulez vous l'ecraser ? (O|N) ", LoggerPriority::Warn);
                    ConsoleExtension::SetConsoleTextColor(ConsoleExtension::ConsoleColor::Green);
                    std::cin >> rep;
                    ConsoleExtension::SetConsoleTextColor(ConsoleExtension::ConsoleColor::Default_Color);
                    if (rep == 'O')
                    {
                        delete storage;
                        storage = new Maillage(*scene);
                        logger.Log("Storing scene finished !", LoggerPriority::Info);
                    }
                }
                else
                {

                    storage = new Maillage(*scene);
                    logger.Log("Storing scene finished !", LoggerPriority::Info);
                }
            }
            else
                logger.Log("Scene introuvable !", LoggerPriority::Error);
        }
        break;
        case 5:
        {
            if (storage != nullptr)
            {
                delete scene;
                scene = new Maillage(*storage);
                Svgfile dessinVec;

                scene->Dessiner(dessinVec, false);
                logger.Log("Restauration de la scene faite !", LoggerPriority::Info);
            }
            else
                logger.Log("Storage introuvable !", LoggerPriority::Error);
        }
        break;
        case 6:
        {
            if (scene != nullptr)
            {
                FichierRecorder fr(scene, get_file_name(fichier));
                fr.Save();
                delete scene;
                scene = nullptr;
                fichier = " ";
                logger.Log("Sauvegarde de la scene en cours terminee !", LoggerPriority::Info);
            }
            else
                logger.Log("Impossible de save une scene inexistante !", LoggerPriority::Error);
        }
        break;
        case 7:
        {
            if (scene == nullptr)
                logger.Log("Impossible de rentrer en script mode, scene inexistante !", LoggerPriority::Info);
            else
            {

                ScriptManager scriptManager(scene);
                ScriptInformation infos = scriptManager.EntrerCommande();
                ScriptInstruction scriptInstruction(scene, infos);

                scriptInstruction.Execute();
            }
        }
        break;
        case 8:
        {
            if (scene == nullptr)
                logger.Log("Impossible de charger un .script, scene inexistante !", LoggerPriority::Info);
            else
            {
                std::string sfichier;

                std::cout << "Entrer le chemin d'acces au fichier .script : ";
                ConsoleExtension::SetConsoleTextColor(ConsoleExtension::ConsoleColor::Green);
                std::cin >> sfichier;

                ConsoleExtension::SetConsoleTextColor(ConsoleExtension::ConsoleColor::Default_Color);

                ScriptLoader sloader(sfichier, scene);
                std::vector<ScriptFonction> fonctions = sloader.Load();

                ScriptMenu menu;
                menu.EnterMenu(fonctions);
            }
        }
        break;
        default:
            logger.Log("Choix du menu incorrect !", LoggerPriority::Error);
            continue;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1700));
    } while (choix != 0);

    if (scene != nullptr)
        delete scene;
    if (storage != nullptr)
        delete storage;
}