#if !defined(__CERCLE__)
#define __CERCLE__

#include "../inc/Forme.hpp"

class Cercle : public Forme
{

private:
    int m_rayon;
    bool m_fill;

public:
    Cercle(std::string const &id, std::vector<Sommet *> const &centre, int rayon, bool fill, std::string const &couleur);
    ~Cercle();

    void Dessiner(Svgfile &dessinVec, bool afficherInfo) const override;
    Coords GetCentre() const override;
    int GetRayon() const;
};

#endif // __CERCLE__
