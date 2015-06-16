
import os
from subprocess import check_call

files = [f for f in os.listdir('.') if os.path.isfile(f)]
for f in files:
	name, extension = os.path.splitext(f)
	if extension == '.dot':
                print(f)
                check_call(['dot','-Tpng', f,'-o', name+'.png'])
