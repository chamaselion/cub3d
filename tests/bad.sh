# run_valgrind_bad_maps.sh
if [ ! -d valgrind_bad ]; then
    mkdir results/valgrind_bad
fi
for map in maps/bad/*.cub
do
    name=$(basename "$map" .cub)
    log="valgrind_bad/${name}.log"
    valgrind --leak-check=full ../cub3d "$map" > "$log" 2>&1
done