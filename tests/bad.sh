# run_valgrind_bad_maps.sh
if [ ! -d valgrind_bad ]; then
    mkdir -p results/valgrind_bad
fi
for map in maps/bad/*.cub
do
    name=$(basename "$map" .cub)
    log="results/valgrind_bad/${name}.log"
    valgrind --leak-check=full ../cub3D "$map" > "$log" 2>&1
done