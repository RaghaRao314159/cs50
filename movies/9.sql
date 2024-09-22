SELECT DISTINCT people.name FROM people, stars, movies
    WHERE stars.person_id = people.id AND movies.id = stars.movie_id AND movies.year = 2004
    ORDER BY people.birth ASC;