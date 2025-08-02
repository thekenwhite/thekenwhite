
cmake -S . -B .cmake/target &&
cmake --build .cmake/target &&
if [ $# -eq 0 ]; then
    .cmake/output/_
else
    .cmake/output/$1
fi
