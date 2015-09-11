namespace CritCalcType1
{
// Typ 1 ->Helden haben eine vom Int-Wert unabh�ngige Kritchance
int CalculateCritFix(RPG::Battler *currentBattler)
{
    // Helden haben auf jeden Fall Defaultchance
    int currentCritChance = ConfigType1::parDefaultCritchance;
    // Pr�fen, ob der Held f�r eine Variablenquelle registriert ist
    if(ConfigType1::parIdAndVariable.count(currentBattler->id))
    {
        int varReference = ConfigType1::parIdAndVariable[currentBattler->id];
        currentCritChance = RPG::variables[varReference];
    }
    else
    {   // Pr�fen, ob der Held f�r einen eigenen Fixwert besitzt
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
