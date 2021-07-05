from sys import setdlopenflags
from ctypes import RTLD_GLOBAL
setdlopenflags (RTLD_GLOBAL | 2)

from bloc_component import Bloc
from blockchain_component import Blockchain
b=Bloc()
b2=Bloc()
blockchain=Blockchain(b.to_json())
print(blockchain)