SELECT name FROM
    (SELECT DISTINCT id, name
        FROM
        people, directors, ratings
    WHERE
        ratings.movie_id = directors.movie_id
        and people.id = directors.person_id
        and ratings.rating >= 9)
;


--write a SQL query to list the names of all people who have
--directed a movie that received a rating of at least 9.0

--results in a table with 1 column and 2,236 rows.