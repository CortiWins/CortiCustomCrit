
bool onComment(
    const char *text,
    const RPG::ParsedCommentData *parsedData,
    RPG::EventScriptLine *nextScriptLine,
    RPG::EventScriptData *scriptData,
    int	eventId,
    int pageId,
    int lineId,
    int *nextLineId)
{
    if(!strcmp(parsedData->command, "ccrit_getstatus"))
    {
        CritCommands::GetStatus(parsedData);
        return false;
    }
    else if(!strcmp(parsedData->command, "ccrit_resetstatus"))
    {
        CritCommands::ResetStatus(parsedData);
        return false;
    }
    else if(!strcmp(parsedData->command, "ccrit_skill_addcon"))
    {
        CritCommands::AddSkillData(parsedData, 1);
        return false;
    }
    else if(!strcmp(parsedData->command, "ccrit_skill_addvar"))
    {
        CritCommands::AddSkillData(parsedData, 2);
        return false;
    }
    else if(!strcmp(parsedData->command, "ccrit_skill_mulcon"))
    {
        CritCommands::AddSkillData(parsedData, 3);
        return false;
    }
    else if(!strcmp(parsedData->command, "ccrit_skill_mulvar"))
    {
        CritCommands::AddSkillData(parsedData, 4);
        return false;
    }
    else if(!strcmp(parsedData->command, "ccrit_skill_delay"))
    {
        CritCommands::AddSkillData(parsedData, 5);
        return false;
    }
    return true;
}
