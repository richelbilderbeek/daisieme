#' Creates a daisieme parameter file
#' @inheritParams default_params_doc
#' @export
dme_create_params_file <- function(
  filename,
  ana_psr,
  clado_is_psr,
  clado_main_psr,
  ext_is_psr,
  ext_main_psr,
  mig_to_is_psr,
  carry_cap_is,
  carry_cap_main,
  rng_seed,
  init_n_main_clades,
  init_n_main_sps,
  crown_age
) {
  dme_create_params_file_cpp(
    filename = filename,
    ana_psr = ana_psr,
    clado_is_psr = clado_is_psr,
    clado_main_psr = clado_main_psr,
    ext_is_psr = ext_is_psr,
    ext_main_psr = ext_main_psr,
    mig_to_is_psr = mig_to_is_psr,
    carry_cap_is = carry_cap_is,
    carry_cap_main = carry_cap_main,
    rng_seed = rng_seed,
    init_n_main_clades = init_n_main_clades,
    init_n_main_sps = init_n_main_sps,
    crown_age = crown_age
  )
}
