from building import *
import os

cwd = GetCurrentDir()
src = Glob('*.c')
CPPPATH = [cwd]
folder_name = os.path.basename(cwd)
group = DefineGroup(folder_name, src, depend = [''], CPPPATH = CPPPATH)

list = os.listdir(cwd)
for item in list:
    if os.path.isfile(os.path.join(cwd, item, 'SConscript')):
        group = group + SConscript(os.path.join(item, 'SConscript'))

Return('group')