package curs;

import curs.domain.CriteriiUtilizator;
import curs.domain.Utilizator;
import curs.domain.validators.UtilizatorValidator;
import curs.domain.validators.UtilizatorValidatorStrict;
import curs.domain.validators.ValidationException;
import curs.domain.validators.Validator;
import curs.ex.functional.Arie;
import curs.ex.functional.Cerc;
import curs.ex.functional.Patrat;
import curs.repository.InMemoryRepository;
import curs.repository.Repository;
import curs.repository.factory.RepositoryFactory;
import curs.repository.file.UtilizatorFileRepository;
import curs.util.Colectii;
import jdk.jshell.execution.Util;

import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.Comparator;
import java.util.List;
import java.util.Properties;
import java.util.function.BinaryOperator;
import java.util.function.Function;

public class Main {

    /**
     *
     * @param args - command line arguments (not used)
     */
    public static void main(String[] args) {
//        cerinta1();
//        cerinta2();
//        cerinta3();
//        cerinta4();
//        listaArii();
//        cerinta7();
//        cerinta8();
//        cerinta9();
        cerinta10();
    }

    // ---------------- Cerinta 3. Repository in fisier text ----------------

    /**
     * loads the users from a text file, saves new users (the valid ones reach
     * the file) and reopens the file with a new repository to show that the
     * data persisted
     */
    static void cerinta3() {
        System.out.println("\n=== Cerinta 3 ===");
        String fisier = "data/utilizatori.txt";


    }

    // ---------------- Cerinta 2. Repository in memorie ----------------

    /**
     * saves the same users in two repositories that use different validation
     * strategies; the exceptions thrown by the validator propagate through
     * the repository and are handled here, in the caller
     */
    static void cerinta2() {
        System.out.println("\n=== Cerinta 2 ===");
        // Strategy: acelasi Context (InMemoryRepository), strategii diferite

        //System.out.println("findAll: " + repo.findAll());
    }

    /**
     * saves an entity and reports the result; ValidationException (thrown by
     * the validator) and IllegalArgumentException (thrown by the repository)
     * propagate from the repository and are caught here
     *
     * @param repo   - the repository where the user is saved
     * @param entity - the user to be saved (may be null)
     */
    static void salveaza(Repository<Long, Utilizator> repo, Utilizator entity) {

    }

    // ---------------- Cerinta 1. Utilizator valid ----------------

    /**
     * builds users from text lines (id;firstName;lastName), validates them
     * and prints the result; invalid data does not stop the program
     */
    static void cerinta1() {
        System.out.println("=== Cerinta 1 ===");
        Validator<Utilizator> validator = new UtilizatorValidator();

        // datele vin ca text, ca dintr-un fisier: id;prenume;nume
        String[] linii = {
                "1;Ana;Pop",
                "-2;;ionescu",     // 3 erori de validare
                "12b;Mihai;Pop",   // id nenumeric -> NumberFormatException
                "3;Ion;"           // nume lipsa la final -> vezi split(";", -1)
        };


        System.out.println("Programul continua dupa validare.");
    }

    static void cerinta4() {
        Properties properties = incarcaConfiguratie("/config.properties");
        RepositoryFactory repositoryFactory = new RepositoryFactory(properties);
        Repository<Long, Utilizator> repo = repositoryFactory.createUtilizatorRepository(new UtilizatorValidator());
        System.out.println("Repository creat" + repo.getClass().getSimpleName());
        System.out.println("Find all: " + repo.findAll());
    }

    static void cerinta9() {
        List<Utilizator> lista = Colectii.catreLista(reteaDemo().findAll());
        Function<Utilizator, String> numeComplet = u -> u.getFirstName() +
                " " + u.getLastName();
        Comparator<Utilizator> dupaNume = Comparator.comparing(Utilizator::getLastName)
                .thenComparing(Utilizator::getFirstName);
        lista.sort(dupaNume);
        System.out.println("Lista ordonata dupa nume si apoi dupa prenume:");
        System.out.println(Colectii.transforma(lista, numeComplet));

        Comparator<Utilizator> nrPrieteni = Comparator
                .comparingInt(u -> u.getFriends().size());

        lista.sort(nrPrieteni.reversed().thenComparing(dupaNume));
        System.out.println("Lista sortata dupa nr prieteni si apoi dupa nume:");
        System.out.println(Colectii.transforma(lista, u -> numeComplet.apply(u)
                + " " + u.getFriends().size()));

        Function<String, String> majuscule = String::toUpperCase;

        System.out.println("Lista cu numele complet cu majuscule");
        System.out.println(Colectii.transforma(lista, numeComplet.andThen(majuscule)));

        BinaryOperator<Utilizator> popular = BinaryOperator.maxBy(nrPrieteni);
        Utilizator maxPopular = Colectii.reduce(lista, popular);
        System.out.println("Cel mai popular utilizator: " + numeComplet.apply(maxPopular));
    }

    /**
     * creates a user from a text line; the NumberFormatException thrown by
     * Long.parseLong is translated into a ValidationException, keeping the
     * original exception as cause (exception chaining)
     *
     * @param linie - text line with the format id;firstName;lastName
     * @return the user created from the given line (not validated yet)
     * @throws ValidationException if the id is not numeric
     */
    static Utilizator utilizatorDinText(String linie) {
        String[] fields = linie.split(";", -1);
        try {
            Utilizator u_new = new Utilizator(fields[1], fields[2]);
            u_new.setId(Long.parseLong(fields[0]));
            return u_new;
        } catch (NumberFormatException e) {
            throw new ValidationException("Format invalid");
        }
    }

    static Properties incarcaConfiguratie(String resursa) {
        Properties properties = new Properties();
        try {
            InputStream inputStream = Main.class.getResourceAsStream(resursa);
            if(inputStream == null) {
                throw new RuntimeException("Resursa nu poate fi null!");
            }
            properties.load(inputStream);
        } catch (IOException e) {
            throw new RuntimeException("Eroare la citirea resursei" + resursa, e);
        }
        return properties;
    }

    static <E> void printArie(List<E> figuri, Arie<E> arie) {
        for (E figura : figuri) {
            System.out.println("Aria figurii " + figura + " este " + arie.calculeaza(figura));
        }
    }

    static void listaArii() {
        //lista imutabila, nu se poate adauga sau sterge din ea
        List<Cerc> cercuri = List.of(new Cerc(1), new Cerc(2), new Cerc(3));
        List<Patrat> patrate = List.of(new Patrat(1), new Patrat(2), new Patrat(3));
        Arie<Cerc> arieCercAnonim = new Arie<Cerc>() {
            @Override
            public double calculeaza(Cerc c) {
                return Math.PI * c.getRaza() * c.getRaza();
            }
        };
        System.out.println("Arie clasa anonima: ");
        printArie(cercuri, arieCercAnonim);

        Arie<Cerc> lambdaCerc = c -> Math.PI * c.getRaza() * c.getRaza();
        System.out.println("Arie lambda: ");
        printArie(cercuri, lambdaCerc);

        Arie<Cerc> arieCercReference = Cerc::arie;
        System.out.println("Arie cu referinta: ");
        printArie(cercuri, arieCercReference);
    }

    static void verificaPrenume(Utilizator u) {
        if(u.getFirstName() == null || u.getFirstName().isBlank()
                || u.getLastName() == null || u.getLastName().isBlank()) {
            throw new IllegalArgumentException("Prenumele sau numele lipseste");
        }
    }

    static void cerinta7() {
        Validator<Utilizator> validatorAnonim = new Validator<Utilizator>() {
            @Override
            public void validate(Utilizator u) {
                if(u.getFirstName() == null || u.getFirstName().isBlank()
                        || u.getLastName() == null || u.getLastName().isBlank()) {
                    throw new ValidationException("Prenumele sau numele lipseste");
                }
            }
        };

        Validator<Utilizator> validatorLambda = u -> {
            if(u.getFirstName() == null || u.getFirstName().isBlank()
                    || u.getLastName() == null || u.getLastName().isBlank()) {
                throw new IllegalArgumentException("Prenumele sau numele lipseste");
            }
        };

        Validator<Utilizator> validatorReferinta = Main::verificaPrenume;

        Utilizator utilizator = utilizatorDinText("7;;Pop");
        try {
            System.out.println("Validare anonima: ");
            validatorAnonim.validate(utilizator);
            System.out.println("Validare lambda: ");
            validatorLambda.validate(utilizator);
            System.out.println("Validare referinta: ");
            validatorReferinta.validate(utilizator);
        } catch (ValidationException e) {
            System.out.println(e.getMessage());
        }

        int max_len = 10;
        Validator<Utilizator> validator = u -> {
            if (u.getFirstName().length() > max_len || u.getLastName().length() > max_len) {
                throw new ValidationException("Preunumele si numele au cel mult " + max_len + " caractere");
            }
        };

        Validator<Utilizator> validatorCompus = new UtilizatorValidator().andThen(validator);

        Repository<Long, Utilizator> repoInjectat = new InMemoryRepository<>(validatorCompus);
        try {
            repoInjectat.save(utilizatorDinText("1;Ana;Pop"));
            repoInjectat.save(utilizatorDinText("2;Maximilian-Alexandru;Pop"));
            repoInjectat.save(utilizatorDinText("3;ana;Pop"));
        } catch (ValidationException e) {
            System.out.println(e.getMessage());
        }
    }

    static void cerinta8() {
        Repository<Long, Utilizator> retea = reteaDemo();
        System.out.println("Numele Pop: ");
        //retea.findAll(CriteriiUtilizator.areNumele("Pop")).forEach(System.out::println);
        List<Utilizator> list = retea.findAll(CriteriiUtilizator.areNumele("Pop"));
        for (Utilizator u : list) {
            System.out.println(u);
        }

        list = retea.findAll(CriteriiUtilizator.areCelPutinPrieteni(2));
        System.out.println("Are cel putin 2 prieteni: ");
        for (Utilizator u : list) {
            System.out.println(u);
        }

        retea.findAll(x -> x.getLastName() != "Pop" && x.getFirstName() == "Matei").forEach(System.out::println);
        System.out.println("Are numele diferit de Pop si prenumele matei: ");
        for (Utilizator u : list) {
            System.out.println(u);
        }

        List<Utilizator> lista = Colectii.catreLista(retea.findAll());
        lista.removeIf(CriteriiUtilizator::faraPrieteni);
        System.out.println("Numarul de utilizatori fara prieteni:");
        System.out.println(lista.size());


    }

    static void cerinta10() {
        Properties properties = incarcaConfiguratie("/config.properties");
        RepositoryFactory repositoryFactory = new RepositoryFactory(properties);
        Repository<Long, Utilizator> repo = repositoryFactory.createUtilizatorRepository(new UtilizatorValidator());
        System.out.println("Repository creat" + repo.getClass().getSimpleName());
        System.out.println("Find all: " + repo.findAll());
    }

    static Repository<Long, Utilizator> reteaDemo() {
        Repository<Long, Utilizator> repo = new InMemoryRepository<>(new UtilizatorValidator());

        String[] utilizatori = {"1;Ana;Pop", "2;Iancu;Robila", "3;Ion;Glanetas", "4;Lica;Samadaul", "5;Harap;Alb", "6;Filip;Cristian"};
        for(String s : utilizatori) {
            repo.save(utilizatorDinText(s));
        }
        long[][] prietenii = {{1,2}, {2,3}, {3,4}};
        for(long[] prieteni : prietenii) {
            Utilizator a = repo.findOne(prieteni[0]);
            Utilizator b = repo.findOne(prieteni[1]);
            a.getFriends().add(b);
            b.getFriends().add(a);
        }
        return repo;
    }
}
