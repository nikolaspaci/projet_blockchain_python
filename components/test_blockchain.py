import json
import pprint
from sys import setdlopenflags
from ctypes import RTLD_GLOBAL
setdlopenflags (RTLD_GLOBAL | 2)

from bloc_component import Bloc
from blockchain_component import Blockchain

### Lecture du mock JSON et instanciation de blockchain
f = open('blockChain.json')
data = json.load(f)
blockchain=Blockchain(data)

###Verification de l'instanciation et des méthodes from_Json() et to_Json()
def testCreateBlockchainFromJson(data,blockchain):
    print("---Verification de l'instanciation et des méthodes from_Json() et to_Json()---")
    print("Contenu JSON du mock:\n")
    pprint.pprint(data)
    print("\n")

    print("Contenu de l'objet blockchain chargé:\n")
    pprint.pprint(blockchain.to_json())
    print("\n")

###Verification de la méthode getBloc()
def testGetBloc(data,blockchain):
    print("---Verification de la méthode getBloc()---")
    print("Contenu du premier bloc du mock:\n")
    pprint.pprint(data['blocs'][0])
    print("\n")

    print("Contenu du premier bloc de l'objet blockchain chargé:\n")
    pprint.pprint(blockchain.getBloc(0).to_json())
    print("\n")

###Verification du nombre de blocs avec la méthode getNbBloc()
def testNBBloc(data,blockchain):
    print("---Verification de la méthode getNbBloc()---")
    print("Nombre de blocs dans le mock: ",len(data['blocs']))
    print("Nombre de blocs dans l'objet blockchain: ",blockchain.getNbBloc())
    print("Identique: ",len(data['blocs'])==blockchain.getNbBloc(),"\n")

###Verification de l'ajout d'un bloc correct avec les méthodes verifyPreviousBlock et addBloc
def testVerifPreviousHashAndAddCorrectBloc(blockchain):
    print("---Verification de l'ajout d'un bloc correct avec les méthodes verifyPreviousBlock et addBloc---")
    JsonblocToAddCorrect= {
        'hash': '000123456789A123456789A123456789A123456789A123456789A123456789B',
        'nonce': 42,
        'num': 0,
        'previous_hash': '000123456789A123456789A123456789A123456789A123456789A123456789A',
        'transactions': '',
        'txm': ''
    }
    blocToAddCorrect=Bloc(JsonblocToAddCorrect)
    print("Contenu du bloc à ajouter avec previous hash correct:")
    pprint.pprint(blocToAddCorrect.to_json())

    previousBlock=blockchain.getBloc(blockchain.getNbBloc()-1)
    print("Vérification du previous hash, retourne true si identique: "\
          ,blockchain.verifyPreviousBlock(blocToAddCorrect,previousBlock),"\n")

    print("Ajout du bloc dans la blockchain")
    blockchain.addBloc(blocToAddCorrect)
    print("Verification que le bloc est bien présent en fin de liste")
    lastBlock=blockchain.getBloc(blockchain.getNbBloc()-1)
    print(blocToAddCorrect.to_json()==lastBlock.to_json())
    print("Dernier bloc de la liste: ")
    pprint.pprint(lastBlock.to_json())
    print("\n")

###Verification du non ajout d'un bloc incorrect avec les méthodes verifyPreviousBlock et addBloc
def testVerifPreviousHashAndAddIncorrectBloc(blockchain):
    print("---Verification  du non ajout d'un bloc incorrect avec les méthodes verifyPreviousBlock et addBloc---")
    JsonblocToAddIncorrect= {
        'hash': '000123456789A123456789A123456789A123456789A123456789A123456766A',
        'nonce': 42,
        'num': 0,
        'previous_hash': '000123456789A123456789A123456789A123456789A123456789A123456784B',
        'transactions': '',
        'txm': ''
    }
    blocToAddIncorrect=Bloc(JsonblocToAddIncorrect)
    print("Contenu du bloc à essayer d'ajouter avec previous hash incorrect:")
    pprint.pprint(blocToAddIncorrect.to_json())
    prevBlock=blockchain.getBloc(blockchain.getNbBloc()-1)
    print("Vérification du previous hash, retourne false si pas identique: " \
          ,blockchain.verifyPreviousBlock(blocToAddIncorrect,prevBlock),"\n")
    print("Tentative d'ajout du bloc dans la blockchain")
    blockchain.addBloc(blocToAddIncorrect)
    print("Verification que le bloc n'est pas ajouté en fin de liste")
    lastBlock=blockchain.getBloc(blockchain.getNbBloc()-1)
    print("Affiche false si le dernier bloc ne correspond pas au bloc: ",\
          blocToAddIncorrect.to_json()==lastBlock.to_json())
    print("Dernier bloc de la liste: ")
    pprint.pprint(lastBlock.to_json())

testCreateBlockchainFromJson(data,blockchain)
testNBBloc(data,blockchain)
testGetBloc(data,blockchain)
testVerifPreviousHashAndAddCorrectBloc(blockchain)
testVerifPreviousHashAndAddIncorrectBloc(blockchain)