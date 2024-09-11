class Node:
    def __init__(self, value, ID):
        self.value = value
        self.ID = ID
        self.left = None
        self.right = None

    def isLeafNode(self):
        return self.left is None and self.right is None
#for modeling the first example; already running into issues though

def twentyQuestions(root):
    current = root
    questionCount = 0
    
    while questionCount < 20:
        answer = input(current.value + ' (y/n): ')
        questionCount += 1
        
        if (answer == 'y'):
            if (not current.isLeafNode() and current.left is not None):
                current = current.left
#if yes child node exists


                
            else:
                print("I've run out of things to guess! Help me learn how to beat you next time.")
                newValue = input('Provide a new thing to add to my knowledge: ')
                print('Thanks! I will place ' + newValue + " where it belongs based on what you've told me.")
                
                newQuestion = 'Is it a(n) ' + newValue + '?'
                current.left = Node(newQuestion, 2 * current.ID + 1)
                break
#leftover from before adding isLeafNode, don't think this is ever reached
            
        if (answer == 'n'):
            if (not current.isLeafNode() and current.right is not None):
                current = current.right
#if 'no' child node exists

            else:
                print("You’ve stumped me! Help me learn how to beat you next time.")
                print("I really thought it was going to be a(n) " + current.value + "! Give me a new yes/no question relevant to " + current.value + ".")
                
                newQuestion = input("Provide new question: ")
                newChildPath = input('Would a(n) ' + current.value + ' be associated with a yes or no answer to your new question? (y/n): ')
                
                if (newChildPath == 'y'):
                    current.right = Node(newQuestion, 2 * current.ID + 2)
                    current.right.left = Node(current.value, 2 * current.right.ID + 1)
                    
                elif (newChildPath == 'n'):
                    current.right = Node(newQuestion, 2 * current.ID + 2)
                    current.right.right = Node(current.value, 2 * current.right.ID + 2)
                break
#current.ID is multiplied by two and added by 1 or 2 depending on if its left or right; to be used in input tree

if __name__ == '__main__':
    print('Starting the 20 Questions game')
    
    value = input('Provide first question: ')
    root = Node(value, 0)
    keepPlaying = True
    
    while keepPlaying:
        keepPlaying = twentyQuestions(root)
    
    print("I had fun! Let's play again sometime.")
