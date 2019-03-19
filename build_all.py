import subprocess
import os
import sys

basePath = os.getcwd()

folders = ['copy', 'dynamicLibraries', 'dlopen', 'loadDynamicLibrary', 'lib_functions', 'passing_variables', 'min_syslibs']

for folder, n in zip(folders, range(len(folders))):
  print('#### {} BUILDING {}'.format(n+1, folder))
  ninja_folder = os.path.join(os.path.join(basePath, folder), 'ninja')
  output_folder = os.path.join(os.path.join(basePath, folder), 'output')
  if not os.path.exists(ninja_folder):
    os.mkdir(ninja_folder)
  if not os.path.exists(output_folder):
    os.mkdir(output_folder)

  os.chdir(ninja_folder)
  if len(sys.argv) > 1 and sys.argv[1] == 'clean' or not os.path.exists(os.path.join(ninja_folder, 'rules.ninja')):
    subprocess.call(['ninja', 'clean'])
    subprocess.call(['emcmake', 'cmake', '-G', 'Ninja', '..'], shell=True)

  subprocess.call(['ninja'])
