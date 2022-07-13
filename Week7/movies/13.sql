SELECT DISTINCT name FROM people, stars
    WHERE people.id = stars.person_id
    AND name IS NOT 'Kevin Bacon'
    and stars.movie_id IN
    (SELECT stars.movie_id FROM stars, people
    WHERE people.id = stars.person_id
    AND name = 'Kevin Bacon'
    AND birth = 1958)
    ;


-- write a SQL query to list the names of all people
-- who starred in a movie in which Kevin Bacon also starred.

-- results in a table with 1 column and 185 rows.