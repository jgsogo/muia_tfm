
import os
import sys
from subprocess import check_call

# Work current dir
def work_dir(directory, force):
    directory = os.path.abspath(directory)
    print("Work in directory %r" % directory)
    files = [os.path.join(directory, f) for f in os.listdir(directory) if os.path.isfile(os.path.join(directory, f))]
    n = len(files)
    i = 1
    for f in files:
        name, extension = os.path.splitext(f)
        if extension == '.dot':
            print("%d/%d %s" %(i, n, f))
            output = os.path.join(directory, name+'.png')
            if force or not os.path.isfile(output):
                check_call(['dot','-Tpng', f,'-o', output])
        i+=1

# Clean directory
def clean_dir(directory):
    directory = os.path.abspath(directory)
    print("Work in directory %r" % directory)
    files = [os.path.join(directory, f) for f in os.listdir(directory) if os.path.isfile(os.path.join(directory, f))]
    for f in files:
        name, extension = os.path.splitext(f)
        if extension == '.png':
            os.remove(f)
    if directory.endswith("-brief"):
        os.rmdir(directory)


if __name__=='__main__':
    force = sys.argv[1]=='force' if len(sys.argv)==2 else False
    clean = sys.argv[1]=='clean' if len(sys.argv)==2 else False
    
    if clean:
        clean_dir('.')
        _ = [clean_dir(os.path.join('.', d)) for d in os.listdir('.') if os.path.isdir(d)]
                
    else:
        work_dir('.', force)
        _ = [work_dir(os.path.join('.', d), force) for d in os.listdir('.') if os.path.isdir(d)]
     