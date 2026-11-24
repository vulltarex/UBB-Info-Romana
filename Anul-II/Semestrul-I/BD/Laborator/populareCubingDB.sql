USE CubingDB
GO

INSERT INTO Concurent (nume, prenume, data_nasterii)
VALUES
    ('Zemdegs', 'Feliks', '1995-12-20'),
    ('Park', 'Max', '2001-11-28'),
    ('Valk', 'Mats', '1996-05-04'),
    ('Kolasinski', 'Tymon', '2005-06-21'),
    ('Du', 'Yusheng', '1999-06-14'),
    ('Ponce', 'Patrick', '2001-03-15'),
    ('Filip', 'Cristian', '2006-01-22'),
    ('Weyer', 'Philipp', '1997-12-04'),
    ('Xu', 'Ruihang', '2008-06-10'),
    ('Wang', 'Zihan', '2006-09-22');

INSERT INTO Locatie (denumire, oras, adresa)
VALUES
    ('Sala Polivalenta', 'Bucuresti', 'Calea Piscului 10'),
    ('Centrul de Conferinte', 'Cluj-Napoca', 'Strada Memorandumului 15'),
    ('Casa de Cultura', 'Bucuresti', 'Strada Academiei 20');

INSERT INTO Competitie
    (denumire, data_incepere, data_incheiere, id_locatie)
VALUES
    ('Bucharest Cube Open 2025', '2025-03-15', '2025-03-16', 100),
    ('Cluj Cubing Challenge 2025', '2025-06-21', '2025-06-22', 101),
    ('Bucharest Winter Cubing 2025', '2025-12-06', '2025-12-07', 102);

INSERT INTO Puzzle (denumire)
VALUES
    ('2x2x2'),
    ('3x3x3'),
    ('4x4x4'),
    ('Pyraminx');

INSERT INTO Proba (denumire, id_puzzle)
VALUES
    ('2x2x2 Speed', 300),
    ('3x3x3 Speed', 301),
    ('3x3x3 One-Handed', 301),
    ('4x4x4 Speed', 302),
    ('Pyraminx Speed', 303);

INSERT INTO ProbaCompetitie (id_comp, id_proba)
VALUES
    (200, 400),
    (200, 401),
    (200, 403),
    (201, 401),
    (201, 402),
    (201, 404),
    (202, 400),
    (202, 401),
    (202, 403);

INSERT INTO Inscriere (id_concurent, id_comp, data_inscrierii)
VALUES
    (1, 200, '2025-02-10'),
    (2, 200, '2025-02-12'),
    (3, 200, '2025-02-15'),
    (4, 200, '2025-02-20'),
    (5, 200, '2025-03-01'),
    (1, 201, '2025-05-10'),
    (4, 201, '2025-05-12'),
    (6, 201, '2025-05-20'),
    (7, 201, '2025-06-01'),
    (2, 202, '2025-11-05'),
    (8, 202, '2025-11-10'),
    (9, 202, '2025-11-15'),
    (10, 202, '2025-11-20');

INSERT INTO ParticipareProba (id_inscriere, id_proba_comp)
VALUES
    (600, 500),
    (600, 501),
    (601, 501),
    (601, 502),
    (602, 501),
    (603, 500),
    (603, 501),
    (604, 501),
    (605, 503),
    (605, 504),
    (606, 503),
    (607, 505),
    (608, 503),
    (609, 507),
    (609, 508),
    (610, 508),
    (611, 506),
    (611, 507),
    (612, 507);

INSERT INTO Runda (id_proba_comp, nr_runda, denumire)
VALUES
    (500, 1, 'Finala'),
    (501, 1, 'Calificari'),
    (501, 2, 'Finala'),
    (502, 1, 'Finala'),
    (503, 1, 'Calificari'),
    (503, 2, 'Finala'),
    (504, 1, 'Finala'),
    (505, 1, 'Finala'),
    (506, 1, 'Finala'),
    (507, 1, 'Calificari'),
    (507, 2, 'Finala'),
    (508, 1, 'Finala');

INSERT INTO Incercare
    (id_participare, id_runda, nr_incercare, timp_ms)
VALUES
    -- Feliks: 2x2, Bucuresti
    (700, 800, 1, 2100),
    (700, 800, 2, 1850),
    (700, 800, 3, 2300),

    -- Feliks: 3x3, calificari si finala
    (701, 801, 1, 6250),
    (701, 801, 2, 5980),
    (701, 801, 3, 6410),
    (701, 802, 1, 5820),
    (701, 802, 2, 6100),
    (701, 802, 3, 5670),

    -- Max: 3x3, calificari si finala
    (702, 801, 1, 5510),
    (702, 801, 2, 5890),
    (702, 801, 3, 5320),
    (702, 802, 1, 5100),
    (702, 802, 2, 5450),
    (702, 802, 3, 5280),

    -- Max: 4x4
    (703, 803, 1, 19500),
    (703, 803, 2, 20100),
    (703, 803, 3, 18800),

    -- Mats: 3x3, calificari
    (704, 801, 1, 7200),
    (704, 801, 2, 6850),
    (704, 801, 3, 7410),

    -- Tymon: 2x2
    (705, 800, 1, 1780),
    (705, 800, 2, 2050),
    (705, 800, 3, 1920),

    -- Tymon: 3x3, calificari si finala
    (706, 801, 1, 5320),
    (706, 801, 2, 5610),
    (706, 801, 3, 5480),
    (706, 802, 1, 5190),
    (706, 802, 2, 5370),
    (706, 802, 3, 5020),

    -- Yusheng: 3x3, calificari
    (707, 801, 1, 7050),
    (707, 801, 2, 6320),
    (707, 801, 3, 6810),

    -- Feliks: 3x3, Cluj, calificari si finala
    (708, 804, 1, 6120),
    (708, 804, 2, 5910),
    (708, 804, 3, 6280),
    (708, 805, 1, 5750),
    (708, 805, 2, 6020),
    (708, 805, 3, 5890),

    -- Feliks: 3x3 cu o singura mana
    (709, 806, 1, 12500),
    (709, 806, 2, 13200),
    (709, 806, 3, 11900),

    -- Tymon: 3x3, Cluj, calificari si finala
    (710, 804, 1, 5210),
    (710, 804, 2, 5480),
    (710, 804, 3, 5350),
    (710, 805, 1, 4980),
    (710, 805, 2, 5120),
    (710, 805, 3, 5260),

    -- Patrick: Pyraminx
    (711, 807, 1, 4200),
    (711, 807, 2, 3850),
    (711, 807, 3, 4510),

    -- Eu: 3x3, calificari
    (712, 804, 1, 7850),
    (712, 804, 2, 8100),
    (712, 804, 3, 7620),

    -- Max: 3x3, competitia de iarna
    (713, 809, 1, 5420),
    (713, 809, 2, 5180),
    (713, 809, 3, 5610),
    (713, 810, 1, 5050),
    (713, 810, 2, 5320),
    (713, 810, 3, 5140),

    -- Max: 4x4, competitia de iarna
    (714, 811, 1, 18200),
    (714, 811, 2, 19100),
    (714, 811, 3, 18550),

    -- Philipp: 4x4
    (715, 811, 1, 24500),
    (715, 811, 2, 23800),
    (715, 811, 3, 25100),

    -- Ruihang: 2x2
    (716, 808, 1, 2250),
    (716, 808, 2, 1980),
    (716, 808, 3, 2410),

    -- Ruihang: 3x3, calificari si finala
    (717, 809, 1, 5710),
    (717, 809, 2, 5520),
    (717, 809, 3, 5890),
    (717, 810, 1, 5380),
    (717, 810, 2, 5610),
    (717, 810, 3, 5490),

    -- Zihan: 3x3, calificari
    (718, 809, 1, 6120),
    (718, 809, 2, 5850),
    (718, 809, 3, 6340);