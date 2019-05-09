#include "dme_create_params_file_cpp.h"

#include <fstream>

void dme_create_params_file_cpp(const std::string& filename)
{
  std::ofstream f(filename.c_str());
 f << "STUB";
}
