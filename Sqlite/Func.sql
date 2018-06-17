DECLARE
    f INT;
    c INT;
	average NUMERIC;
BEGIN
	IF _score > 7 OR _score < 0 OR _score = 0 THEN
		RAISE SQLSTATE 'DB017';
	ELSE
		SELECT PR.paper_id INTO f
			FROM PaperReviewing as PR JOIN Paper ON Paper.id = PR.paper_id
			WHERE PR.paper_id = _paper_id AND PR.reviewer_id = _reviewer_id AND Paper.accepted IS NULL;
		IF NOT FOUND THEN
			RAISE SQLSTATE 'DB017';
		ELSE 
			UPDATE PaperReviewing SET score = _score
				WHERE paper_id = _paper_id AND reviewer_id = _reviewer_id;
            SELECT COUNT(*) INTO c
                FROM PaperReviewing
                WHERE paper_id = _paper_id and score IS NOT NULL;
			IF c = 3 THEN
                SELECT AVG(PaperReviewing.score)::NUMERIC INTO average
                    FROM PaperReviewing
					WHERE paper_id = _paper_id;
				IF average > 4 THEN
					UPDATE Paper SET accepted = TRUE
                        WHERE Paper.id = _paper_id;
				ELSE
					UPDATE Paper SET accepted = FALSE
                        WHERE Paper.id = _paper_id;
				END IF;
			END IF;
		END IF;
	END IF;
END;
