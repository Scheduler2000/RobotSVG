#if !defined(__FORME__)
#define __FORME__

#include <vector>
#include <string>
#include "../inc/Element.hpp"
#include "../inc/Sommet.hpp"
#include "../inc/Couleur.hpp"
#include "../inc/SvgFile.hpp"

enum class FormeType
{
	Cercle,
	Ellipse,
	Rectangle,
	Ligne,
	Triangle
};

class Forme : public Element
{
private:
	std::string m_id;
	FormeType m_type;

protected:
	std::vector<Sommet *> _sommets;
	std::string _couleur;

public:
	Forme(std::string const &id, std::vector<Sommet *> const &sommets, std::string const &couleur, FormeType type);
	virtual ~Forme();

	virtual void Dessiner(Svgfile &dessinVec, bool afficherInfo) const = 0;
	virtual Coords GetCentre() const = 0;

	void Deplacer(double valeur);
	void Rotate(double angle);

	std::vector<Sommet *> GetSommets() const;
	std::string GetId() const;
	FormeType GetType() const;
	std::string GetCouleur();
};

#endif // __FORME__
