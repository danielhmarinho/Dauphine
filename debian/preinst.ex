#!/bin/sh
# preinst script for dauphine
#
# see: dh_installdeb(1)

set -e
case "$1" in
           install)

wget https://www.lua.org/ftp/lua-5.2.4.tar.gz -P /user/local
tar -zxvf /tmp/lua-5.2.4.tar.gz -C /usr/local
cd /usr/local/lua-5.2.4
make linux install;;
    upgrade|abort-upgrade)
        ;;

    *)
            echo "postinst called with unknown argument \`$1'" >&2
        exit 0
        ;;
esac

#DEBHELPER#

exit 0
wget https://www.lua.org/ftp/lua-5.2.4.tar.gz -P /tmp

tar -zxvf /tmp/lua-5.2.4.tar.gz -C /tmp

cd /tmp/lua-5.2.4
make linux install

