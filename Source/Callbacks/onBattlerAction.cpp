
bool notFirstTry = false;
bool onDoBattlerAction ( RPG::Battler * battler, bool  firstTry)
{
    if(battler->isMonster())
    {
        return true;
    }

    if(notFirstTry == true)
    {
        return true;
    }

    CustomCrit::OnDoHeroAction(battler);
    notFirstTry = true;
}

bool onBattlerActionDone ( RPG::Battler * battler, bool success )
{
    if(battler->isMonster())
    {
        return true;
    }

    if(success)
    {
        notFirstTry = false;
    }
}
