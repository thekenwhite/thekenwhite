
git add .

if [ $# -eq 0 ]; then
    msg="commit"
else
    msg="$@"
fi

git commit -am "$msg"

git pull

git push
