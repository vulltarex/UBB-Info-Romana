package config;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Properties;

/** Loads application configuration from the classpath or filesystem using Properties. */
public final class ConfigLoader {
    private ConfigLoader() {}

    /**
     * Loads the application configuration.
     * @return properties loaded from config.properties
     * @throws ConfigurationException if the resource is missing, unreadable or malformed
     */
    public static Properties load() {
        InputStream input = ConfigLoader.class.getResourceAsStream("/config.properties");
        if (input == null) {
            Path rootConfig = Paths.get("config.properties");
            Path resourceConfig = Paths.get("src/main/resources/config.properties");
            try {
                if (Files.exists(rootConfig)) {
                    input = Files.newInputStream(rootConfig);
                } else if (Files.exists(resourceConfig)) {
                    input = Files.newInputStream(resourceConfig);
                }
            } catch (IOException ignored) {}
        }
        if (input == null) {
            throw new ConfigurationException("Resursa config.properties lipseste din classpath si din proiect!");
        }
        try (InputStream in = input;
             BufferedReader reader = new BufferedReader(new InputStreamReader(in, StandardCharsets.UTF_8))) {
            Properties properties = new Properties();
            properties.load(reader);
            return properties;
        } catch (IOException | IllegalArgumentException e) {
            throw new ConfigurationException("Nu se poate incarca config.properties: " + e.getMessage(), e);
        }
    }
}
