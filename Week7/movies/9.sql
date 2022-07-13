SELECT DISTINCT(name)
    FROM
        movies, stars, people
    WHERE movies.id = movie_id
        and people.id = person_id
        and year = 2004
    ORDER BY birth
;