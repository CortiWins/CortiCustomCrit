namespace CustomCrit
{
// Function Pointer to chosen CritCalculation.
int (*critFunction)(RPG::Battler*);

// Returns if the action can crit.
bool CanCrit(RPG::Battler *battler)
{
    bool calcCrit = false;
    if(battler->action->kind == RPG::AK_SKILL)
    {
        // Skills can be critical.
        calcCrit = true;

        // Critical strikes on healing skills can be disabled.
        if(Configuration::critCalcOnHerosDisabled && ((battler->action->target == RPG::TARGET_ALL_ACTORS) || (battler->action->target == RPG::TARGET_ACTOR)) )
        {
            calcCrit = false;
        }
    }
    else if(battler->action->kind == RPG::AK_BASIC)
    {
        // Weapon attacks can crit.
        if(battler->action->basicActionId == RPG::BA_ATTACK || battler->action->basicActionId == RPG::BA_DOUBLE_ATTACK)
        {
            calcCrit = true;
        }
    }

    return calcCrit;
}

int GetZero(RPG::Battler *battler)
{
    return 0;
}

// Happens when a hero does an action.
void OnDoHeroAction ( RPG::Battler *battler )
{
    // Check if action can crit.
    if(CanCrit(battler))
    {
        ConfigDebug::DebugHeroIdToVariable(battler->id);

        // Calling the configured crit calculation.
        int currentCritChance = critFunction(battler);

        // When using skills, calculate skillspecific factors.
        if((battler->action->kind == RPG::AK_SKILL))
        {
            currentCritChance = Calculations::CalcSkillspecific(currentCritChance, battler->action->skillId);
        }

         // Roll the dice and compare to calculated crit value.
        int rnd = RPG::getDiceRoll(100);
        if(rnd<=currentCritChance)
        {
            // Action is critical, so set Attack bonus for battler.
            HeroAttackBonus::AddCritBonus(battler->id);
            // Add Splash-Effect to the action target.
            DrawCritSplash::AddEffects(battler->action);
        }
        else
        {

            // Action did not roll crit, so reset crit status.
            HeroAttackBonus::ResetCritBonus(battler->id);
        }
    }
    else
    {
        // Action can't crit, so reset crit status.
        HeroAttackBonus::ResetCritBonus(battler->id);
    }
}

// Passiert wenn das Spiel resettet wurde im Testmodus.
// Unterschied zwischen OnResetGame und OnSceneChange:
// in OnResetGame wird nur das Kritbonus-Flag resettet, das reduzieren der Attack-Werte passiert durch den Spielreset von selbst.
void OnResetGame()
{
    HeroAttackBonus::OnResetGame();
    DrawCritSplash::ResetFrames();
}

// Aufgerufen bei Szenenwechsel zum Kampf oder vom Kampf weg. In dem Fall alle Kritboni entfernen und Animationen abbrechen
void OnSceneChange()
{
    HeroAttackBonus::OnSceneChange();
    DrawCritSplash::ResetFrames();
}

}
