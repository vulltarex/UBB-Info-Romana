-- Script initializare baza de date socialnetwork pentru PostgreSQL

CREATE TABLE IF NOT EXISTS users (
    id BIGINT GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
    first_name VARCHAR NOT NULL,
    last_name VARCHAR NOT NULL
);

CREATE TABLE IF NOT EXISTS friendships (
    id1 BIGINT NOT NULL,
    id2 BIGINT NOT NULL,
    friends_from TIMESTAMP NOT NULL,
    PRIMARY KEY (id1, id2),
    CHECK (id1 < id2),
    CONSTRAINT fk_friendship_user1 FOREIGN KEY (id1) REFERENCES users(id) ON DELETE CASCADE,
    CONSTRAINT fk_friendship_user2 FOREIGN KEY (id2) REFERENCES users(id) ON DELETE CASCADE
);
