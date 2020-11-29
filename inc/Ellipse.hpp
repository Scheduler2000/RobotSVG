#if !defined(__ELLIPSE__)
#define __ELLIPSE__

#include "../inc/Forme.hpp"

namespace rom
{
class Ellipse : public Forme
{
private:
    int m_radiusX;
    int m_radiusY;

public:
    Ellipse(std::string const &id, std::vector<Sommet *> const &sommets, int rx, int ry, std::string const &couleur);
    ~Ellipse();

    void Dessiner(Svgfile &dessinVec, bool afficherInfo) const override;
    Coords GetCentre() const override;
    int GetRadiusX() const;
    int GetRadiusY() const;
};
} // namespace rom
#endif // __ELLIPSE__
