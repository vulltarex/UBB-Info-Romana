USE Blog222;
SELECT * FROM CuvinteCheie;
GO
--crearea unei proceduri stocate
CREATE PROCEDURE AdaugaCuvantCheie @nume VARCHAR(50)
AS
BEGIN
IF(EXISTS(SELECT * FROM CuvinteCheie WHERE nume=@nume))
	PRINT 'Acest cuvant cheie a fost deja adaugat in tabel!';
ELSE
	INSERT INTO CuvinteCheie (nume) VALUES (@nume);
END;
GO
--Apelarea procedurii stocate
EXEC AdaugaCuvantCheie 'Halloween';
SELECT * FROM CuvinteCheie;
GO
--Modificarea definitiei procedurii stocate
ALTER PROCEDURE AdaugaCuvantCheie @nume VARCHAR(50)
AS
BEGIN
SET NOCOUNT ON;
IF(EXISTS(SELECT * FROM CuvinteCheie WHERE nume=@nume))
	PRINT 'Acest cuvant cheie a fost deja adaugat in tabel!';
ELSE
	INSERT INTO CuvinteCheie (nume) VALUES (@nume);
END;
GO
--Afisarea definitiei procedurii stocate de pe server
EXEC sp_helptext 'dbo.AdaugaCuvantCheie';
--Apelul procedurii dupa modificarea definitiei sale
EXEC AdaugaCuvantCheie 'Pumpkin';
SELECT * FROM CuvinteCheie;
--Stergerea unei proceduri stocate
DROP PROCEDURE AdaugaCuvantCheie;