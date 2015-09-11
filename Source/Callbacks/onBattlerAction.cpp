bool onBattlerActionDone ( RPG::Battler * battler, bool success )
{
    if(battler->isMonster())
    {
        return true;
    }

    if(success)
    {
        CustomCrit::OnDoHeroAction(battler);
    }
}
