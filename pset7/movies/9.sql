SELECT name FROM people
JOIN stars ON people.id = stars.person_id
Join movies ON stars.movie_id = movies.id
WHERE year = 2004
ORDER BY birth;