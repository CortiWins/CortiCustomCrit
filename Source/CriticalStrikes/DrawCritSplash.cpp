namespace DrawCritSplash
{
// Framezähler für die CRIT!-Animation auf Monstern
int monsterCritFrames[8] = { 0,0,0,0,0,0,0,0};
// Framezähler für die CRIT!-Animation auf Helden
int heroCritFrames[4] = { 0,0,0,0};

// Wenn Monster gezeichnet wurde. Anzeige der CRIT!-Animation auf Monstern.
void OnMonsterDrawn(int id, RPG::Battler *batPtr) // zB Group ID
{
    if(monsterCritFrames[id]<70)
    {
        const int offsetX = 16;
        const int offsetY = 16;

        if(monsterCritFrames[id]<20)
        {
            // erste 20 Frames: nix
        }
        else if(monsterCritFrames[id]<40) // 20 bis 39
        {
            // weitere 20 Frames: einblenden
            SplashEffect::Draw(255 * (monsterCritFrames[id]-20)/20, batPtr->x + offsetX,  batPtr->y + offsetY );
        }
        else if(monsterCritFrames[id]<50) // 40 bis 49
        {
            SplashEffect::Draw(255 , batPtr->x + offsetX,  batPtr->y + offsetY );
        }
        else if(monsterCritFrames[id]<70) // 50 bis 70
        {
            SplashEffect::Draw( 255 - (255 * (monsterCritFrames[id]-50)/20) , batPtr->x + offsetX,  batPtr->y + offsetY );
        }

        monsterCritFrames[id]++;
    }
}

// Wenn Helden gezeichnet wurde. Anzeige der CRIT!-Animation auf Helden.
void OnHeroDrawn(int databaseId, RPG::Battler *batPtr)
{
    int index = RPG::getPartyIndex(databaseId);
    if(index == -1)
    {
        Dialog::ShowInfoBox(databaseId,"HeroDrawn..index -1");
        return;
    }

    if(heroCritFrames[index]< 70)
    {
        if(heroCritFrames[index]<20)
        {
            // erste 20 Frames: nix
        }
        else if(heroCritFrames[index]<40) // 20 bis 40
        {
            // weitere 20 Frames: einblenden
            SplashEffect::Draw(255 * (heroCritFrames[index]-20)/20 , batPtr->x,  batPtr->y );
        }
        else if(heroCritFrames[index]<50) // 40 bis 49
        {
            SplashEffect::Draw(255 , batPtr->x,  batPtr->y );
        }
        else if(heroCritFrames[index]<70) // 50 bis 69
        {
            // Ausfaden:
            // Frames Minus 50 bei Werten zwischen 50 und 69 ergibt 0 bis 19.
            // 255 * (0 bis 19) / 20 bedeutet also von 0 bis fast 100% von 255 im Verlauf von 0 bis 19.
            SplashEffect::Draw(255 - (255 * (heroCritFrames[index]-50)/20) , batPtr->x,  batPtr->y );
        }

        heroCritFrames[index]++;
    }
}

// Zufügen der CRIT!-Animation auf betroffenen Helden oder Monstern
void AddEffects(RPG::Action *action)
{
    int startFrame = 1;
    if(action->kind == RPG::AK_SKILL)
    {
        if(ConfigSkills::skillDelay.count(action->skillId))
        {
            startFrame = -ConfigSkills::skillDelay[action->skillId];
        }
    }

    if(action->target == RPG::TARGET_MONSTER)
    {
        monsterCritFrames[action->targetId] = startFrame;
    }
    else if (action->target == RPG::TARGET_ALL_MONSTERS)
    {
        for(int i = 0; i<8; i++)
        {
            RPG::Monster *monPtr = RPG::monsters[i];
            if(monPtr != NULL)
            {
                if(monPtr->notHidden && monPtr->hp > 0)
                {
                    monsterCritFrames[i] = startFrame;
                }
            }
        }
    }
    else if(action->target == RPG::TARGET_ALL_ACTORS)
    {
        for(int i = 0; i<4; i++)
        {
            RPG::Actor *actPtr = RPG::Actor::partyMember(i);

            if(actPtr != NULL)
            {
                if(actPtr->hp > 0)
                {
                    heroCritFrames[i] = startFrame;
                }
            }
        }
    }
    else if(action->target == RPG::TARGET_ACTOR)
    {
        heroCritFrames[action->targetId] = startFrame;
    }
}


void ResetFrames()
{
    for(int iMonsters = 0; iMonsters < 8; iMonsters++)
    {
        monsterCritFrames[iMonsters] = 70;
    }

    for(int iHeroes = 0; iHeroes < 4; iHeroes++)
    {
        heroCritFrames[iHeroes] = 70;
    }
}

}
