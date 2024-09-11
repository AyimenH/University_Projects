import sys

class Node:
    def __init__(self, ID, nodeType, value, parentID = None, leftID = None, rightID = None):
        self.ID = ID
        self.nodeType = nodeType
        self.value = value
        self.parentID = parentID
        self.leftID = leftID
        self.rightID = rightID
        
        self.left = None
        self.right = None

#Class based on file input section

def readFile(filePath):
    treeNodes = {}
    file = open(filePath, 'r')
    
    for line in file:
        sections = line.strip().split(':')
        
        nodeID, nodeType, value, parentID, leftID, rightID = [section if section else None for section in sections]
        node = Node(int(nodeID), nodeType, value, parentID, leftID, rightID)
        treeNodes[int(nodeID)] = node
    
    file.close()
    return treeNodes

#Open file in read-only and split each line of the file up by the ':'
#Each section is used for their part in the new node
#Newly created nodes are put into a dictionary based on the ID
#Section if statement is to check if a part of the line is empty and if it is make it None

def buildTree(treeNodes):
    for node in treeNodes.values():
        if node.leftID is not None:
            node.left = treeNodes.get(int(node.leftID))
            
        if node.rightID is not None:
            node.right =  treeNodes.get(int(node.rightID))
            
        if node.parentID is None:
            root = node
            
    return root

#Take in the dictionary of nodes from treeNodes
#Assign the children node if they exist based on their ID

def playGame(root):
    current = root
    questionCount = 0
    
    parent = None
    lastAnswer = None
    
    while current.nodeType == 'question':
        parent = current
        if questionCount >= 20:
            print("I've run out of questions! You win!")
            break
        
        answer = input(current.value + ' (y/n): ')
        if answer == 'y':
            lastAnswer = 'yes'
            current = current.left
            
        if answer == 'n':
            lastAnswer = 'no'
            current = current.right
        
        questionCount += 1
    
    if current.nodeType == 'answer':
        finalAnswer = input('Is it ' + current.value + '? (y/n): ')
        if finalAnswer == 'y':
            print("I win! Better luck next time.")
        
        if finalAnswer == 'n':
            print("You've stumped me! Help me learn from this game.")
            playerAddedNode(current, parent, lastAnswer, treeNodes)
                
#When the nodeType is question it will go to its child node depending on answer
#When the nodeType is answer it will decide a response depending on answer
#Parent & lastAnswer are used for adding a new node (explained more in playerAddedNode)
#By setting parent to the current node you can keep track of it ^

def playerAddedNode(current, parent, lastAnswer, treeNodes):
    print('I really thought it was going to be a(n) ' + current.value + '! Give me a new yes/no question relevant to a(n) ' + current.value)
    
    newQuestion = input('Provide new question: ')
    newAnswer = input('Would a(n) ' + current.value + ' be associated with a yes or no answer to your new question? (y/n): ')
    
    newQuestionNode = Node(max(treeNodes.keys()) + 1, 'question', newQuestion, None, None, None)
    
    if newAnswer == 'y':
        newQuestionNode.left = current
    if newAnswer == 'n':
        newQuestionNode.right = current
        
    if lastAnswer == 'yes':
        parent.left = newQuestionNode
    if lastAnswer == 'no':
        parent.right = newQuestionNode
        
    treeNodes[newQuestionNode.ID] = newQuestionNode
    
#newQuestionNode creates a node with an ID that is +1 current largest nodeID (ID is the key for my dict)
#newQuestion would be the value and all other segments are the same as a regular node
#lastAnswer allows us to determine whether its a left or right child based on the parent node of our newQuestionNode

if __name__ == '__main__':
    print('Starting the 20 Questions game.')
    print('Thanks for passing me my database!')
    
    filePath = sys.argv[1]
    treeNodes = readFile(filePath)
    rootNode = buildTree(treeNodes)
    
    while True:
        playGame(rootNode)
        playAgain = input("Play again? (y/n): ")
        
        if playAgain != 'y':
            print("I had fun! Let's play again sometime.")
            break

#filePath is assigned to the second thing in cmd line
#while playAgain is y the game will keep looping
