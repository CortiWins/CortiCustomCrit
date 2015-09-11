namespace ConfigType1
{
// Defaultcritchance für Helden, die keine Customchance bekommen haben
int parDefaultCritchance = 20;
// Mapping Helden-ID und Fixer Critwert
std::map<int, int> parIdAndCritFix;
// Mapping Helden-ID und Quellvarible für Critwert
std::map<int, int> parIdAndVariable;

// Laden der Einstellungen für Kritberechnung Typ 1
// Typ 1 ->Helden haben eine vom Int-Wert unabhängige Kritchance
void Load()
{
    parDefaultCritchance = 20;
    if(configMap.count("t1CritChanceDefault"))
    {
        parDefaultCritchance = (atoi(configMap["t1CritChanceDefault"].c_str()));
        if(parDefaultCritchance<=0 || parDefaultCritchance > 100 )
        {
            Dialog::ShowInfoBox(parDefaultCritchance, "Invalid t1CritChanceDefault");
        }
        else
        {
            ConfigDebug::ShowDebugValue(parDefaultCritchance, "t1CritChanceDefault");
        }
    }

    bool stopRead = false;
    int increasingValue = 1;
    while(!stopRead)
    {
        std::stringstream keyName;
        keyName << "t1HeroCritHero_" << (increasingValue) << "_Id";

        if(configMap.count(keyName.str()))
        {
            // Weiterer Helden-ID Eintrag vorhanden
            int heroId = (atoi(configMap[keyName.str()].c_str()));
            ConfigDebug::ShowDebugValue(heroId, keyName.str());

            // Nun checken, ob dazu eine Referenzvariable vorhanden ist.
            std::stringstream keyNameVar;
            keyNameVar << "t1HeroCritHero_" << (increasingValue) << "_Variable";
            if(configMap.count(keyNameVar.str()))
            {
                // Referenzvariable vorhanden
                int var = (atoi(configMap[keyNameVar.str()].c_str()));
                // Wertepaar <HeroId,VariableId> eintragen
                parIdAndVariable[heroId] = var;
                ConfigDebug::ShowDebugValue(var, keyNameVar.str());
            }
            else
            {
                // Keine Referenzvariable, schauen nach Fixwert
                std::stringstream keyNameFix;
                keyNameFix << "t1HeroCritHero_" << (increasingValue) << "_FixCrit";
                if(configMap.count(keyNameFix.str()))
                {
                    // Fixwert vorhanden
                    int fix = (atoi(configMap[keyNameFix.str()].c_str()));
                    ConfigDebug::ShowDebugValue(fix, keyNameFix.str());

                    // Wertepaar <HeroId,FixValue> eintragen
                    parIdAndCritFix[heroId] = fix;
                }
                else
                {
                    // Kein Fixwert ... Fehler anzeigen
                    Dialog::ShowInfoBox(heroId,"Hero with this ID no crit configs set...");
                }
            }
        }
        else
        {
            // Schleife abbrechen
            stopRead = true;
        }

        increasingValue++;
    }
}
}
