package repository;

import domain.Entity;
import domain.validator.ValidationException;
import domain.validator.Validator;

import java.io.IOException;
import java.io.UncheckedIOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.AtomicMoveNotSupportedException;
import java.nio.file.Files;
import java.nio.file.NoSuchFileException;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardCopyOption;
import java.time.format.DateTimeParseException;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.IntStream;
import java.util.stream.Stream;

/**
 * UTF-8 text persistence using Template Method; subclasses only convert lines.
 * Missing files mean empty repositories. Invalid lines stop loading with context.
 * @param <ID> the identifier type
 * @param <E> the entity type
 */
public abstract class AbstractFileRepository<ID, E extends Entity<ID>> extends InMemoryRepository<ID, E> {
    private final Path filename;

    /**
     * Conversion methods invoked here must not depend on subclass instance fields.
     * @param validator the strategy, fully initialized before file loading
     * @param filename the relative text file path
     * @throws IllegalArgumentException if a parameter is invalid
     * @throws RepositoryException if an existing file cannot be loaded or contains invalid data
     */
    public AbstractFileRepository(Validator<E> validator, String filename) {
        super(validator);
        if (filename == null || filename.isBlank()) throw new IllegalArgumentException("Calea fisierului lipseste!");
        this.filename = Paths.get(filename);
        if (this.filename.isAbsolute()) throw new IllegalArgumentException("Calea fisierului trebuie sa fie relativa!");
        loadFromFile();
    }

    /**
     * Converts one text line into an entity.
     * @param line one line of text
     * @return the corresponding entity
     * @throws IllegalArgumentException if fields or numeric IDs are invalid
     * @throws DateTimeParseException if a date cannot be parsed
     */
    protected abstract E extractEntity(String line);

    /**
     * Converts an entity into one text line.
     * @param entity the entity to serialize
     * @return one line of text without a line terminator
     */
    protected abstract String createEntityAsString(E entity);

    private void loadFromFile() {
        try (Stream<String> source = Files.lines(filename, StandardCharsets.UTF_8)) {
            List<String> lines = source.collect(Collectors.toList());
            IntStream.range(0, lines.size())
                    .filter(index -> !lines.get(index).isBlank())
                    .forEachOrdered(index -> loadLine(lines.get(index), index + 1));
        } catch (NoSuchFileException e) {
            // A missing file is a supported initial state, not a loading failure.
            repo.clear();
        } catch (UncheckedIOException e) {
            throw new RepositoryException("Eroare la citirea fisierului " + filename + ".", e.getCause());
        } catch (IOException e) {
            throw new RepositoryException("Eroare la citirea fisierului " + filename + ".", e);
        }
    }

    private void loadLine(String line, int lineNumber) {
        try {
            E entity = extractEntity(line);
            if (super.save(entity) != null) throw new IllegalArgumentException("ID duplicat!");
        } catch (IllegalArgumentException | ValidationException | DateTimeParseException e) {
            throw new RepositoryException("Fisier " + filename + ", linia " + lineNumber + ": " + e.getMessage(), e);
        }
    }

    private void writeToFile() {
        Path temporary = null;
        try {
            Path parent = filename.getParent();
            if (parent == null) parent = Paths.get(".");
            Files.createDirectories(parent);
            temporary = Files.createTempFile(parent, "repository-", ".tmp");
            List<String> lines = repo.values().stream().map(this::createEntityAsString).collect(Collectors.toList());
            Files.write(temporary, lines, StandardCharsets.UTF_8);
            try {
                Files.move(temporary, filename, StandardCopyOption.REPLACE_EXISTING, StandardCopyOption.ATOMIC_MOVE);
            } catch (AtomicMoveNotSupportedException e) {
                Files.move(temporary, filename, StandardCopyOption.REPLACE_EXISTING);
            }
        } catch (IOException e) {
            if (temporary != null) {
                try {
                    Files.deleteIfExists(temporary);
                } catch (IOException cleanupError) {
                    e.addSuppressed(cleanupError);
                }
            }
            throw new RepositoryException("Eroare la scrierea fisierului " + filename + ".", e);
        }
    }

    /** {@inheritDoc} */
    @Override
    public E save(E entity) {
        E result = super.save(entity);
        if (result == null) {
            try {
                writeToFile();
            } catch (RepositoryException e) {
                repo.remove(entity.getID());
                throw e;
            }
        }
        return result;
    }

    /** {@inheritDoc} */
    @Override
    public E delete(ID id) {
        E result = super.delete(id);
        if (result != null) {
            try {
                writeToFile();
            } catch (RepositoryException e) {
                repo.put(id, result);
                throw e;
            }
        }
        return result;
    }

    /** {@inheritDoc} */
    @Override
    public E update(E entity) {
        if (entity == null) throw new IllegalArgumentException("Entitatea nu poate fi null!");
        E previous = findOne(entity.getID());
        E result = super.update(entity);
        if (result == null) {
            try {
                writeToFile();
            } catch (RepositoryException e) {
                repo.put(entity.getID(), previous);
                throw e;
            }
        }
        return result;
    }
}
