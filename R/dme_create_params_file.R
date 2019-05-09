#' Creates a daisieme parameter file
#' @param filename name of the file
#' @export
dme_create_params_file <- function(filename) {
  dme_create_params_file_cpp(
    filenename = filename
  )
}
