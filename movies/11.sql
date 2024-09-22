SELECT movies.title FROM movies, ratings, people, stars
    WHERE movies.id = ratings.movie_id AND movies.id = stars.movie_id AND people.id = stars.person_id AND people.NAME = 'Chadwick Boseman'
    ORDER BY ratings.rating DESC
    LIMIT 5;