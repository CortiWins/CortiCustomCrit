namespace CritCommands
{
// 1 @ccrit_skill_addcon
// 2 @ccrit_skill_addvar
// 3 @ccrit_skill_mulcon
// 4 @ccrit_skill_mulvar
// 5 @ccrit_skill_delay
void AddSkillData(const RPG::ParsedCommentData *parsedData, int type)
{
    if(parsedData->parametersCount != 2)
    {
        Dialog::ShowInfoBox(parsedData->command,"[CortiCustomCrit] Command needs 2 parameters:");
        return;
    }

    // Parameter 1 the ID of the skill
    int skillId = ((int)parsedData->parameters[0].number );
    // Parameter 2 is CritValue, MultiplicationFactor, DelayFrames according to command
    int value = (int)parsedData->parameters[1].number;

    if(type == 1) // @ccrit_skill_addcon
    {
        ConfigSkills::skillAddConstant[skillId] = value;
    }
    else if(type == 2) // @ccrit_skill_addvar
    {
        ConfigSkills::skillAddVariable[skillId] = value;
    }
    else if(type == 3) //  @ccrit_skill_mulcon
    {
        ConfigSkills::skillMulConstant[skillId] = value;
    }
    else if(type == 4) // @ccrit_skill_mulvar
    {
        ConfigSkills::skillMulVariable[skillId] = value;
    }
    else if(type == 5) // @ccrit_skill_delay
    {
        ConfigSkills::skillDelay[skillId] = value;
    }
}

void GetStatus(const RPG::ParsedCommentData *parsedData)
{
    if(parsedData->parametersCount != 2)
    {
        Dialog::ShowInfoBox("ccrit_getstatus: Bad number of parameters.","[CortiCustomCrit] Comment Command Error");
        return;
    }

    // Parameter 1 ist die Datenbank-ID des Helden
    int databaseId = ((int)parsedData->parameters[0].number );
    // Parameter 2 ist die ID des Switches in die geschrieben wird
    int switchId = (int)parsedData->parameters[1].number;

    if( (databaseId < 1) || (databaseId >= RPG::actors.count()) )
    {
        Dialog::ShowInfoBox("ccrit_getstatus: Bad number hero id.","[CortiCustomCrit] Comment Command Error");
        return;
    }

    if( switchId < 1 )
    {
        Dialog::ShowInfoBox("ccrit_getstatus: Bad number switches id.","[CortiCustomCrit] Comment Command Error");
        return;
    }

    // Write crit-status to switch.
    RPG::switches[switchId] = HeroAttackBonus::GetAtkStatus(databaseId);
}

void ResetStatus(const RPG::ParsedCommentData *parsedData)
{
    if(parsedData->parametersCount != 1)
    {
        Dialog::ShowInfoBox("ccrit_resetstatus: Bad number of parameters.","[CortiCustomCrit] Comment Command Error");
        return;
    }

    // Parameter 1 ist die Datenbank-ID des Helden
    int databaseId = ((int)parsedData->parameters[0].number );

    if( (databaseId < 1) || (databaseId >= RPG::actors.count()) )
    {
        Dialog::ShowInfoBox("ccrit_getstatus: Bad number hero id.","[CortiCustomCrit] Comment Command Error");
        return;
    }

    HeroAttackBonus::ResetCritBonus(databaseId);
}
}
