#if !defined(__ROBOT_BUILDER__)
#define __ROBOT_BUILDER__
#include <map>
#include <string>
#include "../inc/Forme.hpp"
#include "../inc/Robot.hpp"

class RobotBuilder
{
private:
    std::map<RobotComposant, Forme *> m_composants;
    std::vector<Forme *> m_visage;

public:
    RobotBuilder();
    ~RobotBuilder();
    RobotBuilder AjouterComposant(Forme *forme, RobotComposant partieDuCorps);
    RobotBuilder AjouterVisage(Forme *forme);
    Robot *Build(std::string const &nom, std::string const &mood);
};

#endif // __ROBOT_BUILDER__
