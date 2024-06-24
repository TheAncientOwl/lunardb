# /bin/python3

import random


def main():
    lines = [
        'database drop Scenario_WAL_DB;',
        'database create Scenario_WAL_DB;',
        'database use Scenario_WAL_DB;',

        'schema Scenario_WAL_Schema { name: string; salary: float; };',
        'drop structure Scenario_WAL_Table;',
        'create table Scenario_WAL_Table based on Scenario_WAL_Schema;',
    ]

    objects = ['{"name":"Bob1","salary":"1000"}']

    insert_objects = 50_000
    random_objects = ' '.join(
        ['{"name":"Bob1","salary":"1000"}' for _ in range(insert_objects)])
    insert_line = f'insert into Scenario_WAL_Table objects [ {random_objects} ];'

    with open("./scenario04-undo-delete.sql", "w") as scenario_file:
        scenario_file.writelines('\n'.join(lines) + '\n')
        scenario_file.write(insert_line + '\n')
        scenario_file.write(
            'delete from structure Scenario_WAL_Table where ( name == Bob1 );')


if __name__ == "__main__":
    main()
