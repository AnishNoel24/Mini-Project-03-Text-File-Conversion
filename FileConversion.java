import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.File;
import java.io.IOException;

public class FileConversion {
    // Function to convert file to upper case
    public static void convertToUpperCase(String filePath) {
        try {
            BufferedReader reader = new BufferedReader(new FileReader(filePath));
            BufferedWriter writer = new BufferedWriter(new FileWriter(filePath + ".tmp"));

            int c;
            while ((c = reader.read()) != -1) {
                writer.write(Character.toUpperCase(c));
            }

            reader.close();
            writer.close();

            // Replace the original file with the temporary file
            new File(filePath).delete();
            new File(filePath + ".tmp").renameTo(new File(filePath));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        // File sizes to test
        int[] fileSizes = {200, 400, 600, 800, 1000};  // MB

        // Perform conversion for each file size
        for (int size : fileSizes) {
            String filePath = "input_" + size + "mb.txt";

            try {
                // Create text file of given size (filled with random characters)
                BufferedWriter writer = new BufferedWriter(new FileWriter(filePath));
                for (int j = 0; j < size * 1024 * 1024; j++) {
                    writer.write('a');
                }
                writer.close();

                // Measure execution time
                long startTime = System.currentTimeMillis();
                convertToUpperCase(filePath);
                long endTime = System.currentTimeMillis();

                // Calculate and print execution time
                double executionTime = (endTime - startTime) / 1000.0;
                System.out.println("File size: " + size + "MB, Execution time: " + executionTime + " seconds");
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}
