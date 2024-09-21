from setuptools import Extension, setup

module = Extension("symnmfmodule", sources=['symnmf.c', 'symnmfmodule.c'])
setup(name='symnmfmodule',
      version='1.0',
      description='symnmf for project',
      ext_modules=[module])
