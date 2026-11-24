INSERT INTO Inscrieri(id_s, id_a, data)
VALUES
    (7, 12, 20261031);

UPDATE Ateliere
SET locuri = 25
WHERE id_a = 12;

DELETE FROM Inscrieri WHERE id_s = 7, id_a = 12
