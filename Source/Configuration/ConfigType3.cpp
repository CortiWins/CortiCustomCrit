namespace ConfigType3
{
// Datenbank-ID des Helden, dessen Kurvenverlauf als Daten für die Umrechnung angenommen werden
int ratingCoefficientHeroId = 0;


// Laden der Einstellungen für Kritberechnung Typ 3
// Typ 3 -> Der Intwert ist ein Ratingwert, der in eine Chance umgewandelt wird.
void Load()
{
    if(configMap.count("t3RatingCoefficientHeroId"))
    {
        ratingCoefficientHeroId = (atoi(configMap["t3RatingCoefficientHeroId"].c_str()));
        if(ratingCoefficientHeroId<0 || ratingCoefficientHeroId > RPG::actors.count() )
        {
            Dialog::ShowInfoBox(ratingCoefficientHeroId, "Invalid t3RatingCoefficientHeroId");
        }
    }

    // Anzahl Helden in der Datenbank
    int numberOfActors= RPG::actors.count();
    if(ratingCoefficientHeroId>numberOfActors)
    {
        Dialog::ShowInfoBox("Referenced Hero exceeds HeroDatabaseSize", "Invalid t3RatingCoefficientHeroId");
        Configuration::critAttackBonusValidSettings = false; // Settings nicht in Ordnung
    }
}


}
