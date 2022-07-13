SELECT title FROM movies
    WHERE id IN
    (SELECT movie_id FROM stars, people
    WHERE people.id = stars.person_id
    AND name = 'Johnny Depp'
    AND movie_id IN
    (SELECT movie_id FROM stars, people
    WHERE people.id = stars.person_id
    AND name = 'Helena Bonham Carter'))
;

--write a SQL query to list the titles of all movies
--in which both Johnny Depp and Helena Bonham Carter starred

-- results in a table with 1 column and 6 rows.