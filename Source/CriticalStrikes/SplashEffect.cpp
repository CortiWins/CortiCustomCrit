namespace SplashEffect
{
// Grafik des Splash-Crit!-Symbols
RPG::Image *critSymbol;

void Draw(int alpha, int x, int y )
{
    critSymbol->alpha = alpha;
    RPG::screen->canvas->draw (x - critSymbol->width,  y - critSymbol->height,  critSymbol);
}

void Load()
{
    critSymbol = RPG::Image::create();
    critSymbol->useMaskColor = true;
    critSymbol->alpha = 255;
    if(Helper::FileExist("DynRessource\\Splash.png"))
    {
        critSymbol->loadFromFile ("DynRessource\\Splash.png", false );
    }
    else
    {
        Dialog::ShowInfoBox("DynRessource\\Splash.png","File does not exist.");
    }
}

void Unload()
{
    RPG::Image::destroy ( critSymbol );
}

}
