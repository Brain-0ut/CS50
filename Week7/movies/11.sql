SELECT title
    FROM
        movies, stars, people, ratings
    WHERE
        movies.id = stars.movie_id
        and movies.id = ratings.movie_id
        and people.id = person_id
        and name = 'Chadwick Boseman'
    ORDER BY rating DESC
    LIMIT 5
;
--write a SQL query to list the titles of the five
--highest rated movies (in order) that Chadwick
--Boseman starred in, starting with the highest rated.

-- results in a table with 1 column and 5 rows.