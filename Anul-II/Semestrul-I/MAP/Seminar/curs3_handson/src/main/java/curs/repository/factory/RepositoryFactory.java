package curs.repository.factory;

import curs.domain.Utilizator;
import curs.domain.validators.Validator;
import curs.repository.InMemoryRepository;
import curs.repository.Repository;
import curs.repository.db.UtilizatorDbRepository;
import curs.repository.file.UtilizatorFileRepository;

import java.util.HashMap;
import java.util.Map;
import java.util.Properties;
import java.util.function.Supplier;

public class RepositoryFactory {
    private final Properties properties;

    public RepositoryFactory(Properties properties) {
        this.properties = properties;
    }

    public Repository<Long, Utilizator> createUtilizatorRepository(Validator<Utilizator> validator) {
        String value = properties.getProperty("repository.type");
        if (value == null) {
            throw new IllegalArgumentException("Property nu poate fi null!");
        }
        RepositoryType type = RepositoryType.valueOf(value.trim().toUpperCase());

        Map<RepositoryType, Supplier<Repository<Long, Utilizator>>> map = Map.of (
            RepositoryType.MEMORY,
                    () -> new InMemoryRepository<Long, Utilizator>(validator),
            RepositoryType.FILE,
                    () -> new UtilizatorFileRepository(validator, properties.getProperty("file.utilizatori")),
            RepositoryType.DATABASE,
                    () -> new UtilizatorDbRepository(validator, properties.getProperty("db.url"),
                        properties.getProperty("db.user"), properties.getProperty("db.password"))
        );

        Supplier<Repository<Long, Utilizator>> supplier = map.get(type);
        if(supplier == null) {
            throw new IllegalArgumentException();
        }
        return supplier.get();

//        switch (type) {
//            case MEMORY: return new InMemoryRepository<Long, Utilizator>(validator);
//            case FILE: return new UtilizatorFileRepository(validator, properties.getProperty("file.utilizatori"));
//            case DATABASE: return new UtilizatorDbRepository(validator, properties.getProperty("db.url"),
//                    properties.getProperty("db.user"), properties.getProperty("db.password"));
//            default: throw new IllegalArgumentException("Tip invalid!");
//        }
//        return switch (type){
//            case MEMORY -> new InMemoryRepository<Long, Utilizator>(validator);
//            case FILE -> new UtilizatorFileRepository(validator, properties.getProperty("file.utilizatori"));
//            case DATABASE -> new UtilizatorDbRepository(validator, properties.getProperty("db.url"),
//                    properties.getProperty("db.user"), properties.getProperty("db.password"));
//            default -> throw new IllegalArgumentException("Tip invalid!");
//        };
    }
}
