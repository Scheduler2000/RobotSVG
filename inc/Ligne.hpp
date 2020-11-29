#if !defined(__LIGNE__)
#define __LIGNE__

#include "../inc/Forme.hpp"

class Ligne : public Forme
{
public:
    Ligne(std::string const &id, std::vector<Sommet *> const &sommets, std::string const &couleur);
    ~Ligne();

    void Dessiner(Svgfile &dessinVec, bool afficherInfo) const override;
    Coords GetCentre() const override;
};

#endif // __LIGNE__
