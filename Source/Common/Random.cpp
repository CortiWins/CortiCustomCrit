namespace Random
{
void Load()
{
    SYSTEMTIME st;
    GetSystemTime(&st);
    srand(st.wMilliseconds);  // Initialize random number generator.
}

int GetRandomNumber ( int min, int max )
{
    // Zahl 0 bis...irgendwas generieren
    int randomNumber = (rand() % ( max - min + 1 )) + min;
    /*
            // Example min 3, max 7 : ergibt mögliche Werte 3,4,5,6,7 -> 5 Werte
            // ModValue = 7 - 3 = 4, es sollten aber 5 Werte werden, also +1
            int modValue = ( max - min ) + 1;
            // Hieraus gibt sich dann ein Wert von 0 bis 4
            int randomModulized = randomNumber % modValue;
            // Adidert man Min(3) zu (0...4) ergibt das (3...7)
            int returnrandom = randomModulized + min;
            */

    return randomNumber;
}

bool lastBit = false;
bool GetRandomBit ()
{
    // Zahl 0 bis...irgendwas generieren
    int randomNumber = rand() % 3; // Results in ... 0,1,2
    if(randomNumber==1)
    {
        lastBit = true;
        return true;
    }
    else if(randomNumber==2)
    {
        lastBit = false;
        return false;
    }
    else
    {
        lastBit = !lastBit;
        return lastBit;
    }
}
}
