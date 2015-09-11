#define _WIN32_WINNT 0x0500

#include <sstream>
#include <fstream>
#include <algorithm>
#include <DynRPG/DynRPG.h>

// Contains Configuration. Loaded onStartup
std::map<std::string, std::string> configMap;

// Common Functions
#include "Common//Dialog.cpp"
#include "Common//Helper.cpp"

#include "Configuration//ConfigDebug.cpp"
#include "Configuration//Configuration.cpp"
#include "Configuration//ConfigSkills.cpp"
#include "Configuration//ConfigType1.cpp"
#include "Configuration//ConfigType3.cpp"

#include "Calculations//LevelInfluence.cpp"
#include "Calculations//CritCalcType1.cpp"
#include "Calculations//CritCalcType2.cpp"
#include "Calculations//CritCalcType3.cpp"
#include "Calculations//Calculations.cpp"

#include "CriticalStrikes//SplashEffect.cpp"
#include "CriticalStrikes//DrawCritSplash.cpp"
#include "CriticalStrikes//HeroAttackBonus.cpp"
#include "CriticalStrikes//CritCommands.cpp"

#include "CustomCrit.cpp"

// DynRPG Callbacks
#include "Callbacks//onSystem.cpp"
#include "Callbacks//onBattlerAction.cpp"
#include "Callbacks//onBattlerDrawn.cpp"
#include "Callbacks//onFrame.cpp"
#include "Callbacks//onComment.cpp"
