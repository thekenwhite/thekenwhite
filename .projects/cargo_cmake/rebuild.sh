
rm -rf .cmake/target

cmake -S . -B .cmake/target &&
cmake --build .cmake/target &&
if [ $# -ne 0 ]; then
    .cmake/output/$1
fi
