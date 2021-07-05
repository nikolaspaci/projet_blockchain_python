import json
from sys import setdlopenflags
from ctypes import RTLD_GLOBAL
setdlopenflags (RTLD_GLOBAL | 2)

from bloc_component import Bloc
from blockchain_component import Blockchain
#lecture json mock
f = open('blockChain.json')
data = json.load(f)
#deserialisation blockchain
blockchain=Blockchain(data)
print(blockchain.to_json())