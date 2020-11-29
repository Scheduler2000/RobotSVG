#if !defined(__FICHIER_RECORDER__)
#define __FICHIER_RECORDER__

#include <string>
#include <fstream>
#include <iostream>

#include "../inc/Maillage.hpp"

class FichierRecorder
{
private:
    std::ofstream m_fichier;
    Maillage *m_scene;
    void record_ground(double &largeur, double &hauteur);
    void record_decors(double largeur, double hauteur);
    void record_robots(double largeur, double hauteur);

    std::string delctype_forme(Forme *forme, double &largeur, double &hauteur) const;
    std::string delctype_composant(RobotComposant type) const;

public:
    FichierRecorder(Maillage *scene, std::string const &nomFichier);
    ~FichierRecorder();
    void Save();
};

#endif // __FICHIER_RECORDER__
