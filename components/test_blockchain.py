import json
from sys import setdlopenflags
from ctypes import RTLD_GLOBAL
setdlopenflags (RTLD_GLOBAL | 2)

from bloc_component import Bloc
from blockchain_component import Blockchain
f = open('blockChain.json')
data = json.load(f)

from bloc_component import Bloc
from blockchain_component import Blockchain
print(data)
blocchain=Blockchain(data)