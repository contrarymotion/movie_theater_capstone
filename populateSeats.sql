-- Define the maximum number of rows and seats per row
SET @max_rows = 10;
SET @seats_per_row = 10;

-- Initialize the row and seat counters
SET @row_counter = 1;
SET @seat_counter = 1;

-- Loop through each auditorium
SELECT auditorium_id, total_seats FROM auditorium;
BEGIN
  DECLARE done INT DEFAULT FALSE;
  DECLARE auditorium_id INT;
  DECLARE total_seats INT;
  DECLARE cursor_cur CURSOR FOR SELECT auditorium_id, total_seats FROM auditorium;
  DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;

  OPEN cursor_cur;

  read_loop: LOOP
    FETCH cursor_cur INTO auditorium_id, total_seats;
    IF done THEN
      LEAVE read_loop;
    END IF;
    
    -- Loop through each seat for the current auditorium
    WHILE @row_counter <= @max_rows DO
      WHILE @seat_counter <= @seats_per_row DO
        INSERT INTO seat (auditorium_id, seat_number)
        VALUES (auditorium_id, CONCAT(CHAR(96 + @row_counter), '-', @seat_counter));
        
        SET @seat_counter := @seat_counter + 1;
      END WHILE;
      
      -- Reset seat counter and increment row counter
      SET @seat_counter := 1;
      SET @row_counter := @row_counter + 1;
    END WHILE;
    
    -- Reset row counter for the next auditorium
    SET @row_counter := 1;
  END LOOP;

  CLOSE cursor_cur;
END;
