#include "../inc/RobotBuilder.hpp"

RobotBuilder::RobotBuilder() {}

RobotBuilder::~RobotBuilder() {}

RobotBuilder RobotBuilder::AjouterComposant(Forme *forme, RobotComposant partieDuCorps)
{
    this->m_composants.insert(std::pair<RobotComposant, Forme *>(partieDuCorps, forme));
    return *(this);
}

RobotBuilder RobotBuilder::AjouterVisage(Forme *forme)
{
    this->m_visage.push_back(forme);
    return *this;
}

Robot *RobotBuilder::Build(std::string const &nom, std::string const &mood)
{
    return new Robot(nom, mood, m_composants, m_visage);
}