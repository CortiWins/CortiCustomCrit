// Called after a battler was drawn (or supposed to be drawn)
bool onBattlerDrawn ( RPG::Battler *battler, bool isMonster, int id ) // id is Zero-based
{
    if ( isMonster )
    {
        DrawCritSplash::OnMonsterDrawn(id, battler);
        return true;
    }
    else
    {
        DrawCritSplash::OnHeroDrawn(id, battler);
        return true;
    }
}
