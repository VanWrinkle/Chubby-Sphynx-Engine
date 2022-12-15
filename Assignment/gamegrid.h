//
// Created by anmar on 12/12/2022.
//

#ifndef PROG2002_GAMEGRID_H
#define PROG2002_GAMEGRID_H

#include <random>
#include <vector>
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Direction {
    UP, DOWN, LEFT, RIGHT, FORWARD
};

template <unsigned X, unsigned Y>
class GameGrid {
private:
    struct ActiveBlock { // Grid coordinates of an active block
        int x {};
        int y {};
        int z {};
    };

    enum {
        FULL = 1
    };

    int m_gameGrid[Y][X][X] {}; ///< Array containing all static blocks
    glm::vec3 m_dimensions;     ///< In world dimensions of game grid
    std::vector<ActiveBlock> m_activeBlocks; ///< Vector of all active blocks

private:
    GameGrid() = default
            ;
    //Generates a new set of active blocks
    void generateActive() {
        m_activeBlocks.clear();
        int blocks = rand() % 4 + 1;
        m_activeBlocks.resize(blocks);
        m_activeBlocks[0] = {X/2, X/2, 0};

        for(int i = 1; i < blocks;) {
            ActiveBlock p = m_activeBlocks[i-1];
            int direction = rand() % 4;
            switch(direction) {
                case 0: p.x = std::max(p.x - 1, 0); break;
                case 1: p.y = std::min(p.y + 1, static_cast<int>(X - 1)); break;
                case 2: p.x = std::min(p.x + 1, static_cast<int>(X - 1)); break;
                case 3: p.y = std::max(p.y - 1, 0); break;
                default: break;
            }
            if(!std::any_of(m_activeBlocks.begin(), m_activeBlocks.end(),
                           [&](ActiveBlock &b){ return b.x == p.x && b.y == p.y && b.z == p.z;} )) {
                m_activeBlocks[i] = p;
                i++;
            }
        }

    }

    // Returns true if legal movement
    bool legalMovement( const Direction & movement) {
        switch(movement) {
            case UP:{
                for(auto & b : m_activeBlocks) {
                    if(b.y == X-1) return false;
                    if(m_gameGrid[b.z][b.y+1][b.x] == FULL) return false;
                }
                return true;
            }
            case DOWN: {
                for(auto & b : m_activeBlocks) {
                    if(b.y == 0) return false;
                    if(m_gameGrid[b.z][b.y-1][b.x] == FULL) return false;
                }
                return true;
            }
            case LEFT:{
                for(auto & b : m_activeBlocks) {
                    if(b.x == 0) return false;
                    if(m_gameGrid[b.z][b.y][b.x-1] == FULL) return false;
                }
                return true;
            }
            case RIGHT:{
                for(auto & b : m_activeBlocks) {
                    if(b.x == X-1) return false;
                    if(m_gameGrid[b.z][b.y][b.x+1] == FULL) return false;
                }
                return true;
            }
            case FORWARD:{
                for(auto & b : m_activeBlocks) {
                    if(b.z == Y-1) return false;
                    if(m_gameGrid[b.z+1][b.y][b.x] == FULL) return false;
                }
                return true;
            }
            default: return false;
        }
    }

public:
    std::vector<std::vector<glm::vec3>> stoppedPositions; ///< a vector with the world space positions of all stopped blocks

public:
    explicit GameGrid(const glm::vec3 & dimensions = glm::vec3(1)) : m_dimensions(dimensions){
        generateActive();
        stoppedPositions.resize(Y);
    };

    /**
     * Fills a vector with the positions of the currently active blocks.
     * @return - vector of world space coordinates for blocks
     */
    std::vector<glm::vec3> getActivePositions() {
        std::vector<glm::vec3> ret;
        for(auto & b : m_activeBlocks) {
            float dX = m_dimensions.x / X;
            float dY = m_dimensions.y / X;
            float dZ = m_dimensions.z / Y;
            ret.push_back(glm::vec3(-m_dimensions.x / 2 + b.x*dX + dX / 2,
                                    -m_dimensions.y / 2+ b.y*dY + dX / 2,
                                    -m_dimensions.z / 2 + b.z*dZ + dZ / 2 ));
        }
        return ret;
    }

    /**
     * Attempts to move active blocks forwards. If any block collides with a block in front, or a wall,
     * the active blocks become static, and new active blocks are generated.
     * @return - true if active blocks were able to move forwards
     */
    bool moveForward() {
        if(legalMovement(Direction::FORWARD) ) {
            for(auto & b : m_activeBlocks) {
                b.z += 1;
            }
            return true;
        } else {
            float dX = m_dimensions.x / X;
            float dY = m_dimensions.y / X;
            float dZ = m_dimensions.z / Y;
            for(auto & b : m_activeBlocks) {
                m_gameGrid[b.z][b.y][b.x] = FULL;
                stoppedPositions[b.z].push_back(glm::vec3(-m_dimensions.x / 2 + b.x*dX + dX / 2,
                                                          -m_dimensions.y / 2+ b.y*dY + dX / 2,
                                                          -m_dimensions.z / 2 + b.z*dZ + dZ / 2 ));
            }
            bool full = true;
            for(int i = 0; i < X; i++){
                for(int j = 0; j < X; j++) {
                    if(m_gameGrid[m_activeBlocks.back().z][i][j] != FULL) {
                        full = false;
                    }
                }
            }
            if(full) {
                for(int i = m_activeBlocks.back().z; i >= 1; i--) {
                    stoppedPositions[i].clear();
                    for(int j = 0; j < X; j++){
                        for(int k = 0; k < X; k++) {
                            m_gameGrid[i][j][k] = m_gameGrid[i-1][j][k];
                            if(m_gameGrid[i][j][k] == FULL) {
                                stoppedPositions[i].push_back(glm::vec3(-m_dimensions.x / 2 + k*dX + dX / 2,
                                                                          -m_dimensions.y / 2+ j*dY + dX / 2,
                                                                          -m_dimensions.z / 2 + i*dZ + dZ / 2 ));
                            }
                        }
                    }
                }
            }
        }
        if(m_activeBlocks.back().z == 0) {
            memset(m_gameGrid, 0, sizeof(m_gameGrid));
            for(auto & layer: stoppedPositions){
                layer.clear();
            }
        }
        generateActive();
        return false;
    }


    /**
     * Moves the active blocks in the given direction if unobstructed.
     * @param direction - UP, DOWN, LEFT, RIGHT
     */
    void move(const Direction & direction) {
        if(legalMovement(direction)) {
            switch(direction) {
                case UP: {
                    for(auto & b: m_activeBlocks) {
                        b.y += 1;
                    }
                }; break;
                case DOWN: {
                    for(auto & b: m_activeBlocks) {
                        b.y -= 1;
                    }
                }; break;
                case LEFT: {
                    for(auto & b: m_activeBlocks) {
                        b.x -= 1;
                    }
                }; break;
                case RIGHT: {
                    for(auto & b: m_activeBlocks) {
                        b.x += 1;
                    }
                }; break;
                default: break;
            }
        }
    }
};

#endif //PROG2002_GAMEGRID_H
