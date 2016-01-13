#!/sbin/sh

set -e

modelid=`getprop ro.boot.mid`

case $modelid in
    "0P3P10000") variant="t6vzw" ;;
    "0P3P20000") variant="t6dwg" ;;
    "0P3P30000") variant="t6dug" ;;
    "0P3P40000") variant="t6tl" ;;
    "0P3P70000") variant="t6spr" ;;
    *)           variant="t6" ;;
esac

basedir="/system/blobs/$variant/"
cd $basedir
chmod 755 bin/*
find . -type f | while read file; do ln -s $basedir$file /system/$file ; done

exit 0
