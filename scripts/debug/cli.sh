export LUNARDB_ROOT_PASSWORD="root"
cp ./lunardb.config.json ./build/src/LunarDB/CLI/lunardb.config.json
./build/src/LunarDB/CLI/LunarDB_CLI.debug "$@"
