namespace Calculations
{
// Modifies the critical strice chance for the given skill.
// Returns the modifies crit chance.
int CalcSkillspecific(int currentCritChance, int skillId)
{
    // MULTIPLIKATIV KONSTANT
    if(ConfigSkills::skillMulConstant.count(skillId))
    {
        // Multiplikative Chance zu dem Skill in Map hinterlegt
        int bonus = ConfigSkills::skillMulConstant[skillId];
        currentCritChance = (currentCritChance * bonus) / 100;
    }
    else if(Configuration::disabledSkillCrit == true)
    {
        // If this skill is not set to be enabled, and all skills are meant to be disabled, the chance is set to zero here.
        currentCritChance = 0;
    }

    // MULTIPLIKATIV VARIABLE
    if(ConfigSkills::skillMulVariable.count(skillId))
    {
        // Multiplikative Chance zu dem Skill in Map hinterlegt
        int variableId = ConfigSkills::skillMulVariable[skillId];
        currentCritChance = (currentCritChance * RPG::variables[variableId]) / 100;
    }

    // ADDITIV VARIABLE
    if(ConfigSkills::skillAddVariable.count(skillId))
    {
        // Additive Chance zu dem Skill in Map hinterlegt
        int variableId = ConfigSkills::skillAddVariable[skillId];
        currentCritChance = currentCritChance + RPG::variables[variableId];
    }

    // ADDITIV KONSTANT
    if(ConfigSkills::skillAddConstant.count(skillId))
    {
        // Additive Chance zu dem Skill in Map hinterlegt
        int bonus = ConfigSkills::skillAddConstant[skillId];
        currentCritChance = currentCritChance + bonus;
    }

    return currentCritChance;
}

}
