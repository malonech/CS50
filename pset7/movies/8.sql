SELECT name FROM
people JOIN stars ON people.id = stars.person_id
JOIN movies ON movie_id = movies.id
WHERE title = 'Toy Story';