#' Creates a daisieme parameter file
#' @param filename name of the file
#' @param ana_psr anagenesis per-species rate
#' @export
dme_create_params_file <- function(
 filename,
 ana_psr
) {
  dme_create_params_file_cpp(
    filename = filename,
     ana_psr = ana_psr
  )
}
