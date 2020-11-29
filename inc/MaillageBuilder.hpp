#if !defined(__MAILLAGE_BUILDER__)
#define __MAILLAGE_BUILDER__

#include <vector>
#include <string>
#include "../inc/Robot.hpp"
#include "../inc/Maillage.hpp"

class MaillageBuilder
{
private:
    std::vector<Robot *> m_robots;
    std::vector<Forme *> m_decors;

public:
    MaillageBuilder();
    ~MaillageBuilder();

    MaillageBuilder AjouterRobot(Robot *robot);
    MaillageBuilder AjouterDecor(Forme *decor);
    Maillage Build(double largeur, double hauteur);
};

#endif // __MAILLAGE_BUILDER__
