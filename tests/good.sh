# run_valgrind_good_maps.sh
if [ ! -d valgrind_good ]; then
    mkdir -p results/valgrind_good
fi
for map in maps/good/*.cub
do
    name=$(basename "$map" .cub)
    log="results/valgrind_good/${name}.log"
    valgrind --leak-check=full ../cub3D "$map" > "$log" 2>&1 &
    pid_valgrind=$!
    sleep 10
    win_id=$(xdotool search --pid $pid_valgrind | head -n 1)
    if [ -n "$win_id" ]; then
        end_time=`date +%s`
        end_time=`expr $end_time + 20`
        while [ `date +%s` -lt $end_time ]
        do
            keys="E A S D Left Right"
            set -- $keys
            count=6
            rand=`od -An -N2 -tu2 < /dev/urandom | tr -d ' '`
            index=`expr $rand % $count + 1`
            key=`eval echo \\$$index`
            xdotool windowactivate "$win_id"
            xdotool keydown --window "$win_id" "$key"
            sleep 1
            xdotool keyup --window "$win_id" "$key"
        done
        xdotool windowactivate "$win_id"
        xdotool key --window "$win_id" Escape
    fi
    wait $pid_valgrind
done