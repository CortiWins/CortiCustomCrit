namespace Helper
{
bool FileExist(std::string filename)
{
    // benötigt #include <fstream>
    std::ifstream ifile(filename.c_str()); // Try to open file for reading
    return (bool)ifile; // Casted to bool here, so true if ifile != null, i.e. it exists
}
}
