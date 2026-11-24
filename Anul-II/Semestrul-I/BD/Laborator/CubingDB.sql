USE CubingDB;
GO

CREATE TABLE Concurent (
    id_concurent INT PRIMARY KEY IDENTITY(1,1),
    nume NVARCHAR(50),
    prenume NVARCHAR(50),
    data_nasterii DATE
);

CREATE TABLE Locatie (
    id_locatie INT PRIMARY KEY IDENTITY(100,1),
    denumire NVARCHAR(100),
    oras NVARCHAR(50),
    adresa NVARCHAR(100)
);

CREATE TABLE Competitie (
    id_comp INT PRIMARY KEY IDENTITY(200,1),
    denumire NVARCHAR(100),
    data_incepere DATE,
    data_incheiere DATE,
    id_locatie INT FOREIGN KEY REFERENCES Locatie(id_locatie)
);

CREATE TABLE Puzzle (
    id_puzzle INT PRIMARY KEY IDENTITY(300,1),
    denumire NVARCHAR(25)
);

CREATE TABLE Proba (
    id_proba INT PRIMARY KEY IDENTITY(400,1),
    denumire NVARCHAR(50),
    id_puzzle INT FOREIGN KEY REFERENCES Puzzle(id_puzzle)
);

CREATE TABLE ProbaCompetitie (
    id_proba_comp INT PRIMARY KEY IDENTITY(500,1),
    id_comp INT FOREIGN KEY REFERENCES Competitie(id_comp),
    id_proba INT FOREIGN KEY REFERENCES Proba(id_proba)
);

CREATE TABLE Inscriere (
    id_inscriere INT PRIMARY KEY IDENTITY(600,1),
    id_concurent INT FOREIGN KEY REFERENCES Concurent(id_concurent),
    id_comp INT FOREIGN KEY REFERENCES Competitie(id_comp),
    data_inscrierii DATETIME
);

CREATE TABLE ParticipareProba (
    id_participare INT PRIMARY KEY IDENTITY(700,1),
    id_inscriere INT FOREIGN KEY REFERENCES Inscriere(id_inscriere),
    id_proba_comp INT FOREIGN KEY REFERENCES ProbaCompetitie(id_proba_comp)
);

CREATE TABLE Runda (
    id_runda INT PRIMARY KEY IDENTITY(800,1),
    id_proba_comp INT FOREIGN KEY REFERENCES ProbaCompetitie(id_proba_comp),
    nr_runda INT,
    denumire NVARCHAR(50)
);

CREATE TABLE Incercare (
    id_incercare INT PRIMARY KEY IDENTITY(900,1),
    id_participare INT FOREIGN KEY REFERENCES ParticipareProba(id_participare),
    id_runda INT FOREIGN KEY REFERENCES Runda(id_runda),
    nr_incercare INT,
    timp_ms INT
);

USE CubingDB;
GO

SELECT * FROM Concurent;

DELETE FROM Concurent where nume='Zemdegs';