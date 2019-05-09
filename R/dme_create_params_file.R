#' Creates a daisieme parameter file
#' @param filename name of the file
#' @param ana_psr anagenesis, per-species rate
#' @param clado_is_psr cladogenesis on island, per-species rate
#' @param clado_main_psr cladogenesis on mainland, per-species rate
#' @param ext_is_psr extinction rate on island, per-species rate
#' @param ext_main_psr extinction rate on mainland, per-species rate
#' @param mig_to_is_psr migratrion to island, per-species rate
#' @export
dme_create_params_file <- function(
 filename,
 ana_psr,
 clado_is_psr,
 clado_main_psr,
 ext_is_psr,
 ext_main_psr,
 mig_to_is_psr
) {
  dme_create_params_file_cpp(
    filename = filename,
    ana_psr = ana_psr,
    clado_is_psr = clado_is_psr,
    clado_main_psr = clado_main_psr,
    ext_is_psr = ext_is_psr,
    ext_main_psr = ext_main_psr,
   mig_to_is_psr = mig_to_is_psr
  )
}
