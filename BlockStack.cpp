#include <iostream>
#include <vector>

// Block class definition
class Block {
public:
    int width;
    int height;
    int position;

    Block(int w, int h, int p) : width(w), height(h), position(p) {}

    // Handle block misalignment
    void fallOff() {
        if (position != 0) {
            std::cout << "Block is misaligned, losing stability.\n";
            width -= 1;  // Example of misalignment handling
        }
    }

    // Check if block is stable
    bool isStable() {
        return width > 0;
    }
};

// Tower class definition
class Tower {
public:
    std::vector<Block> blocks;
    int height;
    bool stability;

    Tower() : height(0), stability(true) {}

    // Add a block to the tower
    void addBlock(Block block) {
        block.fallOff();  // Handle misalignment
        if (block.isStable()) {
            blocks.push_back(block);
            height += block.height;
            std::cout << "Block added to the tower. Tower height: " << height << "\n";
        } else {
            stability = false;
            std::cout << "Block is unstable, not added to the tower.\n";
        }
    }

    // Check tower stability
    void checkStability() {
        for (Block block : blocks) {
            if (!block.isStable()) {
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
};

// Player class definition
class Player {
public:
    std::string name;
    int score;

    Player(std::string playerName) : name(playerName), score(0) {}

    // Place a block in the game
    void placeBlock(Tower& tower, Block block) {
        tower.addBlock(block);
        increaseScore();
    }

    // Increase player score
    void increaseScore() {
        score += 10;  // Example of scoring
        std::cout << name << "'s score: " << score << "\n";
    }
};

// Game class definition
class Game {
public:
    Tower tower;
    Player player;

    Game(std::string playerName) : player(playerName) {}

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
        return !tower.stability;
    }
};


int main() {
    Game game("Player1");
    game.startGame();

    Block block1(10, 2, 0);
    Block block2(8, 3, 1);
    Block block3(6, 4, -1);  // Misaligned block

    game.player.placeBlock(game.tower, block1);
    game.player.placeBlock(game.tower, block2);
    game.player.placeBlock(game.tower, block3);

    game.tower.checkStability();

    if (game.checkGameOver()) {
        game.endGame();
    }

    return 0;
}