namespace CritCalcType3
{
int GetCritStat(RPG::Battler *currentBattler)
{
    if(Configuration::critSource ==1)
    {
        return currentBattler->getAgility();
    }
    else
    {
        return currentBattler->getIntelligence();
    }
}

// Typ 3 -> Der Intwert ist ein Ratingwert, der in eine Chance umgewandelt wird.
int CalculateCritByRating(RPG::Battler *currentBattler)
{
    // Kritchance% = (Rating des Helden * 100 )  / Levelkonstante[Kampfstufe]
    int currentRating =GetCritStat(currentBattler);
    int currentLevel = LevelInfluence::GetLevel(currentBattler); // Rating
    int hpMaxAkaCoefficient = RPG::dbActors[ConfigType3::ratingCoefficientHeroId]->maxHp[currentLevel];
    currentRating *=100;
    int currentCritChance = currentRating / hpMaxAkaCoefficient;

    ConfigDebug::DebugAdeptedCritVariable(currentCritChance);
    ConfigDebug::DebugRawCritVariable(currentCritChance);
    return currentCritChance;
}

}
