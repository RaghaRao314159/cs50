import sqlite3 as sql


def retreive_old_data():
    old_connection = sql.connect("roster.db")
    db_old = old_connection.cursor()

    result = db_old.execute("SELECT * FROM students").fetchall()

    old_connection.close()
    return result


def add_students(db_name,result):
    connection = sql.connect(db_name)
    db = connection.cursor()
    for i in result:
        db.execute("INSERT INTO students (student_name) VALUES (?)",(i[1],))
    connection.commit()
    connection.close()


def add_houses(db_name,result):
    house_set = set()
    for i in result:
        house_set.add((i[2],i[3]))

    connection = sql.connect(db_name)
    db = connection.cursor()
    for i in house_set:
        db.execute("INSERT INTO houses (house, head) VALUES (?,?)",(i[0],i[1]))
    connection.commit()
    connection.close()

def add_house_assignments(db_name,result):
    connection = sql.connect(db_name)
    db = connection.cursor()
    for i in result:
        name = i[1]
        house = i[2]
        student_id = db.execute("SELECT id FROM students WHERE student_name = ?",(name,)).fetchall()[0][0]
        house_id = db.execute("SELECT id FROM houses WHERE house = ?",(house,)).fetchall()[0][0]
        db.execute("INSERT INTO house_assignments (student_id,house_id) VALUES (?,?)",(student_id,house_id))
    connection.commit()
    connection.close()



result = retreive_old_data()

#add_students("new_roster.db",result)
#add_houses("new_roster.db",result)

add_house_assignments("new_roster.db",result)





