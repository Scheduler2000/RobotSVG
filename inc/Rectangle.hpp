#if !defined(__RECTANGLE__)
#define __RECTANGLE__

#include "../inc/Forme.hpp"

namespace Rom
{
class Rectangle : public Forme
{

public:
    Rectangle(std::string const &id, std::vector<Sommet *> const &sommets, std::string const &couleur);
    ~Rectangle();

    void Dessiner(Svgfile &dessinVec, bool afficherInfo) const override;
    Coords GetCentre() const override;
};
} // namespace Rom
#endif // __RECTANGLE__
