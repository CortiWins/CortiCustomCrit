namespace CortiConfig
{
// Special setting for the game "Dark Sword"
//#define DARKSWORD
void Load()
{
#ifdef DARKSWORD
ConfigSkills::skillAddConstant[12] = 14;
#endif // DARKSWORD
}

}
