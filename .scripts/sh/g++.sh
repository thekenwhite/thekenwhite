
if [ $# -eq 0 ]; then
    bin="_"
else
    bin="$1"
fi

command="g++"

type="cc"

path="$ROOT/.snippets/$type"

source="$path/$bin.$type"

target="$ROOT/.target/$type"

mkdir -p $target 2> /dev/null

$command $source -o $target/$bin

$target/$bin
