namespace CritCommands
{
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
