#include <iostream>
#include <vector>

// Block class definition
class Block {
private:  // Private member variables for encapsulation
    int width;
    int height;
    int position;

public:
    static int totalBlocks;  // Static variable to track total blocks

    // Constructor with 'this' pointer
    Block(int width, int height, int position) {
        this->width = width;
        this->height = height;
        this->position = position;
        totalBlocks++;  // Increment total block count
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

// Tower class definition
class Tower {
private:  // Private member variables to encapsulate tower details
    std::vector<Block*> blocks;
    int height;
    bool stability;

public:
    Tower() : height(0), stability(true) {}

    // Add a block to the tower
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

    // Check tower stability
    void checkStability() {
        for (Block* block : blocks) {
            if (!block->isStable()) {
                stability = false; // This line causes the error
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

    ~Tower() {
        for (Block* block : blocks) {
            delete block;  // Free memory
        }
    }
};

// Player class definition
class Player {
private:  // Private member variables for encapsulation
    std::string name;
    int score;

public:
    static int highScore;  // Static variable to track the highest score

    // Constructor with 'this' pointer
    Player(std::string name) {
        this->name = name;
        this->score = 0;
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

    // Example method chaining usage
    void chainScoreIncrement() {
        this->increaseScore().increaseScore();  // Chaining method calls
    }

    // Place a block in the game
    void placeBlock(Tower& tower, Block* block) {
        tower.addBlock(block);
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
        player = new Player(playerName);
    }

    // Start the game
    void startGame() {
        std::cout << "Game started.\n";
        // Game loop can be added here
    }

    // End the game
    void endGame() {
        std::cout << "Game over.\n";
        std::cout << "Highest score achieved: " << Player::getHighScore() << "\n";  // Display high score
        std::cout << "Total blocks created: " << Block::getTotalBlocks() << "\n";  // Display total blocks
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
        new Block(10, 2, 0),
        new Block(8, 3, 1),
        new Block(6, 4, -1)  // Misaligned block
    };

    // Iterate through the array of blocks and place them in the tower
    for (int i = 0; i < 3; i++) {
        game->player->placeBlock(*game->tower, blocks[i]);
    }

    game->tower->checkStability();

    if (game->checkGameOver()) {
        game->endGame();
    }

    delete game;  // Free memory

    return 0;
}