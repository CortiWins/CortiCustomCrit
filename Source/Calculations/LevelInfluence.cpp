namespace LevelInfluence
{

int GetMonsterIntellect(bool useGroup, int targetId)
{
    int currentIntellect = -1;
    // Intwert des Zielmonsters auslesen
    if(!useGroup)
    {
        if(RPG::monsters[targetId] != NULL)
        {
            currentIntellect = RPG::monsters[targetId]->getIntelligence();
        }
    }
    else // Mittelwert des Intwertes der Gegnergruppe bilden
    {
        int sumOfMonsters = 0;
        int sumOfIntellect = 0;

        for(int iMonsters = 0; iMonsters < 8; iMonsters++) // Alle Monsterslots
        {
            if(RPG::monsters[iMonsters] != NULL) // Davon existierende
            {
                if(RPG::monsters[iMonsters]->hp>0) // Davon lebende
                {
                    if(RPG::monsters[iMonsters]->notHidden) // Davon im Kampf aktive
                    {
                        int intelligence = RPG::monsters[iMonsters]->getIntelligence();
                        if(intelligence>99) // Warnung wenn Intwert zu hoch...
                        {
                            std::stringstream outputStr;
                            outputStr << "Warning: Int-Value is of monster " << RPG::monsters[iMonsters]->getName() << " is at value " << intelligence << ". Set this to valid value 1 - 99";

                            Dialog::ShowInfoBox(outputStr.str(),"CortiCustomCrit");
                        }
                        else
                        {
                            // Aufsummieren und zählen
                            sumOfIntellect += intelligence;
                            sumOfMonsters++;
                        }
                    }
                }
            }
        }

        if(sumOfMonsters>0) // Wenn Werte von Monstern vorhanden waren ...>Mittelwert bilden.
        {
            currentIntellect = sumOfIntellect / sumOfMonsters;
        }
    }

    return currentIntellect;
}

// Berechnet den Level des Zauberzieles
int GetLevel(RPG::Battler * currentBattler)
{
    // Helper::ShowInfoBoxString("GetLevel","CortiCustomCrit");
    RPG::Actor* actPtr = (RPG::Actor*)currentBattler;
    // Level per Default auf den Heldenlevel setzen
    int currentLevel = actPtr->level;

    /* CalcWithLevel Typ Parameter:
            0 = keine Adaption auf Basis des Levels, für die Umrechnung in Berechnungstyp 3 wird der Heldenlevel genutzt
            1 = der Int-Wert des Gegners wird als dessen Levelstufe angenommen.
            2 = eine Variable enthält den Level der Gegner, dieser Wert wird als Level für alle Gegner angenommen */
    if(Configuration::critCalcWithLevel==0)
    {
        // Keine weitere Berechnung, Heldenlevel = Kampflevel
        ConfigDebug::DebugTargetLevelVariable(currentLevel);
        return currentLevel;
    }
    else if(Configuration::critCalcWithLevel==2)
    {
        // Kampflevel aus Variable

        // Wenn CalcWithLevel=2, dann 256: Id der Variable, die die Gegnerlevel enthält
        // CritCalcWithLevelVariable=256*/
        currentLevel = RPG::variables[Configuration::critCalcWithLevelVariable];

        ConfigDebug::DebugTargetLevelVariable(currentLevel);
        return currentLevel;
    }

    // Wenn nicht die beiden Varianten, dann Kampflevel aus Intwerten der Monster
    if(currentBattler->action->target == RPG::TARGET_MONSTER)
    {
        // Intwert des Zielmonsters hinterlegen
        int currentIntellect = GetMonsterIntellect(false, currentBattler->action->targetId);
        // Wenn ein valider MonsterInt-Wert gefunden wurde, dann den übernehmen
        if(currentIntellect != -1)
        {
            currentLevel = currentIntellect;
        }

        ConfigDebug::DebugTargetLevelVariable(currentLevel);
        return currentLevel;
    }
    else if(currentBattler->action->target == RPG::TARGET_ALL_MONSTERS)
    {
        // Int-Mittelwert der Monstergruppe hinterlegen
        int currentIntellect = GetMonsterIntellect(true, currentBattler->action->targetId);
        // Wenn ein valider MonsterInt-Wert gefunden wurde, dann den übernehmen
        if(currentIntellect != -1)
        {
            currentLevel = currentIntellect;
        }

        ConfigDebug::DebugTargetLevelVariable(currentLevel);
        return currentLevel;
    }
    else if(currentBattler->action->target == RPG::TARGET_ALL_ACTORS || currentBattler->action->target == RPG::TARGET_ACTOR)
    {
        // CritCalcOnHerosLevel: Bestimmt, welcher Levelunterschied bei defensiven Sprüchen angenommen wird.
        // 0 = Heldenlevel
        // 1 = Mittelwert der Monster oder aus Variable, je nach Setting des Leveleinflusses
        if(Configuration::critCalcOnHerosLevel==1)
        {
            // Int-Mittelwert der Monstergruppe hinterlegen
            int currentIntellect = GetMonsterIntellect(true, currentBattler->action->targetId);
            // Wenn ein valider MonsterInt-Wert gefunden wurde, dann den übernehmen
            if(currentIntellect != -1)
            {
                currentLevel = currentIntellect;
            }
        }

        ConfigDebug::DebugTargetLevelVariable(currentLevel);
        return currentLevel;
    }
}

// Verändert die Kritische Trefferchance auf Grundlage des Levelunterschiedes zwischen Helden und Ziel.
int AdaptToLevel(int currentCritChance, RPG::Battler *currentBattler)
{
    // critCalcWithLevel = Art der Levelanpassung
    if(Configuration::critCalcWithLevel == 0)
    {
        // 0 = keine Adaption auf Basis des Levels, für die Umrechnung in Berechnungstyp 3 wird der Heldenlevel genutzt
        return currentCritChance;
    }
    else if(Configuration::critCalcWithLevel == 1 || Configuration::critCalcWithLevel == 2)
    {
        // 1 = der Int-Wert des Gegners wird als dessen Levelstufe angenommen oder aber der Wert aus einer Variable
        // currentCritChance = aktuelle Kritwert
        RPG::Actor* actPtr = (RPG::Actor*)currentBattler;
        // Ziellevel berechnen -> currentLevel
        int currentLevel = GetLevel(currentBattler); // AdaptToLevel
        int differenceLevel = (actPtr->level) - currentLevel;

        if(differenceLevel>0) // Positive Werte -> Gegner höherlevelig
        {
            // je Level um 10% erhöhen
            currentCritChance += (currentCritChance * (differenceLevel*10))/100;
        }
        else if(differenceLevel<0) // Negative Werte -> Gegner höherlevelig
        {
            // je Level um 10% reduzieren
            currentCritChance += (currentCritChance * (differenceLevel*5))/100;
            if(currentCritChance<0)
            {
                currentCritChance = 0;    // Wenn auf kleiner Null reduziert, dann  Nullsetzen
            }
        }

        return currentCritChance;
    }
}
}
