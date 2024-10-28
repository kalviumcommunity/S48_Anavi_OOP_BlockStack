#include <iostream>
#include <vector>

// Base class Entity for common traits (Abstraction example)
class Entity {
protected:  // Protected access specifier to allow access in derived classes
    int id;

public:
    Entity() : id(0) {}  // Default constructor
    Entity(int id) : id(id) {}  // Parameterized constructor

    int getId() const {
        return id;
    }
};

// Block class inherits from Entity (Single Inheritance)
class Block : public Entity {
private:  // Private member variables for encapsulation
    int width;
    int height;
    int position;

public:
    static int totalBlocks;  // Static variable to track total blocks

    // Default constructor
    Block() : Entity(0), width(0), height(0), position(0) {
        totalBlocks++;  // Increment total block count
    }

    // Parameterized constructor
    Block(int id, int width, int height, int position) : Entity(id) {
        this->width = width;
        this->height = height;
        this->position = position;
        totalBlocks++;  // Increment total block count
    }

    // Copy constructor
    Block(const Block& other) : Entity(other.id) {
        this->width = other.width;
        this->height = other.height;
        this->position = other.position;
        totalBlocks++;  // Increment total block count
    }

    // Destructor
    ~Block() {
        totalBlocks--;  // Decrement total block count
    }

    // Accessor methods
    int getWidth() const {
        return width;
    }

    int getHeight() const {
        return height;
    }

    int getPosition() const {
        return position;
    }

    // Mutator methods
    void setWidth(int newWidth) {
        width = newWidth;
    }

    void setHeight(int newHeight) {
        height = newHeight;
    }

    void setPosition(int newPosition) {
        position = newPosition;
    }

    // Handle block misalignment
    Block& fallOff() {
        if (this->position != 0) {  // Using 'this' pointer
            std::cout << "Block is misaligned, losing stability.\n";
            this->setWidth(this->getWidth() - 1);  // Use mutator
        }
        return *this;  // Return the current object for method chaining
    }

    // Check if block is stable
    bool isStable() const {
        return this->getWidth() > 0;  // Using accessor
    }

    // Static method to get total blocks
    static int getTotalBlocks() {
        return totalBlocks;
    }
};

// Initialize static variable
int Block::totalBlocks = 0;

// Derived class HeavyBlock inherits from Block (Multilevel Inheritance)
class HeavyBlock : public Block {
private:
    int weight;

public:
    // Constructor for HeavyBlock
    HeavyBlock(int id, int width, int height, int position, int weight)
        : Block(id, width, height, position), weight(weight) {}

    int getWeight() const {
        return weight;
    }

    void setWeight(int newWeight) {
        weight = newWeight;
    }

    // Overriding the fallOff method (Polymorphism concept)
    HeavyBlock& fallOff() {
        std::cout << "Heavy block falling!\n";
        Block::fallOff();  // Call the base class method
        return *this;
    }
};

// Tower class definition
class Tower {
private:  // Private member variables to encapsulate tower details
    std::vector<Block*> blocks;
    int height;
    bool stability;

public:
    // Default constructor
    Tower() : height(0), stability(true) {}

    // Copy constructor
    Tower(const Tower& other) {
        this->height = other.height;
        this->stability = other.stability;
        for (Block* block : other.blocks) {
            blocks.push_back(new Block(*block));  // Use copy constructor of Block
        }
    }

    // Destructor
    ~Tower() {
        for (Block* block : blocks) {
            delete block;  // Free memory
        }
    }

    // Overloaded addBlock method for Block
    void addBlock(Block* block) {
        block->fallOff();  // Handle misalignment
        if (block->isStable()) {
            blocks.push_back(block);
            height += block->getHeight();  // Use accessor
            std::cout << "Block added to the tower. Tower height: " << height << "\n";
        } else {
            stability = false;
            std::cout << "Block is unstable, not added to the tower.\n";
        }
    }

    // Overloaded addBlock method for HeavyBlock (Polymorphism example)
    void addBlock(HeavyBlock* heavyBlock) {
        heavyBlock->fallOff();  // Specialized handling for HeavyBlock
        if (heavyBlock->isStable()) {
            blocks.push_back(heavyBlock);
            height += heavyBlock->getHeight();
            std::cout << "HeavyBlock added to the tower. Tower height: " << height << "\n";
        } else {
            stability = false;
            std::cout << "HeavyBlock is unstable, not added to the tower.\n";
        }
    }

    // Check tower stability
    void checkStability() {
        for (Block* block : blocks) {
            if (!block->isStable()) {
                stability = false;
                break;
            }
        }
        if (!stability) {
            std::cout << "Tower has collapsed!\n";
        } else {
            std::cout << "Tower is stable.\n";
        }
    }

    // Accessor method to check stability
    bool isStable() const {
        return stability;  // Return the current stability state
    }
};

// Player class definition (Single Inheritance from Entity)
class Player : public Entity {
private:  // Private member variables for encapsulation
    std::string name;
    int score;

public:
    static int highScore;  // Static variable to track the highest score

    // Default constructor
    Player() : Entity(0), name("Unnamed"), score(0) {
        // Initialize with default values
    }

    // Parameterized constructor
    Player(int id, std::string name) : Entity(id), name(name), score(0) {}

    // Copy constructor
    Player(const Player& other) : Entity(other.id) {
        this->name = other.name;
        this->score = other.score;
    }

    // Destructor
    ~Player() {
        // Clean-up code can be added here if needed
    }

    // Accessor methods
    std::string getName() const {
        return name;
    }

    int getScore() const {
        return score;
    }

    // Mutator methods
    void setScore(int newScore) {
        score = newScore;
    }

    // Increase player score
    Player& increaseScore() {
        this->setScore(this->getScore() + 10);  // Use mutator
        if (this->score > highScore) {
            highScore = this->score;  // Update high score
        }
        std::cout << this->getName() << "'s score: " << this->getScore() << "\n";  // Using accessor
        return *this;  // Return the current object for method chaining
    }

    // Place a block in the game
    void placeBlock(Tower& tower, Block* block) {
        tower.addBlock(block);
        increaseScore();
    }

    // Place a heavy block in the game (using polymorphism with overloaded addBlock)
    void placeBlock(Tower& tower, HeavyBlock* heavyBlock) {
        tower.addBlock(heavyBlock);
        increaseScore();
    }

    // Static method to get the high score
    static int getHighScore() {
        return highScore;
    }
};

// Initialize static variable
int Player::highScore = 0;

// Game class definition
class Game {
public:
    Tower* tower;
    Player* player;

    Game(std::string playerName) {
        tower = new Tower();
        player = new Player(1, playerName);
    }

    // Start the game
    void startGame() {
        std::cout << "Game started.\n";
    }

    // End the game
    void endGame() {
        std::cout << "Game over.\n";
        std::cout << "Highest score achieved: " << Player::getHighScore() << "\n";
        std::cout << "Total blocks created: " << Block::getTotalBlocks() << "\n";
    }

    // Check if game is over
    bool checkGameOver() {
        return !tower->isStable();  // Use the accessor method
    }

    ~Game() {
        delete tower;  // Free memory
        delete player;  // Free memory
    }
};

int main() {
    Game* game = new Game("Player1");
    game->startGame();

    // Create an array of Block pointers
    Block* blocks[] = {
        new Block(1, 10, 2, 0),
        new Block(2, 8, 3, 0),
        new HeavyBlock(3, 6, 4, 0, 20),  // Array of objects with different types
    };

    for (int i = 0; i < 3; ++i) {
        game->player->placeBlock(*game->tower, blocks[i]);
        game->tower->checkStability();
        if (game->checkGameOver()) {
            break;
        }
    }

    game->endGame();

    // Clean-up memory
    for (int i = 0; i < 3; ++i) {
        delete blocks[i];  // Free memory for each block
    }
    delete game;  // Free memory for game
    return 0;
}
