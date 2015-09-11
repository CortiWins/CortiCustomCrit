
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
    return true;
}
