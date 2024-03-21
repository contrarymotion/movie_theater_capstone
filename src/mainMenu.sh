#!/bin/bash

# MySQL credentials
MYSQL_USER="root"
MYSQL_PASSWORD="student"
MYSQL_HOST="localhost"
MYSQL_DB="movie_theater"
SQL_FILE="setup.sql"

display_menu() {
    # RGB colors to indicate you are now in main menu
    # echo "Movie Theater Main Menu" 3x
    echo
    echo "=================================="
    echo -e "\e[31mMovie Theater Main Menu\e[0m" # red
    sleep .6
    echo -e "\e[32mMovie Theater Main Menu\e[0m" # green
    sleep .6
    echo -e "\e[34mMovie Theater Main Menu\e[0m" # blue
    sleep .6
    echo "=================================="
    sleep .6
    echo
    echo "What would you like to do today?"
    echo
    echo "1. Display list of movies and their showtimes"
    echo "2. Book seats"
    echo "3. Exit"
    echo
    echo "Please enter your choice (1-3):"
}

display_movies() {
    echo
    echo "=================================="
    echo -e "\e[44mList of Movies Playing:\e[0m"
    echo "=================================="
    echo
    echo "Dune: Part Two @ 3:00 PM"
    echo "Forrest Gump @ 6:00 PM"
    echo "Wonka @ 9:00 PM"
}

book_seats() {
    echo "Booking seats..."
    # Navigate to the project directory (if necessary)
    cd /Desktop/Capstone/src 2>/dev/null
    
    # Path to the SQL file
    # SQL_FILE="/Desktop/Capstone/src/setup.sql"

    # Execute the SQL file
    mysql -h $MYSQL_HOST -u $MYSQL_USER --password=$MYSQL_PASSWORD $MYSQL_DB < $SQL_FILE >/dev/null 2>&1

    # Run make to compile the project
    make clean >/dev/null && make >/dev/null 2>&1

    # Check if make was successful
    if [ $? -eq 0 ]; then
        # Execute the compiled program
        ./movie_theater
    else
        echo "Compilation failed."
    fi
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
done