USE CubingDB;
GO

CREATE TABLE VersiuneBD (
    versiune INT NOT NULL
);

INSERT INTO VersiuneBD (versiune) VALUES (0);
GO

-- Versiunea 1: modificarea tipului unei coloane.
CREATE PROCEDURE usp_MaresteDenumireLocatie
AS
BEGIN
    ALTER TABLE Locatie ALTER COLUMN denumire NVARCHAR(150) NULL;
END;
GO

CREATE PROCEDURE usp_RevinoDenumireLocatie
AS
BEGIN
    ALTER TABLE Locatie ALTER COLUMN denumire NVARCHAR(100) NULL;
END;
GO

-- Versiunea 2: valoare implicita pentru inscrierile noi.
CREATE PROCEDURE usp_AdaugaDefaultInscriere
AS
BEGIN
    ALTER TABLE Inscriere
    ADD CONSTRAINT DF_Inscriere_Data DEFAULT GETDATE() FOR data_inscrierii;
END;
GO

CREATE PROCEDURE usp_StergeDefaultInscriere
AS
BEGIN
    ALTER TABLE Inscriere DROP CONSTRAINT DF_Inscriere_Data;
END;
GO

-- Versiunea 3: tabela Organizator.
CREATE PROCEDURE usp_CreeazaOrganizator
AS
BEGIN
    CREATE TABLE Organizator (
        id_organizator INT PRIMARY KEY IDENTITY(1,1),
        denumire NVARCHAR(100) NOT NULL
    );
END;
GO

CREATE PROCEDURE usp_StergeOrganizator
AS
BEGIN
    DROP TABLE Organizator;
END;
GO

-- Versiunea 4: coloana prin care o competitie poate avea un organizator.
CREATE PROCEDURE usp_AdaugaColoanaOrganizator
AS
BEGIN
    ALTER TABLE Competitie ADD id_organizator INT NULL;
END;
GO

CREATE PROCEDURE usp_StergeColoanaOrganizator
AS
BEGIN
    ALTER TABLE Competitie DROP COLUMN id_organizator;
END;
GO

-- Versiunea 5: cheia straina spre tabela Organizator.
CREATE PROCEDURE usp_AdaugaFKOrganizator
AS
BEGIN
    ALTER TABLE Competitie
    ADD CONSTRAINT FK_Competitie_Organizator
        FOREIGN KEY (id_organizator)
        REFERENCES Organizator(id_organizator);
END;
GO

CREATE PROCEDURE usp_StergeFKOrganizator
AS
BEGIN
    ALTER TABLE Competitie DROP CONSTRAINT FK_Competitie_Organizator;
END;
GO

ALTER PROCEDURE usp_SchimbaVersiunea
    @versiune_tinta INT
AS
BEGIN
    IF @versiune_tinta IS NULL OR @versiune_tinta NOT BETWEEN 0 AND 5
        THROW 50001, 'Versiunea trebuie sa fie intre 0 si 5.', 1;

    DECLARE @versiune_curenta INT;

    SELECT @versiune_curenta = versiune
    FROM VersiuneBD;

    BEGIN TRY
        WHILE @versiune_curenta < @versiune_tinta
        BEGIN
            IF @versiune_curenta = 0
                EXEC usp_MaresteDenumireLocatie;
            ELSE IF @versiune_curenta = 1
                EXEC usp_AdaugaDefaultInscriere;
            ELSE IF @versiune_curenta = 2
                EXEC usp_CreeazaOrganizator;
            ELSE IF @versiune_curenta = 3
                EXEC usp_AdaugaColoanaOrganizator;
            ELSE IF @versiune_curenta = 4
                EXEC usp_AdaugaFKOrganizator;

            SET @versiune_curenta = @versiune_curenta + 1;
            UPDATE VersiuneBD SET versiune = @versiune_curenta;
        END;

        WHILE @versiune_curenta > @versiune_tinta
        BEGIN
            IF @versiune_curenta = 5
                EXEC usp_StergeFKOrganizator;
            ELSE IF @versiune_curenta = 4
                EXEC usp_StergeColoanaOrganizator;
            ELSE IF @versiune_curenta = 3
                EXEC usp_StergeOrganizator;
            ELSE IF @versiune_curenta = 2
                EXEC usp_StergeDefaultInscriere;
            ELSE IF @versiune_curenta = 1
                EXEC usp_RevinoDenumireLocatie;

            SET @versiune_curenta = @versiune_curenta - 1;
            UPDATE VersiuneBD SET versiune = @versiune_curenta;
        END;
    END TRY
    BEGIN CATCH
        THROW;
    END CATCH;
END;
GO

SELECT versiune FROM VersiuneBD;

EXEC usp_SchimbaVersiunea 1;