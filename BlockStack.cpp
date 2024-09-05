#include <iostream>
#include <vector>

// Block class definition
class Block {
public:
    int width;
    int height;
    int position;

    // Constructor with 'this' pointer
    Block(int width, int height, int position) {
        this->width = width;
        this->height = height;
        this->position = position;
    }

    // Handle block misalignment
    Block& fallOff() {
        if (this->position != 0) {  // Using 'this' pointer
            std::cout << "Block is misaligned, losing stability.\n";
            this->width -= 1;  // Example of misalignment handling using 'this'
        }
        return *this;  // Return the current object for method chaining
    }

    // Check if block is stable
    bool isStable() {
        return this->width > 0;  // Using 'this' pointer
    }
};

// Tower class definition
class Tower {
public:
    std::vector<Block*> blocks;
    int height;
    bool stability;

    Tower() : height(0), stability(true) {}

    // Add a block to the tower
    void addBlock(Block* block) {
        block->fallOff();  // Handle misalignment
        if (block->isStable()) {
            blocks.push_back(block);
            height += block->height;
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

    ~Tower() {
        for (Block* block : blocks) {
            delete block;  // Free memory
        }
    }
};

// Player class definition
class Player {
public:
    std::string name;
    int score;

    // Constructor with 'this' pointer
    Player(std::string name) {
        this->name = name;
        this->score = 0;
    }

    // Increase player score
    Player& increaseScore() {
        this->score += 10;  // Using 'this' pointer
        std::cout << this->name << "'s score: " << this->score << "\n";  // Using 'this'
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
};

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
    }

    // Check if game is over
    bool checkGameOver() {
        return !tower->stability;
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