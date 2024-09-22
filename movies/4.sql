SELECT COUNT(title) FROM movies
    JOIN ratings on movies.id = ratings.movie_id
    WHERE ABS(rating - 10.0) <= 0.001;