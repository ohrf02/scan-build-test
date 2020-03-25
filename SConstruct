import os

env = Environment(CPPPATH='code-example/',
                  CPPDEFINES=[],
                  LIBS=[],
                  CXX='g++',
                  SCONS_CXX_STANDARD='c++14')

env["CC"] = os.getenv("CC") or env["CC"]
env["CXX"] = os.getenv("CXX") or env["CXX"]
env["ENV"].update(x for x in os.environ.items() if x[0].startswith("CCC_"))

SConscript('code-example/cpp/SConscript', exports='env')
