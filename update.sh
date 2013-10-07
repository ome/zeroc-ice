
#
# Script for adding a directory of Ice source files
# to the git repository. For example:
#
#   $ git clone git://github.com/ome/zeroc-ice.git
#   $ wget .../Ice-3.5.1.tar.gz
#   $ cd zeroc-ice
#   $ sh ../update.sh ../Ice-3.5.1.tar.gz
#
set -e
set -u
set -x

x="$1"
N=`basename ${x%.tar.gz}`
rm -rf *
tar xzf "$x"
find $N -type d -empty -exec touch {}/.gitignore \;

mv $N/* .
rmdir $N
git add -f .
git commit -a -m "$N"
git tag -s -m v.${N#Ice-} v.${N#Ice-}
[[ `git sb --ignored | wc -l` -eq 1 ]] || exit 1
