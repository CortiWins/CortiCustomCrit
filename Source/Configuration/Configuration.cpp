namespace Configuration
{
// Typ der Critberechnung
int critCalcType = 0;

// Determines which stat is chosen for Type 2 and Type 3 calculations
int critSource = 0;

/* Typ der Berechnung des kritischen Trefferbonuses
0 = Keine Variante. Anderen Parameter angeben.
1 = Es wird ein Prozentsatz der aktuellen ATK als Bonus hinzugefügt. Der Prozentsatz ist im Value-Parameter eingestellt.
2 = Es wird ein ATK Wert der Statkurve eines Helden entnommen. Die Datenkbank-ID des Helden ist im Value-Parameter eingestellt. */
int critAttackBonusType = 1;

// Zusatzparameter. Prozentsatz der Atk oder Helden Id
int critAttackBonusTypeValue = 50;

// Flagt, ob korrekte Werte gegeben sind
bool critAttackBonusValidSettings = false;

// CritCalcWithLevel
// 0 = keine Adaption auf Basis des Levels, für die Umrechnung in Berechnungstyp 3 wird der Heldenlevel genutzt
// 1 = der Int-Wert des Gegners wird als dessen Levelstufe angenommen
// 2 = eine Variable enthält den Level der Gegner, dieser Wert wird als Level für alle Gegner angenommen
int critCalcWithLevel = 0;

// Index der Variable für Type2 der Levelberechnung
int critCalcWithLevelVariable = 0;

// Wenn dieser Parameter gesetzt ist, können kritische Treffer nur gegen Feinde ausgeführt werden
bool critCalcOnHerosDisabled=false;

// Tells if critical strikes are disabled for all skills except those especially configured.
bool disabledSkillCrit = false;

// Bestimmt, welcher Levelunterschied bei defensiven Sprüchen angenommen wird.
// 0 = Heldenlevel
// 1 = Mittelwert der Monster oder aus Variable, je nach Setting des Leveleinflusses
int critCalcOnHerosLevel=0;




void Load()
{
    // Kritberechnungstyp
    if(configMap.count("CritCalcType"))
    {
        critCalcType = (atoi(configMap["CritCalcType"].c_str()));
        if(critCalcType<=0 || critCalcType > 5 )
        {
            Dialog::ShowInfoBox(critCalcType, "Invalid CritCalcType");
        }
    }

    // Critical Strike source stat:
    if(configMap.count("CritSource"))
    {
        critSource = (atoi(configMap["CritSource"].c_str()));
        if(critCalcType<0 || critCalcType > 1 )
        {
            Dialog::ShowInfoBox(critCalcType, "Invalid CritSource");
        }
    }

    // Angenommen Parameter sind in Ordnung
    critAttackBonusValidSettings = true;
    if(configMap.count("CritAttackBonusType"))
    {
        critAttackBonusType = (atoi(configMap["CritAttackBonusType"].c_str()));
        if(critAttackBonusType<=0 || critAttackBonusType > 2 )
        {
            Dialog::ShowInfoBox(critAttackBonusType, "Invalid CritAttackBonusType");
            critAttackBonusValidSettings = false; // Settings nicht in Ordnung
        }
    }

    ConfigDebug::ShowDebugValue(critAttackBonusType, "CritAttackBonusType");

    if(configMap.count("CritAttackBonusTypeValue"))
    {
        critAttackBonusTypeValue = (atoi(configMap["CritAttackBonusTypeValue"].c_str()));
        if(critAttackBonusTypeValue<=0)
        {
            Dialog::ShowInfoBox(critAttackBonusTypeValue, "Invalid CritAttackBonusTypeValue");
            critAttackBonusValidSettings = false; // Settings nicht in Ordnung
        }

        // Anzahl Helden in der Datenbank
        int numberOfActors= RPG::actors.count();

        if(critAttackBonusType==2)
        {
            if(critAttackBonusTypeValue>numberOfActors)
            {
                Dialog::ShowInfoBox("Referenced Hero exceeds HeroDatabaseSize", "Invalid CritAttackBonusTypeValue");
                critAttackBonusValidSettings = false; // Settings nicht in Ordnung
            }
        }
    }

    ConfigDebug::ShowDebugValue(critAttackBonusTypeValue, "CritAttackBonusTypeValue");


    // Leveladaptives System
    /* Parameter:
    0 = keine Adaption auf Basis des Levels, für die Umrechnung in Berechnungstyp 3 wird der Heldenlevel genutzt
    1= der Int-Wert des Gegners wird als dessen Levelstufe angenommen.
    2 = eine Variable enthält den Level der Gegner, dieser Wert wird als Level für alle Gegner angenommen*/
    if(configMap.count("CritCalcWithLevel"))
    {
        critCalcWithLevel = (atoi(configMap["CritCalcWithLevel"].c_str()));
        if(critCalcWithLevel<0 || critCalcWithLevel > 2 )
        {
            Dialog::ShowInfoBox(critCalcWithLevel, "Invalid CritCalcWithLevel");
        }
    }

    ConfigDebug::ShowDebugValue(critCalcWithLevel, "CritCalcWithLevel");


    if(critCalcWithLevel==2) // Nur wenn Typ2 der Levelanpassung -> Quellvariable einlesen...
    {
        // ...Variable, die den Feindlevel enthält.
        if(configMap.count("CritCalcWithLevelVariable"))
        {
            critCalcWithLevelVariable = (atoi(configMap["CritCalcWithLevelVariable"].c_str()));
            if(critCalcWithLevelVariable<=0)
            {
                Dialog::ShowInfoBox(critCalcWithLevelVariable, "Invalid CritCalcWithLevelVariable");
            }
        }

        ConfigDebug::ShowDebugValue(critCalcWithLevelVariable, "CritCalcWithLevelVariable");
    }

    // Wenn dieser Parameter gesetzt ist, können kritische Treffer nur gegen Feinde ausgeführt werden
    if(configMap.count("CritCalcOnHerosDisabled"))
    {
        int temp = (atoi(configMap["CritCalcOnHerosDisabled"].c_str()));
        critCalcOnHerosDisabled = temp > 0 ? true :false;
    }

    ConfigDebug::ShowDebugValue(critCalcOnHerosDisabled ? "ON" : "OFF", "CritCalcOnHerosDisabled");

    // Wenn dieser Parameter gesetzt ist, können kritische Treffer nur gegen Feinde ausgeführt werden
    if(configMap.count("CritCalcOnSkillsDisabled"))
    {
        int temp = (atoi(configMap["CritCalcOnSkillsDisabled"].c_str()));
        disabledSkillCrit = temp > 0 ? true :false;
    }

    ConfigDebug::ShowDebugValue(disabledSkillCrit ? "ON" : "OFF", "CritCalcOnSkillsDisabled");

    // Bestimmt, welcher Levelunterschied bei defensiven Sprüchen angenommen wird.
    /*  0 = Heldenlevel
        1 = Mittelwert der Monster oder aus Variable, je nach Setting des Leveleinflusses */
    // ...Variable, die den Feindlevel enthält.
    if(configMap.count("CritCalcOnHerosLevel"))
    {
        critCalcOnHerosLevel = (atoi(configMap["CritCalcOnHerosLevel"].c_str()));
        if(critCalcOnHerosLevel<0)
        {
            Dialog::ShowInfoBox(critCalcOnHerosLevel, "Invalid CritCalcOnHerosLevel");
        }
    }

    ConfigDebug::ShowDebugValue(critCalcOnHerosLevel, "CritCalcOnHerosLevel");

}
}
