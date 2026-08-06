import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.Path;
import java.io.IOException;
import java.nio.charset.StandardCharsets;


public class FileExtractor {
	public static String extract(String folder) {
		StringBuilder allText = new StringBuilder();


		try (var paths = Files.walk(Paths.get(folder))) {
			paths.filter(Files::isRegularFile)
				.forEach(path -> {
					try {
                         String lines = Files.readString( path, StandardCharsets.ISO_8859_1);

						allText.append(lines);
					} catch (IOException e) {
						System.out.println("Error reading: " + path);
					}
				});
		}
		catch (IOException e){
            System.out.println("Error accessing folder: " + folder);
		}

		return allText.toString();
	}
}
