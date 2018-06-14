SELECT SUM(B.b)::BIGINT FROM (
	SELECT MAX(A.a) as b FROM (
		SELECT COUNT(0) as a FROM Planet
		JOIN Flight on Planet.id = Flight.planet_id
        WHERE Planet.galaxy = 2
		GROUP BY Planet.id) AS A
	UNION
	SELECT COUNT(0) as b FROM Planet
    WHERE Planet.galaxy = 2) as B
