#if !defined(__ROBOT__)
#define __ROBOT__
#include "../inc/Forme.hpp"
#include "../inc/SvgFile.hpp"
#include "../inc/Element.hpp"
#include <string>
#include <map>

enum class RobotComposant
{
    Null,
    Tete,
    BrasDroit,
    BrasGauche,
    MainDroite,
    MainGauche,
    HautDuCorps,
    JambeDroite,
    JambeGauche
};

/*Utiliser RobotBuilder (desing pattern) pour instancier l'objet */
class Robot : public Element
{
private:
    std::string m_nom;
    std::string m_mood;
    std::map<RobotComposant, Forme *> m_composants;
    std::vector<Forme *> m_visage;

public:
    Robot(std::string const &nom, std::string const &mood, std::map<RobotComposant, Forme *> &composants, std::vector<Forme *> &visage);
    ~Robot();

    std::string ObtenirNom() const;
    std::string ObtenirMood() const;
    Coords ObtenirCentreRobot() const;
    Forme *ObtenirForme(RobotComposant partieDuCorps) const;
    Forme *ObtenirForme(std::string const &id) const;
    const std::map<RobotComposant, Forme *> &ObtenirComposants() const;
    const std::vector<Forme *> &ObtenirVisage() const;
    void Construire(Svgfile &dessinVec, bool afficherInfo) const;
    void Deplacer(double valeur);
};

#endif // __ROBOT__
