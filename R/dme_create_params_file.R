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

#' Creates a testing daisieme parameter file
#' @inheritParams default_params_doc
#' @export
dme_create_test_params_file <- function(
  filename = tempfile(),
  ana_psr = 0.1,
  clado_is_psr = 0.1,
  clado_main_psr = 0.1,
  ext_is_psr = 0.01,
  ext_main_psr = 0.01,
  mig_to_is_psr = 0.1,
  carry_cap_is = 5,
  carry_cap_main = 20,
  rng_seed = 42,
  init_n_main_clades = 1,
  init_n_main_sps = 10,
  crown_age = 15.0
) {
  dme_create_params_file(
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
