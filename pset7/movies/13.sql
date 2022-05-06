SELECT DISTINCT(name) FROM people
WHERE id IN 
(SELECT person_id FROM stars WHERE movie_id IN
(SELECT movie_id FROM stars WHERE person_id IN
(SELECT id FROM people WHERE name IS 'Kevin Bacon' AND 
(SELECT id FROM people WHERE birth = 1958))))
EXCEPT 
SELECT name FROM people where name = 'Kevin Bacon';

--SELECT DISTINCT(name) FROM people 
--WHERE id IN
--(SELECT person_id FROM stars Where movie_id IN
--(SELECT movie_id FROM stars Where person_id IN
--(SELECT id FROM people WHERE name IS 'Kevin Bacon' and 
--(SELECT id FROM people WHERE birth = 1958))));