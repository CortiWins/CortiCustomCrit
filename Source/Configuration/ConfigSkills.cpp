namespace ConfigSkills
{
// SKILLSPECIFIC BONUSES
// < SkillId , Konstanter Critchancebonus additiv in % > Wertepaar welcher Skill um wieviel erh�ht wird
std::map<int,int> skillAddConstant;
// < SkillId , Konstanter Critchancebonus multiplikativ in % > Wertepaar welcher Skill um wieviel erh�ht wird
std::map<int,int> skillMulConstant;
// < SkillId , Aus Variable Critchancebonus additiv in % > Wertepaar welcher Skill um wieviel erh�ht wird
std::map<int,int> skillAddVariable;
// < SkillId , Aus Variable Critchancebonus multiplikativ in % > Wertepaar welcher Skill um wieviel erh�ht wird
std::map<int,int> skillMulVariable;
// < SkillId , Delay > Wertepaar um wieviel Frames die Animation verz�gert wird.
std::map<int,int> skillDelay;

// L�dt die Einstellungen f�r spezielle Skills
void Load()
{
    // Leeren und R�cksetzen der Maps
    skillAddConstant.clear();
    skillMulConstant.clear();
    skillAddVariable.clear();
    skillMulVariable.clear();
    skillDelay.clear();

    bool endChecking = false;
    int increasingValue = 1;

    do
    {
        // Konstruieren des Schl�ssels
        std::stringstream keyName;
        keyName << "SkillId" << (increasingValue);

        // Pr�fen ob f�r den Schl�ssel ein Wertepaar vorhanden ist
        if(configMap.count(keyName.str()))
        {
            // Wenn Paar vorhanden, Wert auslesen. Dieser entspricht der Nummer des Skills
            int skillId = (atoi(configMap[keyName.str()].c_str()));
            if((skillId>0)) // Ckecken ob die Skill-Nummer im erlaubten Bereich ist
            {
                std::stringstream debugString;
                debugString << "Skillspecific Modification: \n";
                debugString << "Skill ID: " << skillId << "\n";

                // ADDITIV CONSTANT
                {
                    std::stringstream keyNameAddCon;
                    keyNameAddCon << "SkillAddCon" << (increasingValue);
                    // Pr�fen ob f�r den Schl�ssel ein Wertepaar vorhanden ist
                    if(configMap.count(keyNameAddCon.str()))
                    {
                        // Wenn Paar vorhanden, Wert auslesen.
                        int value = (atoi(configMap[keyNameAddCon.str()].c_str()));
                        if((value>0)) // Ckecken ob die Skill-Nummer im erlaubten Bereich ist
                        {
                            // Assoziation SkillId <-> VaribleId hinterlegen
                            skillAddConstant[skillId] = value;
                            debugString << "Additive Constant: " << value << "\n";
                        }
                    }
                }

                // MULTIPLKATIV CONSTANT
                {
                    std::stringstream keyNameMulCon;
                    keyNameMulCon << "SkillMulCon" << (increasingValue);
                    // Pr�fen ob f�r den Schl�ssel ein Wertepaar vorhanden ist
                    if(configMap.count(keyNameMulCon.str()))
                    {
                        // Wenn Paar vorhanden, Wert auslesen.
                        int value = (atoi(configMap[keyNameMulCon.str()].c_str()));
                        if((value>0)) // Ckecken ob die Skill-Nummer im erlaubten Bereich ist
                        {
                            // Assoziation SkillId <-> VaribleId hinterlegen
                            skillMulConstant[skillId] = value;
                            debugString << "Multiplicative Constant: " << value << "\n";
                        }
                    }
                }



                // ADDITIV VARIABLE
                {
                    std::stringstream keyNameAddVar;
                    keyNameAddVar << "SkillAddVar" << (increasingValue);
                    // Pr�fen ob f�r den Schl�ssel ein Wertepaar vorhanden ist
                    if(configMap.count(keyNameAddVar.str()))
                    {
                        // Wenn Paar vorhanden, Wert auslesen.
                        int value = (atoi(configMap[keyNameAddVar.str()].c_str()));
                        if((value>0)) // Ckecken ob die Skill-Nummer im erlaubten Bereich ist
                        {
                            // Assoziation SkillId <-> VaribleId hinterlegen
                            skillAddVariable[skillId] = value;
                            debugString << "Additive from Variable: " << value << "\n";
                        }
                    }
                }



                // MULTIPLKATIV VARIABLE
                {
                    std::stringstream keyNameMulVar;
                    keyNameMulVar << "SkillMulVar" << (increasingValue);
                    // Pr�fen ob f�r den Schl�ssel ein Wertepaar vorhanden ist
                    if(configMap.count(keyNameMulVar.str()))
                    {
                        // Wenn Paar vorhanden, Wert auslesen.
                        int value = (atoi(configMap[keyNameMulVar.str()].c_str()));
                        if((value>0)) // Ckecken ob die Skill-Nummer im erlaubten Bereich ist
                        {
                            // Assoziation SkillId <-> VaribleId hinterlegen
                            skillMulVariable[skillId] = value;
                            debugString << "Multiplicative from Variable: " << value << "\n";
                        }
                    }
                }

                // DELAY
                {
                    std::stringstream keyNameDelay;
                    keyNameDelay << "SkillDelay" << (increasingValue);
                    // Pr�fen ob f�r den Schl�ssel ein Wertepaar vorhanden ist
                    if(configMap.count(keyNameDelay.str()))
                    {
                        // Wenn Paar vorhanden, Wert auslesen.
                        int value = (atoi(configMap[keyNameDelay.str()].c_str()));
                        if((value>0))
                        {
                            // Assoziation SkillId <-> Delay hinterlegen
                            skillDelay[skillId] = value;
                            debugString << "Delay: " << value << "\n";
                        }
                    }
                }

                if(ConfigDebug::debugParams)
                {
                    Dialog::ShowInfoBox(debugString.str(),"[CortiCustomCrit] Debug Configuration Data");
                }
            }

            increasingValue++;
        }
        else
        {
            // Wertepaar nicht vorhanden. Auslesen dieser Daten stoppen.
            endChecking = true;
        }
    }
    while(!endChecking);
}
}
