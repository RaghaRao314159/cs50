CREATE TABLE students (
    id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
    student_name TEXT NOT NULL );

CREATE TABLE houses (
    id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
    house TEXT NOT NULL,
    head TEXT NOT NULL );

CREATE TABLE house_assignments (
    student_id INTEGER  NOT NULL,
    house_id INTEGER NOT NULL,
    FOREIGN KEY(student_id) REFERENCES students(id),
    FOREIGN KEY(house_id) REFERENCES houses(house_id) );