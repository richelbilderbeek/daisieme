#ifndef DME_CREATE_PARAMS_FILE_CPP_H
#define DME_CREATE_PARAMS_FILE_CPP_H

#include <string>

//' Create a parameter file.
//' @param filename name of the file
//' @param ana_psr anagenesis per-species rate
//' @return nothing
//' @author Richel J.C. Bilderbeek
//' @export
// [[Rcpp::export]]
void dme_create_params_file_cpp(
  const std::string& filename,
  const double ana_psr
);

#endif // DME_CREATE_PARAMS_FILE_CPP_H
