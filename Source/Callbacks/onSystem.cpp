
bool onStartup (char *pluginName)
{
    // We load the configuration from the DynRPG.ini file here
    configMap = RPG::loadConfiguration(pluginName);
    return true;
}

void onInitFinished()
{
    ConfigDebug::Load();
    Configuration::Load();
    ConfigSkills::Load();

    if(Configuration::critCalcType == 1)
    {
        // Typ 1 ->Helden haben eine vom Int-Wert unabhängige Kritchance
        CustomCrit::critFunction = CritCalcType1::CalculateCritFix;
        ConfigType1::Load();
    }
    else if(Configuration::critCalcType == 2)
    {
        // Typ 2 ->Helden haben den Int-Wert als Kritchance
        CustomCrit::critFunction = CritCalcType2::CalculateCritRaw;
    }
    else if(Configuration::critCalcType == 3)
    {
        // Typ 3 -> Der Intwert ist ein Ratingwert, der in eine Chance umgewandelt wird.
        CustomCrit::critFunction = CritCalcType3::CalculateCritByRating;
        ConfigType3::Load();
    }
    else if(Configuration::critCalcType == 0)
    {
        CustomCrit::critFunction = CustomCrit::GetZero;
        Dialog::ShowInfoBox("CritCalcType = 0 Try to add a configuration ;-) ","CortiCustomCrit");
    }

    HeroAttackBonus::Load();
    SplashEffect::Load();
}

// This handler is called when the game exits
void onExit()
{
    HeroAttackBonus::Unload();
    SplashEffect::Unload();
}
