-- This file sets up the movie_theater database for new users

-- Drop database if exists
DROP DATABASE IF EXISTS movie_theater;

-- Create database
CREATE DATABASE IF NOT EXISTS movie_theater DEFAULT CHARACTER SET utf8;

-- Use the movie_theater database
USE movie_theater;

-- Drop procedure if exists
DROP PROCEDURE IF EXISTS InsertMovieSeatMappings;

-- Create user table
CREATE TABLE users (
user_id SMALLINT AUTO_INCREMENT PRIMARY KEY,
email VARCHAR(255) UNIQUE NOT NULL
);

-- Create movie table
CREATE TABLE movie (
movie_id SMALLINT AUTO_INCREMENT PRIMARY KEY,
title VARCHAR(255) NOT NULL,
genre VARCHAR(255),
runtime TIME,
rating VARCHAR(10),
start_time TIME,
end_time TIME
);

-- Insert movie data
INSERT INTO movie (movie_id, title, genre, runtime, rating, start_time, end_time) VALUES
(1, 'Dune: Part Two', 'Action/Fantasy', '02:26:00', 'PG13', '15:00:00', '17:26:00'),
(2, 'Forrest Gump', 'Drama', '02:22:00', 'PG13', '18:00:00', '20:22:00'),
(3, 'Wonka', 'Family/Comedy', '01:52:00', 'PG', '21:00:00', '22:52:00');

-- Create price table
CREATE TABLE price (
price_id SMALLINT AUTO_INCREMENT PRIMARY KEY,
movie_id SMALLINT NOT NULL,
price DECIMAL(10, 2),
FOREIGN KEY (movie_id) REFERENCES movie(movie_id)
);

-- Insert price data
INSERT INTO price (price_id, movie_id, price) VALUES
(1, 1, 12.00),
(2, 2, 12.00),
(3, 3, 12.00);

-- Create seat_map table
CREATE TABLE seat_map (
seat_map_id SMALLINT AUTO_INCREMENT PRIMARY KEY,
map_id SMALLINT NOT NULL,
seat_row CHAR(1),
seat_column SMALLINT,
occupied BOOLEAN
);

-- Insert seat_map data
INSERT INTO seat_map (map_id, seat_row, seat_column, occupied) VALUES
(1, 'A', 1, FALSE), (1, 'A', 2, FALSE), (1, 'A', 3, FALSE), (1, 'A', 4, FALSE),
(1, 'A', 5, FALSE), (1, 'A', 6, FALSE), (1, 'A', 7, FALSE), (1, 'A', 8, FALSE),
(1, 'A', 9, FALSE), (1, 'A', 10, FALSE), (1, 'B', 1, FALSE), (1, 'B', 2, FALSE),
(1, 'B', 3, FALSE), (1, 'B', 4, FALSE), (1, 'B', 5, FALSE), (1, 'B', 6, FALSE),
(1, 'B', 7, FALSE), (1, 'B', 8, FALSE), (1, 'B', 9, FALSE), (1, 'B', 10, FALSE),
(1, 'C', 1, FALSE), (1, 'C', 2, FALSE), (1, 'C', 3, FALSE), (1, 'C', 4, FALSE),
(1, 'C', 5, FALSE), (1, 'C', 6, FALSE), (1, 'C', 7, FALSE), (1, 'C', 8, FALSE),
(1, 'C', 9, FALSE), (1, 'C', 10, FALSE), (1, 'D', 1, FALSE), (1, 'D', 2, FALSE),
(1, 'D', 3, FALSE), (1, 'D', 4, FALSE), (1, 'D', 5, FALSE), (1, 'D', 6, FALSE),
(1, 'D', 7, FALSE), (1, 'D', 8, FALSE), (1, 'D', 9, FALSE), (1, 'D', 10, FALSE),
(1, 'E', 1, FALSE), (1, 'E', 2, FALSE), (1, 'E', 3, FALSE), (1, 'E', 4, FALSE),
(1, 'E', 5, FALSE), (1, 'E', 6, FALSE), (1, 'E', 7, FALSE), (1, 'E', 8, FALSE),
(1, 'E', 9, FALSE), (1, 'E', 10, FALSE), (1, 'F', 1, FALSE), (1, 'F', 2, FALSE),
(1, 'F', 3, FALSE), (1, 'F', 4, FALSE), (1, 'F', 5, FALSE), (1, 'F', 6, FALSE),
(1, 'F', 7, FALSE), (1, 'F', 8, FALSE), (1, 'F', 9, FALSE), (1, 'F', 10, FALSE),
(1, 'G', 1, FALSE), (1, 'G', 2, FALSE), (1, 'G', 3, FALSE), (1, 'G', 4, FALSE),
(1, 'G', 5, FALSE), (1, 'G', 6, FALSE), (1, 'G', 7, FALSE), (1, 'G', 8, FALSE),
(1, 'G', 9, FALSE), (1, 'G', 10, FALSE), (1, 'H', 1, FALSE), (1, 'H', 2, FALSE),
(1, 'H', 3, FALSE), (1, 'H', 4, FALSE), (1, 'H', 5, FALSE), (1, 'H', 6, FALSE),
(1, 'H', 7, FALSE), (1, 'H', 8, FALSE), (1, 'H', 9, FALSE), (1, 'H', 10, FALSE),
(1, 'I', 1, FALSE), (1, 'I', 2, FALSE), (1, 'I', 3, FALSE), (1, 'I', 4, FALSE),
(1, 'I', 5, FALSE), (1, 'I', 6, FALSE), (1, 'I', 7, FALSE), (1, 'I', 8, FALSE),
(1, 'I', 9, FALSE), (1, 'I', 10, FALSE), (1, 'J', 1, FALSE), (1, 'J', 2, FALSE),
(1, 'J', 3, FALSE), (1, 'J', 4, FALSE), (1, 'J', 5, FALSE), (1, 'J', 6, FALSE),
(1, 'J', 7, FALSE), (1, 'J', 8, FALSE), (1, 'J', 9, FALSE), (1, 'J', 10, FALSE),
(2, 'A', 1, FALSE), (2, 'A', 2, FALSE), (2, 'A', 3, FALSE), (2, 'A', 4, FALSE),
(2, 'A', 5, FALSE), (2, 'A', 6, FALSE), (2, 'A', 7, FALSE), (2, 'A', 8, FALSE),
(2, 'A', 9, FALSE), (2, 'A', 10, FALSE), (2, 'B', 1, FALSE), (2, 'B', 2, FALSE),
(2, 'B', 3, FALSE), (2, 'B', 4, FALSE), (2, 'B', 5, FALSE), (2, 'B', 6, FALSE),
(2, 'B', 7, FALSE), (2, 'B', 8, FALSE), (2, 'B', 9, FALSE), (2, 'B', 10, FALSE),
(2, 'C', 1, FALSE), (2, 'C', 2, FALSE), (2, 'C', 3, FALSE), (2, 'C', 4, FALSE),
(2, 'C', 5, FALSE), (2, 'C', 6, FALSE), (2, 'C', 7, FALSE), (2, 'C', 8, FALSE),
(2, 'C', 9, FALSE), (2, 'C', 10, FALSE), (2, 'D', 1, FALSE), (2, 'D', 2, FALSE),
(2, 'D', 3, FALSE), (2, 'D', 4, FALSE), (2, 'D', 5, FALSE), (2, 'D', 6, FALSE),
(2, 'D', 7, FALSE), (2, 'D', 8, FALSE), (2, 'D', 9, FALSE), (2, 'D', 10, FALSE),
(2, 'E', 1, FALSE), (2, 'E', 2, FALSE), (2, 'E', 3, FALSE), (2, 'E', 4, FALSE),
(2, 'E', 5, FALSE), (2, 'E', 6, FALSE), (2, 'E', 7, FALSE), (2, 'E', 8, FALSE),
(2, 'E', 9, FALSE), (2, 'E', 10, FALSE), (2, 'F', 1, FALSE), (2, 'F', 2, FALSE),
(2, 'F', 3, FALSE), (2, 'F', 4, FALSE), (2, 'F', 5, FALSE), (2, 'F', 6, FALSE),
(2, 'F', 7, FALSE), (2, 'F', 8, FALSE), (2, 'F', 9, FALSE), (2, 'F', 10, FALSE),
(2, 'G', 1, FALSE), (2, 'G', 2, FALSE), (2, 'G', 3, FALSE), (2, 'G', 4, FALSE),
(2, 'G', 5, FALSE), (2, 'G', 6, FALSE), (2, 'G', 7, FALSE), (2, 'G', 8, FALSE),
(2, 'G', 9, FALSE), (2, 'G', 10, FALSE), (2, 'H', 1, FALSE), (2, 'H', 2, FALSE),
(2, 'H', 3, FALSE), (2, 'H', 4, FALSE), (2, 'H', 5, FALSE), (2, 'H', 6, FALSE),
(2, 'H', 7, FALSE), (2, 'H', 8, FALSE), (2, 'H', 9, FALSE), (2, 'H', 10, FALSE), 
(2, 'I', 1, FALSE), (2, 'I', 2, FALSE), (2, 'I', 3, FALSE), (2, 'I', 4, FALSE),
(2, 'I', 5, FALSE), (2, 'I', 6, FALSE), (2, 'I', 7, FALSE), (2, 'I', 8, FALSE),
(2, 'I', 9, FALSE), (2, 'I', 10, FALSE), (2, 'J', 1, FALSE), (2, 'J', 2, FALSE),
(2, 'J', 3, FALSE), (2, 'J', 4, FALSE), (2, 'J', 5, FALSE), (2, 'J', 6, FALSE),
(2, 'J', 7, FALSE), (2, 'J', 8, FALSE), (2, 'J', 9, FALSE), (2, 'J', 10, FALSE),
(3, 'A', 1, FALSE), (3, 'A', 2, FALSE), (3, 'A', 3, FALSE), (3, 'A', 4, FALSE),
(3, 'A', 5, FALSE), (3, 'A', 6, FALSE), (3, 'A', 7, FALSE), (3, 'A', 8, FALSE),
(3, 'A', 9, FALSE), (3, 'A', 10, FALSE), (3, 'B', 1, FALSE), (3, 'B', 2, FALSE),
(3, 'B', 3, FALSE), (3, 'B', 4, FALSE), (3, 'B', 5, FALSE), (3, 'B', 6, FALSE),
(3, 'B', 7, FALSE), (3, 'B', 8, FALSE), (3, 'B', 9, FALSE), (3, 'B', 10, FALSE),
(3, 'C', 1, FALSE), (3, 'C', 2, FALSE), (3, 'C', 3, FALSE), (3, 'C', 4, FALSE),
(3, 'C', 5, FALSE), (3, 'C', 6, FALSE), (3, 'C', 7, FALSE), (3, 'C', 8, FALSE),
(3, 'C', 9, FALSE), (3, 'C', 10, FALSE), (3, 'D', 1, FALSE), (3, 'D', 2, FALSE),
(3, 'D', 3, FALSE), (3, 'D', 4, FALSE), (3, 'D', 5, FALSE), (3, 'D', 6, FALSE),
(3, 'D', 7, FALSE), (3, 'D', 8, FALSE), (3, 'D', 9, FALSE), (3, 'D', 10, FALSE),
(3, 'E', 1, FALSE), (3, 'E', 2, FALSE), (3, 'E', 3, FALSE), (3, 'E', 4, FALSE),
(3, 'E', 5, FALSE), (3, 'E', 6, FALSE), (3, 'E', 7, FALSE), (3, 'E', 8, FALSE),
(3, 'E', 9, FALSE), (3, 'E', 10, FALSE), (3, 'F', 1, FALSE), (3, 'F', 2, FALSE),
(3, 'F', 3, FALSE), (3, 'F', 4, FALSE), (3, 'F', 5, FALSE), (3, 'F', 6, FALSE),
(3, 'F', 7, FALSE), (3, 'F', 8, FALSE), (3, 'F', 9, FALSE), (3, 'F', 10, FALSE),
(3, 'G', 1, FALSE), (3, 'G', 2, FALSE), (3, 'G', 3, FALSE), (3, 'G', 4, FALSE),
(3, 'G', 5, FALSE), (3, 'G', 6, FALSE), (3, 'G', 7, FALSE), (3, 'G', 8, FALSE),
(3, 'G', 9, FALSE), (3, 'G', 10, FALSE), (3, 'H', 1, FALSE), (3, 'H', 2, FALSE),
(3, 'H', 3, FALSE), (3, 'H', 4, FALSE), (3, 'H', 5, FALSE), (3, 'H', 6, FALSE),
(3, 'H', 7, FALSE), (3, 'H', 8, FALSE), (3, 'H', 9, FALSE), (3, 'H', 10, FALSE),
(3, 'I', 1, FALSE), (3, 'I', 2, FALSE), (3, 'I', 3, FALSE), (3, 'I', 4, FALSE),
(3, 'I', 5, FALSE), (3, 'I', 6, FALSE), (3, 'I', 7, FALSE), (3, 'I', 8, FALSE),
(3, 'I', 9, FALSE), (3, 'I', 10, FALSE), (3, 'J', 1, FALSE), (3, 'J', 2, FALSE),
(3, 'J', 3, FALSE), (3, 'J', 4, FALSE), (3, 'J', 5, FALSE), (3, 'J', 6, FALSE),
(3, 'J', 7, FALSE), (3, 'J', 8, FALSE), (3, 'J', 9, FALSE), (3, 'J', 10, FALSE);

-- Create movie_map table
CREATE TABLE movie_map (
movie_map_id SMALLINT AUTO_INCREMENT PRIMARY KEY,
movie_id SMALLINT NOT NULL,
seat_map_id SMALLINT NOT NULL,
FOREIGN KEY (movie_id) REFERENCES movie(movie_id),
FOREIGN KEY (seat_map_id) REFERENCES seat_map(seat_map_id)
);

-- Create checkout table
CREATE TABLE checkout (
checkout_id SMALLINT AUTO_INCREMENT PRIMARY KEY,
confirmation VARCHAR(15),
user_id SMALLINT NOT NULL,
price_id SMALLINT NOT NULL,
movie_id SMALLINT NOT NULL,
FOREIGN KEY (user_id) REFERENCES users(user_id),
FOREIGN KEY (price_id) REFERENCES price(price_id),
FOREIGN KEY (movie_id) REFERENCES movie(movie_id)
);

-- Create procedure
DELIMITER $$
CREATE PROCEDURE InsertMovieSeatMappings()
BEGIN
DECLARE i INT DEFAULT 1;
DECLARE total_seats_per_movie INT DEFAULT 100; -- Assuming each movie has 100 unique seats
TRUNCATE TABLE movie_map; -- Clear previous mappings

-- Insert mappings for movie 1
WHILE i <= total_seats_per_movie DO
INSERT INTO movie_map (movie_id, seat_map_id) VALUES (1, i);
SET i = i + 1;
END WHILE;
SET i = 1; -- Reset counter for next movie

-- Insert mappings for movie 2
WHILE i <= total_seats_per_movie DO
INSERT INTO movie_map (movie_id, seat_map_id) VALUES (2, i + total_seats_per_movie);
SET i = i + 1;
END WHILE;
SET i = 1; -- Reset counter for next movie

-- Insert mappings for movie 3
WHILE i <= total_seats_per_movie DO
INSERT INTO movie_map (movie_id, seat_map_id) VALUES (3, i + (total_seats_per_movie * 2));
SET i = i + 1;
END WHILE;
END$$
DELIMITER ;