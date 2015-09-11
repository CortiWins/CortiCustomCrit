namespace CritCalcType1
{
// Typ 1 ->Helden haben eine vom Int-Wert unabhängige Kritchance
int CalculateCritFix(RPG::Battler *currentBattler)
{
    // Helden haben auf jeden Fall Defaultchance
    int currentCritChance = ConfigType1::parDefaultCritchance;
    // Prüfen, ob der Held für eine Variablenquelle registriert ist
    if(ConfigType1::parIdAndVariable.count(currentBattler->id))
    {
        int varReference = ConfigType1::parIdAndVariable[currentBattler->id];
        currentCritChance = RPG::variables[varReference];
    }
    else
    {   // Prüfen, ob der Held für einen eigenen Fixwert besitzt
        if(ConfigType1::parIdAndCritFix.count(currentBattler->id))
        {
            currentCritChance = ConfigType1::parIdAndCritFix[currentBattler->id];
        }
    }

    ConfigDebug::DebugRawCritVariable(currentCritChance);

    //Grundcritwert vorhanden, nun im Falle eins Levelunterschiedes den Wert anpassen
    currentCritChance = LevelInfluence::AdaptToLevel(currentCritChance, currentBattler);

    ConfigDebug::DebugAdeptedCritVariable(currentCritChance);

    return currentCritChance;
}
}
