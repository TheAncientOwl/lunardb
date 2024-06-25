# /bin/python3

import sys
import os


def printUsage():
    print('> Usage: python make-wal-scenario.py (table|collection) (insert|update|delete)')


def exitIfNotContained(actual, values):
    for value in values:
        if value == actual:
            return
    values_str = ', '.join(values)
    printUsage()
    print(
        f'Hint: \'{actual}\' is not a valid value, try one of [ {values_str} ] instead')
    exit(1)


def main():
    collection_type = ''
    scenario_type = ''

    if len(sys.argv) < 3:
        printUsage()
        exit(1)

    collection_type = sys.argv[1]
    scenario_type = sys.argv[2]

    exitIfNotContained(collection_type, ['table', 'collection'])
    exitIfNotContained(scenario_type, ['insert', 'update', 'delete'])

    type = sys.argv[1]
    db_name = f'WAL_Scenario_DB_{type}'
    schema_name = f'WAL_Scenario_Schema_{type}'
    collection_name = f'WAL_Scenario_Collection_{type}'

    setup = [
        f'database drop {db_name};',
        f'database create {db_name};',
        f'database use {db_name};',

        'schema ' + schema_name + ' { name: string; salary: float; };',
        f'drop structure {collection_name};',
        f'create {collection_type} {collection_name} based on {schema_name};',
    ]

    insert_objects = 100000
    object = '{"name":"Bob","salary":"5000"}'
    objects = ' '.join([object for _ in range(insert_objects)])
    insert_line = f'insert into {collection_name} objects [ {objects} ];'
    setup.append(insert_line)

    if scenario_type == 'delete':
        setup.append(
            f'delete from structure {collection_name} where ( name == Bob );')
    elif scenario_type == 'update':
        setup.append(
            f'update structure {collection_name} where ( name == Bob ) modify [ salary => 1000 ];'
        )

    scripts_path = os.path.join(os.getcwd(), 'large')
    if not os.path.exists(scripts_path):
        os.makedirs(scripts_path)

    with open(f'./large/{collection_type}_{scenario_type}.sql', 'w') as scenario_file:
        scenario_file.write('\n'.join(setup))


if __name__ == "__main__":
    main()
