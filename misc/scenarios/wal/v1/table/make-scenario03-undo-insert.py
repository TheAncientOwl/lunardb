# /bin/python3

import random


def main():
    lines = [
        'database drop Scenario_WAL_DB;',
        'database create Scenario_WAL_DB;',
        'database use Scenario_WAL_DB;',

        'schema Scenario_WAL_Schema { name: string; salary: float; };',
        'drop table Scenario_WAL_Table;',
        'create table Scenario_WAL_Table based on Scenario_WAL_Schema;',

        'insert into Scenario_WAL_Table objects [ {"name":"Bob","salary":"4000"} {"name":"George","salary":"4500"} {"name":"Akshan","salary":"1000000"} ];',
        'select from structure Scenario_WAL_Table where ( 1 == 1 ) fields [ salary, name ]',
    ]

    objects = [
        '{"name":"Bob1","salary":"1000"}',
        '{"name":"Bob2","salary":"2000"}',
        '{"name":"Bob3","salary":"3000"}',
        '{"name":"Bob4","salary":"4000"}',
        '{"name":"George1","salary":"10000"}',
        '{"name":"George2","salary":"20000"}',
        '{"name":"George3","salary":"30000"}',
        '{"name":"George4","salary":"40000"}',
        '{"name":"Akshan1","salary":"1000000"}'
        '{"name":"Akshan2","salary":"2000000"}'
        '{"name":"Akshan3","salary":"3000000"}'
        '{"name":"Akshan4","salary":"4000000"}'
    ]

    insert_objects = 100
    insert_lines = 100_000

    random_objects = ' '.join([random.choice(objects)
                              for _ in range(insert_objects)])
    insert_line = f'insert into Scenario_WAL_Table objects [ {random_objects} ];'

    with open("./scenario03-undo-insert.sql", "w") as scenario_file:
        scenario_file.writelines('\n'.join(lines) + '\n')

        for x in range(0, insert_lines):
            scenario_file.write(insert_line + '\n')


if __name__ == "__main__":
    main()
