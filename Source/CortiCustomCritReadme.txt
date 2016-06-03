CortiCustomCrit DynRPG PlugIn V0.6
	by Corti ( 2013-2015 )
	for RPG Maker 2003 with DynRPG v0.20 or higher

github.com/CortiWins/CortiCustomCrit
*******************************************************************
*                     Versions
*******************************************************************
(V0.1) [22.12.2013] Testversion
(V0.2) [29.12.2013] Advanced configuration
(V0.3) [28.01.2014] Error on reset fixed
(V0.4) [30.01.2015] Skillspecific modification of critchances
(V0.5) [11.09.2015] Restructured, translated. New setting: CritCalcOnSkillsDisabled
(V0.6) [13.09.2015] Fixed bug that prevent reenabling of specific skill if crit is disabled on skills. Improved documentation for Skillspecific Modifications. Translated DynRPG.ini lines.
(V0.7) [13.09.2015] Skillspecific delay for <CRIT!> Icon!

Planned for future releases:
* adding agility as a crit stat in a way less complex than calculation type 3.

*******************************************************************
*                     Content
*******************************************************************
Using the plugin
Configuration Parameters
Calculating the critical hit chance
    Type 1: Fixed Value
    Type 2: Raw Stat
    Type 3: Rating to Chance
Calculating the critical hit damage
Calculating the level influence
Configuration: Skillspecific Modifications
Configuration: Disabling crit on skills
Configuration: Disabling crit on defensive skills
Debug outputs
Comment commands
For Developers

*******************************************************************
*                     Using the plugin
*******************************************************************
Implements the possibility to deal critical strikes with attacks and skills in a way that is more flexible than the rpg makers own crit calculations.

>> Critical Strike:
Landing a critical means that an attack randomly deals more damage. This plugin simulates that by increasing the respective heros attack value before the attack
Since there is no callback that is called after the attack is done, the attack bonus can not be immediatley reset, but it is updated when the next action is done.

When an attack lands a critical strike, a symbol is shown on top of the target. The symbol can be replaced with your own.

>> Crit Source: There are different possible sources of crit.

* Constant or from variable
* Using the int stat
* Using the agi stat

Chosing INT as the crit stat:
The heart of this plugin is to replace the crippled magic-off/def with something useful and way more cool.
Using the int stat is practical because you can use items and conditions to influence the critchance.

"But without int, how is magic improved then?"

Use attack and rename it to power or anything else that can be both physical and magical. The int formular is so bad, you can't do good power scaling with it anyway.

With int as the crit stat you have:
* Attack: Stronger at what you do
* Defense: live longer
* Agility: Do things more often
* Krit/Ex-Int: Chance to deal more damage

Chosing AGI as the crit stat:
Though i'd recommend to use int, agi is also possible to use agility, but only when using Type 3 right now.
This cam be useful, if you are using int for something else, like regeneration or if you hacked the formular and made int useful.

*******************************************************************
*                     Configuration Parameters
*******************************************************************
The important configuration settings are...
- Calculating the critical hit CHANCE
- Calculating the critical hit DAMAGE BONUS
- Level of player level vs monster level

All configuration is done in the DynRPG.ini file. See the TestProject for an example.

*******************************************************************
*                     Calculating the critical hit chance
*******************************************************************
This parameter determines the way the critical strike chance is calculated.
CritCalcType=1

The critical strike chance can be calculated in three different ways.

* Type 1: Fixed Value
* Type 2: Raw Stat
* Type 3: Rating to Chance

*******************************************************************
*                     Type 1: Fixed Value
*******************************************************************
Neither int nor crit are used to calculate the crit chance. The crit chance for each hero is configured in the configuration file.
This is for users that don't want to override one of the base stats and users who just like it very simple.

The default critical strike chance is 20%. This can be chanced and every hero can be configured individually.
Hero int can be used for magic.
Monster it can be used as enemy level if configured that way.

========= CONFIGURATION ====================
; CalculationType1 : DefaultCritChance for all heroes that are not specifically set
t1CritChanceDefault=20

; Hero with database ID 5 gets a 25% chance to crit.
t1HeroCritHero_1_Id=5
t1HeroCritHero_1_FixCrit=25

; Hero with database ID 3 gets his crit chance from variable 345
t1HeroCritHero_2_Id=3
t1HeroCritHero_2_Variable=345

*******************************************************************
*                     Type 2: Raw Stat
*******************************************************************

In this type, the critical strike chance equals your int value.
Monster it can be used as enemy level if configured that way.

*******************************************************************
*                    Type 3: Rating to Chance
*******************************************************************
In this type, the critical strike chance does not equal int or agility value.
The stat values is taken as a rating value that is calculated into the chance division with a coefficient that depends on player and enemy level.

For this it is required to deposit an unused hero in the database whose maximum life curve is used as the coefficient.
Stat curves are quite abstract and hard to get for people who don't get well with mathematics.

This type of calculcation can be used to achieve best stat equivalency, but in most cases, the games don't require that.

Basics to stat curves ( in german ):
http://www.multimediaxis.de/threads/134909-RM-2k-2K3-Zahlen-und-Werteprogress
http://www.multimediaxis.de/threads/139514-Rm2k-2k3-Statkurven-als-Wertetemplate

========= CONFIGURATION ====================
Since coeffients are often floating point numbers, the max life alues from the stat curse is coefficient  100.

Example:
3 Int should be 14% Crit.
3 Int = 14% -> 3/14Int = 1% -> 0,214 Int -> 1% critical strike chance.

This 0,21 are now deposited in the stat curve as 21.

This parameter sets the database id of the hero whose max life curse if taken as a coeffient
t3RatingCoefficientHeroId=11

*******************************************************************
*                     Setting intellect or agility
*******************************************************************
CritSource=0

0 = Plugin uses intellect for Type 3 calculations ( Default )
1 = Plugin uses agility for Type 3 calculations

*******************************************************************
*                     Calculating the critical hit damage
*******************************************************************
When a critical strike is dealt, the atk of the hero is increased before the action is executed.
This parameter determines the way the critical strike damage bonus is calculated.
CritAttackBonusType=1

0 = Invalid! Chose a better one!
1 = Atk is increased by a percentage of the heros atk. The percentage is configured i the CritAttackBonusTypeValue parameter.
2 = Atk is taken from the atk stat curse of a hero in the database. The database id of that hero is configured as the CritAttackBonusTypeValue parameter.

Example:
CritAttackBonusTypeValue=33
When using CritAttackBonusType 2, this increases atk by 33%.
When using CritAttackBonusType 3, this increases atk by the atk value of hero 33 on current hero level.

*******************************************************************
*                     Calculating the level influence
*******************************************************************
Calculating the heros and enemies level into the equation is required for type 3 stat equavalency.
If you are using type 1 or type 2 crit calculation, you don't need this and you can use standard values.
This can also be used to mimic the way crit is done by setting player agility off aginst enemy agility like it is done in a lot of jRPGs and the rpg makers own crit formular.
CritCalcWithLevel=1

Parameter:
0 = No changes based on level, the heros own level is used as a coefficient in type 3.
1 = The enemies int value is taken as his level.
2 = A variable holds all enemies level.

; If CalcWithLevel=2, then this parameter determines the variable that holds the moblevel.
CritCalcWithLevelVariable=256

Set the enemy level to one that matches your hoes level when you first encounter the monster type.

Additional information ( in german )
http://www.multimediaxis.de/threads/134909-RM-2k-2K3-Zahlen-und-Werteprogress
http://www.multimediaxis.de/threads/139514-Rm2k-2k3-Statkurven-als-Wertetemplate

*******************************************************************
*                     Configuration: Skillspecific Modifications
*******************************************************************
This settings allow to influence the critical strike chance of certain specific skills that can be configured.
There are four possible modifications. Lets pretend the basic critchance is 10%.

* Constant multiplicative chance
Example: 50 = 10 * 50 / 100 = 15% critical strike chance

* Multiplicative chance from variable
Example: 123 = 10 * \v[123] / 100

* Constant additive chance
Example: 20 = 10 +20% critical strike chance

* Additive chance from variable
Example: 123 = + \v[123] critical strike chance

* Delay to shew the > CRIT! < Icon in frames.
Example: 25 = showing tthe icon is delayed by 25 frames.

Formular for Hero (H) using Skill (S)
CritChance = ( CritChance(H) * MultiConst(S) /100  * MultiVar(S) / 100 ) + AddConst(S) + AddVar(S)

SkillIdX=123
SkillMulConX=0
SkillMulVarX=0
SkillAddConX=0
SkillAddVarX=04
SkillDelayX=25

========= CONFIGURATION ====================
The X is a number. Use "SkillId1" for the first skill, "SkillId2" for the second.
Parsing the parameters stops when a number is not found.

How to set up different skills:

; Skill 123 does have his crit chance doubled
SkillId1=123
SkillMulCon1=200

; Skill 19 does have his crit chance increased by the value in variable 4200
SkillId2=19
SkillAddVar2=4200

; Skill 23 will not be configured because there is no skill configured with "SkillId3=..."
SkillId4=23
SkillAddCon4=30

*******************************************************************
*                     Configuration: Disabling crit on skills
*******************************************************************
If this parameter is set, critical strikes can only be done by certain skills.
CritCalcOnSkillsDisabled=0

If you want to disable crits on skill use, set this to one. If you want to enable crit for certain spells,
refer to section "Skillspecific Modifications".

By setting the Constant multiplicative chance, the skill is recognized as a exception for this rule.

*******************************************************************
*                     Configuration: Disabling crit on defensive skills
*******************************************************************
If this parameter is set, critical strikes can only be dealt against monsters.
CritCalcOnHerosDisabled=0

Determines the level difference that is taken when using a defensive skill
CritCalcOnHerosLevel=0
0 = Hero Level
1 = Mean monster value or from variable, according to setting

*******************************************************************
*                     Debug outputs
*******************************************************************
This parameter can be used to check your settings when you encounter problems.
DebugParams=1

Example:
1 = Show which parameters are set.
0 = Deactivated ( default )

The following parameters activate writing the results of a crit calculation into variabled.

ID of the acting hero in variable 21
DebugHeroIdVariable=21

Raw crit chance of the action
DebugRawCritVariable=22

Calculated target level
DebugTargetLevelVariable=23

Critical chance after level influence ( Typ 1 und 2)
DebugAdeptedCritVariable=24

Applied attack bonus
DebugAppliedAttackBonusVariable=25

*******************************************************************
*                     Comment commands
*******************************************************************
Use of comment commands: http://rewtone.com/dynrpg/guidelines.html

You can use this commands in event scripts to request and reset a heros critical strike status for things like building an effect that happens after dealing a critical strike.

// Request crit status
@ccrit_getstatus heroId, switchId
heroId = Heros Database ID
switchId = ID of the switch that is set according to crit status.

// Manual reset of the heros crit status
@ccrit_resetstatus heroId
heroId = Heros Database ID

*******************************************************************
*                     For Developers
*******************************************************************
GCC compiler optimizations will destroy this plugins functionality.
If you recompile, make sure to deal with this.
http://rpgmaker.net/forums/topics/10254/?post=674082#post674082
