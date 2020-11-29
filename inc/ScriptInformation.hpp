#if !defined(__SCRIPT_INFORMATION__)
#define __SCRIPT_INFORMATION__

#include <string>
#include "../inc/Element.hpp"
#include "../inc/CommandeType.hpp"

class ScriptInformation
{
private:
    Element *m_target;
    CommandeType m_action;
    double m_valeur;

public:
    ScriptInformation(Element *target, CommandeType action, double valeur);

    Element *ObtenirTarget() const;
    CommandeType ObtenirAction() const;
    double ObtenirValeur() const;
};

#endif // __SCRIPT_INFORMATION__
