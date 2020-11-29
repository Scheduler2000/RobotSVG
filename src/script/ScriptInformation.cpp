#include "../inc/ScriptInformation.hpp"

ScriptInformation::ScriptInformation(Element *target, CommandeType action, double valeur)
    : m_target(target), m_action(action), m_valeur(valeur) {}

Element *ScriptInformation::ObtenirTarget() const { return m_target; }

CommandeType ScriptInformation::ObtenirAction() const { return m_action; }

double ScriptInformation::ObtenirValeur() const { return m_valeur; }