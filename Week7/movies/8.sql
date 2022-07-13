SELECT name FROM movies, stars, people
    WHERE movies.id = movie_id
    and people.id = person_id
    and title = 'Toy Story';