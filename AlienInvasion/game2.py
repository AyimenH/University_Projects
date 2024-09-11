import random
import re
import sys

# 100MB of characters
NUM_BYTES = (1024 ** 2) * 100
HEIGHT = 8
WIDTH = 8
STRENGTH = 9
CELL_WIDTH = 11

ANSI_CYAN = "\033[96m"
ANSI_END = "\033[0m"
ANSI_GREEN = "\033[92m"
ANSI_RED = "\033[91m"

class Alien:
    def __init__(self, board, coords, strength):
        self.board = board
        self.coords = coords
        self.strength = strength
        self.board.addAlien(self)
        self.x = coords[0]
        self.y = coords[1]
        self.squished = False
        self.value = bytearray(NUM_BYTES)
        self.children = []

    def __str__(self):
        return ANSI_RED + str(self.strength) + ANSI_END

    def doDeath(self):
        self.squished = True
        self.board.clearCell(self.coords)

    def doPop(self, strength=1):
        self.strength -= strength
        if self.strength < 1:
            self.doDeath()

    def doGrow(self):
        chance = random.randint(0, 9)
        if self.strength < STRENGTH and chance > 7:
            self.strength += 1

    def doTimestep(self):
        self.doTravel()
        self.doSpawn()
        self.doGrow()

    def doTravel(self):
        distx = random.randint(-1, 1)
        disty = random.randint(-1, 1)
        newx = self.x + distx
        newy = self.y + disty
        if self.inRange((newx, newy)):
            self.board.moveAlien(self.coords, (newx, newy))
            self.coords = (newx, newy)
    
    def doSpawn(self):
        emptySpace = self.findEmptySpace()
        neighbor = self.getNeighbor()
        chance = random.randint(0, 9)
        if neighbor != None and emptySpace != None and chance > 6:
            child = Alien(self.board, emptySpace, max(1, self.strength - 1))
            self.children.append(child)

    def findEmptySpace(self):
        adjacent = [(self.x + 1, self.y + 1), (self.x + 1, self.y), (self.x + 1, self.y - 1),
                    (self.x, self.y + 1), (self.x, self.y - 1), (self.x - 1, self.y - 1),
                    (self.x - 1, self.y), (self.x - 1, self.y + 1)]
        random.shuffle(adjacent)
        for coords in adjacent:
            if self.inRange(coords) and self.board.isEmpty(coords):
               return coords
        return None

    def getNeighbor(self):
        adjacent = [(self.x + 1, self.y + 1), (self.x + 1, self.y), (self.x + 1, self.y - 1),
                    (self.x, self.y + 1), (self.x, self.y - 1), (self.x - 1, self.y - 1),
                    (self.x - 1, self.y), (self.x - 1, self.y + 1)]
        neighbors = []
        for coords in adjacent:
            if self.inRange(coords):
                neighbor = self.board.getAlien(coords)
                if neighbor != None:
                    neighbors.append(neighbor)
        if len(neighbors) == 0:
            return None
        neighbor = neighbors[random.randint(0, len(neighbors) - 1)]
        return neighbor

    def inRange(self, coords):
        if coords[0] > 0 and coords[0] < self.board.width and coords[1] > 0 and coords[1] < self.board.height:
            return True
        return False

class Board:
    def isOverrun(self):
        overrunCounter = 0
        
        for i in range(self.width):
            for j in range(self.height):
                
                if self.board[i][j] is not None:
                    overrunCounter +=1
                    
        overrrunMaximum = self.width * self.height * 0.75
        
        return overrunCounter >= overrrunMaximum
    
#isOverrun returns a boolean that increments a counter for each square on the board that is filled
#then takes 8 * 8 * 0.75; might allow the user to change the 0.75 value for difficulty tiers
    
    def __init__(self, height, width):
        self.board = [[None for j in range(width)] for i in range(height)]
        self.height = height
        self.width = width
        self.nuked = {}
    
    def nuke(self, x, y):
        radius = [(x + 1, y + 1), (x + 1, y), (x + 1, y - 1), 
                (x, y + 1), (x, y), (x, y - 1),
                (x - 1, y + 1), (x - 1, y), (x - 1, y - 1)]

        for nukeX, nukeY in radius:
            if 0 <= nukeX < self.width and 0 <= nukeY < self.height:
                self.clearCell((nukeX, nukeY))
                
#radius is taken from adjacent in Alien and modifed to include itself and the square below it
#nuke checks if the radius is in bounds and if it is eradicates the aliens

    def __str__(self):
        string = ""
        for i in range(self.width):
            cells1 = []
            cells2 = []
            for j in range(self.height):
                alien = self.getAlien((i, j))
                cell1 = "|    -     ".format(alien)
                if alien != None and alien.squished == False:
                    cell1 = "|    {0}     ".format(alien)
                cell2 = "| ({0:02d},{1:02d})  ".format(i, j)
                if j == (self.height - 1):
                    cell1 += '|'
                    cell2 += '|'
                cells1.append(cell1)
                cells2.append(cell2)
            string += '-' * ((len(cells1) * CELL_WIDTH) + 1)
            string += '\n'
            for cell in cells1:
                string += cell
            string += '\n'
            for cell in cells2:
                string += cell
            string += '\n'
            if i == (self.width - 1):
                string += '-' * ((len(cells1) * CELL_WIDTH) + 1)
                string += '\n'
        return string

    def addAlien(self, alien):
        coords = alien.coords
        if self.board[coords[0]][coords[1]] is None:
            self.board[coords[0]][coords[1]] = alien
            
            return True

    def clearCell(self, coords):
        self.board[coords[0]][coords[1]] = None

    def doTimestep(self):
        for i in range(self.width):
            for j in range(self.height):
                alien = self.getAlien((i, j))
                if alien != None and alien.squished == False:
                    alien.doTimestep()

    def getAlien(self, coords):
        return self.board[coords[0]][coords[1]]

    def isEmpty(self, coords=None):
        if coords == None:
            flag = 0
            for i in range(self.width):
                for j in range(self.height):
                    if self.getAlien((i, j)) != None:
                        flag = 1
                        return False
            return True
        if self.getAlien(coords) != None:
            return False
        return True

    def moveAlien(self, oldCoords, newCoords):
        if not self.isEmpty(oldCoords) and self.isEmpty(newCoords):
            alien = self.getAlien(oldCoords)
            self.clearCell(oldCoords)
            self.board[newCoords[0]][newCoords[1]] = alien

    def squish(self, coords, strength=1):
        if coords[0] < 0 or coords[0] >= self.width:
            print("Invalid coordinates. Lose your turn.")
            return -1
        elif coords[1] < 0 or coords[1] >= self.height:
            print("Invalid coordinates. Lose your turn.")
            return -1
        elif self.isEmpty(coords):
            print("Cell is empty. Lose your turn.")
            return -1
        else:
            alien = self.getAlien(coords)
            if alien != None:
                score = strength if alien.strength > strength else alien.strength
                alien.doPop(strength)
                return score
        return -1

class Player:
    def __init__(self, board, troops, bombs):
        self.board = board
        self.score = 0
        self.strength = 1
        self.turn = 0
        self.nukeCooldown = 5
        
    def roundsUntilNuke(self):
        if self.nukeCooldown > 0:
            self.nukeCooldown -= 1
                
#roundsUntilNuke; commenting so I remember that I added this
                
    def nukeAvailable(self):
        return self.nukeCooldown == 0
        
#nukeAvailable is a bool that returns true when the nuke is ready for deployment

    def useNuke(self, x, y):
        if self.nukeAvailable():
            self.board.nuke(x,y)
            self.nukeCooldown = 5
            print(f"Nuke deployed at ({x}, {y}). Cooldown is now {self.nukeCooldown} rounds.")

#useNuke uses our nukeAvailable bool to deploy our nuke at the users input
#coolDown is then reset back to 5; might edit cooldown to coincide with diffculty

    def __str__(self):
        width = self.board.width
        size = (width * CELL_WIDTH) + 1
        string = "TURN: {0}\tSTRENGTH: {1}\tSCORE: ".format(self.turn, self.strength)
        if self.score > 0:
            string += ANSI_GREEN + str(self.score) + ANSI_END
        elif self.score == 0:
            string += str(self.score)
        else:
            string += ANSI_RED + str(self.score) + ANSI_END
        return "{0:^{1}}".format(string, size)

    def doTimestep(self):
        self.turn += 1
        self.roundsUntilNuke()
        
#modified doTimestep to decrement nuke timer every round

def printTree(alien, depth=0):
    tree = "{0}({1}):".format(str(alien), depth)
    if len(alien.children) == 0:
        return tree
    else:
        for child in alien.children:
            tree += printTree(child, depth + 1)
    return tree

def printTrees(aliens):
    for alien in aliens:
        tree = printTree(alien)
        print(tree)
        
#Mark & Sweep

def markAliens(aliens):
    markedAliens = []
    
    def findAndMark(alien):
        if alien.squished:
            if alien not in markedAliens:
                markedAliens.append(alien)
                
            for child in alien.children:
                if child.squished:
                    findAndMark(child)
                    
    for alien in aliens:
        if alien.squished:
            findAndMark(alien)
            
    return markedAliens

#markAliens starts by adding squished aliens to our markedAlien list
#then its children if squished, the list of all squished aliens is returned
#this list will be used by sweepAliens to only target squished aliens

def sweepAliens(aliens, markedAliens):
    aliveAliens = []
    
    for alien in aliens:
        if alien not in markedAliens:
            aliveAliens.append(alien)
            
        else:
            keepChildren(alien, aliveAliens, markedAliens)
            
    for alien in aliveAliens:
        sweepChildren(alien, markedAliens)
        
    return aliveAliens

#sweepAliens utilizes the list from markAliens to direct what method is called
#if an alien is not squished then it gets appended to aliveAliens
#if an alien is squished (look at keepChildren comments)
#for all aliens in aliveAliens (look at sweepChildren)

def keepChildren(alien, aliveAliens, markedAliens):
    for child in alien.children:
        
        if child not in markedAliens and child not in aliveAliens:
            aliveAliens.append(child)

#keepChildren checks for each child if its not squished and not already in aliveAliens
#then appends it to aliveAliens

def sweepChildren(alien, markedAliens):
    newChildren = []
    
    for child in alien.children:
        
        if child not in markedAliens:
            newChildren.append(child)
            
    alien.children = newChildren

#sweepChildren checks each child alien of squished aliens and adds unsquished to newChildren
#each aliens children are updated to only include unsquished aliens

def garbageCollection(aliens):
    markedAliens = markAliens(aliens)
    aliens = sweepAliens(aliens, markedAliens)
    return aliens

#garbageCollection utilizes mark and sweep together and updates aliens used in main to be only alive aliens

#Mark & Sweep

if __name__ == "__main__":
    seed = 0
    if len(sys.argv) > 1:
        seed = sum([ord(c) for c in sys.argv[1]])
    random.seed(seed)
    aliens = []
    board = Board(HEIGHT, WIDTH)
    player = Player(board, 3, 3)
    userin = ""
    while(userin.upper() != "QUIT" and userin.upper() != "EXIT"):
        x = random.randint(0, WIDTH - 1)
        y = random.randint(0, HEIGHT - 1)
        s = random.randint(1, STRENGTH)
        if player.turn == 0:
            s = 5
            
        if board.isEmpty((x, y)):
            alien = Alien(board, (x, y), s)
            if board.addAlien(alien):
                aliens.append(alien)
            
        print(board)
        print(player)
        
        userin = input("Choose your attack (squish or nuke): ")
        
        if userin.lower() == "nuke":
            if player.nukeAvailable():
                try:
                    x = int(input("Provide the x coordinate for the nuke: "))
                    y = int(input("Provide the y coordinate for the nuke: "))
                    player.useNuke(x, y)
                except ValueError:
                    print("Invalid input. Coordinates must be integers.")
            else:
                print(f"Nuke not ready. Please wait {player.nukeCooldown} more rounds.")

        elif userin.lower() == "squish":
            coords = input("Choose a coordinate to attack (x,y): ")
            search = re.search(r"\(?(-?\d+)[, ]+(-?\d+)\)?", coords)
            (userx, usery) = search.groups() if search != None else (None, None)
            if userx is None or usery is None:
                if userin.upper() == "QUIT" or userin.upper() == "EXIT":
                    continue
                elif userin.upper() == "TREES":
                    printTrees(aliens)
                    continue
                print("Invalid coordinates. Lose your turn.")
            else:
                userx, usery = int(userx), int(usery)
                score = board.squish((userx, usery), player.strength)
                if score > 0:
                    player.strength += 1 if player.strength < STRENGTH else 0
                elif score <= 0:
                    player.strength -= 1 if player.strength > 1 else 0
                player.score += score
                
        board.doTimestep()
        player.doTimestep()
        
        if player.turn % 2 == 0:
            aliens = garbageCollection(aliens)
            
        #garbageCollection is run every other move
        
        if board.isOverrun():
            print("Game over: The aliens have overrun the board!")
            exit(0)
            
        #exits when the board is at or above 75% capacity
        
        if board.isEmpty():
            print("You win!")
            exit(0)
