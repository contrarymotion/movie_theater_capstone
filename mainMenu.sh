#!/bin/bash

# MySQL credentials
DB_USER="root"
DB_PASS="student"
DB_NAME="movie_theater"

display_menu() {
    echo "Welcome to the Movie Theater!"
    echo "1. Display list of movies"
    echo "2. Book seats"
    echo "3. Exit"
    echo "Please enter your choice (1-3):"
}

display_movies() {
    echo "List of Movies:"
    echo "Dune: Part Two"
    echo "Forrest Gump"
    echo "Wonka"
}

book_seats() {
    echo "Booking seats..."
    # Add code here to handle seat booking
}

while true; do
    display_menu
    read choice
    case $choice in
        1)
            display_movies
            ;;
        2)
            book_seats
            ;;
        3)
            echo "Exiting..."
            exit 0
            ;;
        *)
            echo "Invalid choice. Please enter a number between 1 and 3."
            ;;
    esac
done2
