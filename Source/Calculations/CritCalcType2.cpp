namespace CritCalcType2
{
// Typ 2 ->Helden haben den Int-Wert als Kritchance
int CalculateCritRaw(RPG::Battler *currentBattler)
{
    // Der Critwert des Helden ist 1:1 der Int-Wert. Bei > 100 wird 100 angenommen.
    int currentCritChance = currentBattler->getIntelligence();
    if(currentCritChance>100) { currentCritChance = 100; }

    ConfigDebug::DebugRawCritVariable(currentCritChance);

    //Grundcritwert vorhanden, nun im Falle eins Levelunterschiedes den Wert anpassen
    currentCritChance = LevelInfluence::AdaptToLevel(currentCritChance, currentBattler);

    ConfigDebug::DebugAdeptedCritVariable(currentCritChance);
    return currentCritChance;
}

}
