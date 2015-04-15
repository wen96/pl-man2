#!/usr/bin/python2.7

import sys

sys.stdout.write('CARAPAN\n')
sys.stdout.flush()
res=sys.stdin.readline()
sys.stdin.flush()
if res == 'COCAINUM\n':
	sys.stdout.write('bien'+'\n')
else:
	sys.stdout.write('mal'+'\n')

sys.stdout.flush()
