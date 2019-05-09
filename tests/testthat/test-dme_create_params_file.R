context("test-dme_create_params_file")

test_that("use", {
  expect_silent(dme_create_params_file(tempfile()))
})
