
import os
from subprocess import check_call

# Work current dir
def work_dir(directory):
    directory = os.path.abspath(directory)
    print("Work in directory %r" % directory)
    files = [os.path.join(directory, f) for f in os.listdir(directory) if os.path.isfile(os.path.join(directory, f))]
    n = len(files)
    i = 1
    for f in files:
	    name, extension = os.path.splitext(f)
	    if extension == '.dot':
                    print("%d/%d %s" %(i, n, f))
                    check_call(['dot','-Tpng', f,'-o', os.path.join(directory, name+'.png')])
	    i+=1
                
# Work subdirs
work_dir('.')
_ = [work_dir(os.path.join('.', d)) for d in os.listdir('.') if os.path.isdir(d)]

