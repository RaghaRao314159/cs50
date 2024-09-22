SELECT bc_title from
    (SELECT title as bc_title, movies.id as bc_movie_id FROM movies
        JOIN stars ON movies.id = stars.movie_id
        JOIN people ON people.id = stars.person_id
        WHERE people.name = 'Bradley Cooper')
    JOIN stars ON bc_movie_id = stars.movie_id
    JOIN people ON people.id = stars.person_id
    WHERE people.name = 'Jennifer Lawrence';