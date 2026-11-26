package seminar9.service;

import seminar9.domain.Movie;
import seminar9.domain.validators.Validator;
import seminar9.repository.PagingRepository;
import seminar9.util.Page;
import seminar9.util.Pageable;
import seminar9.util.Sort;

public class MovieService {
    private final PagingRepository<Long, Movie> repository;
    private final Validator<Movie> validator;

    public MovieService(PagingRepository<Long, Movie> repository, Validator<Movie> validator) {
        this.repository = repository;
        this.validator = validator;
    }

    public Page<Movie> findAllOnPage(int pageNumber, int pageSize) {
        return repository.findAllOnPage(new Pageable(pageNumber, pageSize));
    }

    public Page<Movie> findAllOnPage(int pageNumber, int pageSize, Sort sort) {
        return repository.findAllOnPage(new Pageable(pageNumber, pageSize), sort);
    }

    public Page<Movie> findAllOnPage(int pageNumber, int pageSize, String text){
        return repository.findAllOnPage(new Pageable(pageNumber, pageSize), text);
    }
    /**
     * @throws seminar9.domain.validators.ValidationException if the movie is not valid
     */
    public Movie addMovie(String title, String director, int year, int duration) {
        Movie movie = new Movie(title, director, year, duration);
        validator.validate(movie);
        repository.save(movie);
        return movie;
    }

    /**
     * @throws seminar9.domain.validators.ValidationException if the new data is not valid
     * @throws IllegalArgumentException if there is no movie with the given id
     */
    public Movie updateMovie(Long id, String title, String director, int year, int duration) {
        Movie movie = new Movie(title, director, year, duration);
        movie.setId(id);
        validator.validate(movie);
        if (repository.update(movie).isPresent())
            throw new IllegalArgumentException("There is no movie with id " + id);
        return movie;
    }

    /**
     * @throws IllegalArgumentException if there is no movie with the given id
     */
    public Movie deleteMovie(Long id) {
        return repository.delete(id)
                .orElseThrow(() -> new IllegalArgumentException("There is no movie with id " + id));
    }
}
