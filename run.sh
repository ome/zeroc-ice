
#
# Script for processing a directory of Ice source files
# into a single git repository. For example, prepare the
# following downloads:
#
#   $ ls -l *[0-9].tar.gz
#   Ice-1.0.0.tar.gz
#   Ice-1.0.1.tar.gz
#   ...
#   Ice-3.4.2.tar.gz
#
# and then execute this script.
#
set -e
set -u
set -x

rm -rf Git
mkdir Git
cd Git
git init
cd ..

for x in *[0-9].tar.gz
do
    cd Git
    N=${x%.tar.gz}
    rm -rf *
    tar xzf ../$N.tar.gz
    find $N -type d -empty -exec touch {}/.gitignore \;

    mv $N/* .
    rmdir $N
    git add -f .
    git commit -a -m "$N"
    git tag -s -m v.${N#Ice-} v.${N#Ice-}
    [[ `git sb --ignored | wc -l` -eq 1 ]] || exit 1
    cd ..
done
