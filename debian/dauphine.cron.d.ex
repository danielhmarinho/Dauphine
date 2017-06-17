#
# Regular cron jobs for the dauphine package
#
0 4	* * *	root	[ -x /usr/bin/dauphine_maintenance ] && /usr/bin/dauphine_maintenance
