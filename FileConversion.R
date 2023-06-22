convertToUpperCase <- function(file_path) {
  content <- readLines(file_path)
  content <- toupper(content)
  writeLines(content, file_path)
}

file_sizes <- c(200, 400, 600, 800, 1000)  # MB

for (size in file_sizes) {
  file_path <- paste0("input_", size, "mb.txt")

  # Create text file of given size (filled with random characters)
  file <- file(file_path, "w")
  writeLines(rep("a", size * 1024 * 1024), file)
  close(file)

  # Measure execution time
  start_time <- Sys.time()
  convertToUpperCase(file_path)
  end_time <- Sys.time()

  # Calculate and print execution time
  execution_time <- end_time - start_time
  print(paste("File size:", size, "MB, Execution time:", execution_time, "seconds"))
}

