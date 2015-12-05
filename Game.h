/* 
 * File:   Game.h
 * Author: Evan
 *
 * Created on November 27, 2015, 7:28 PM
 */

#ifndef GAME_H
#define	GAME_H

#include "Matrix4.h"
#include "MatrixNode.h"
#include "Brick.h"
#include "Wall.h"
#include "Paddle.h"
#include "Ball.h"
#include "Window.h"
#include "BasicParticles.h"
#include <vector>

class Game : public MatrixNode {
public:

    const int rows = 7;
    const int cols = 10;

    const static int width = 40;
    const static int height = 35;

    static bool isPaused;

    static Ball* ball;

    vector<Collidable*> walls;
    Material mat;

    Game() : walls() {
        transform = Matrix4::makeTranslate(-width / 2, -width / 2, -height).applyOther(Matrix4::makeRotateX(RAD(90)));


        Wall* top = new Wall(Vector3(width / 2, .5, 0), width + 1, 1);
        Wall* left = new Wall(Vector3(0, .5, height / 2), 1, height);
        Wall* right = new Wall(Vector3(width, .5, height / 2), 1, height);
        Paddle* paddle = new Paddle(Vector3(width / 2, .5, height));
        mat = top->mat;

        add(top);
        add(left);
        add(right);

        walls.push_back(top);
        walls.push_back(left);
        walls.push_back(right);
        walls.push_back(paddle);



        add(ball);
        add(paddle);

        const int hoffset = (width - 3 * cols) / 2;

        for (int r = 2; r < rows; r += 2) {
            for (int c = 0; c < 3 * cols; c += 3) {
                Brick* brick = new Brick(Vector3(hoffset + c + .5, .5, r));
                add(brick);
                walls.push_back(brick);
            }
        }


        for (int r = rows +1; r < 2 * rows; r += 2) {
            for (int c = 0; c < 3 * cols ; c += 3) {
                Brick* brick = new Brick(Vector3(hoffset + c + .5, .5, r));
                add(brick);
                brick->mat.setAll(Color::green());
                walls.push_back(brick);
            }
        }

    }

    Game(const Game& orig) {

    }

    virtual ~Game() {

    }

    void draw(MatrixStack& old) override {
        MatrixStack cur(old, transform);
        //  ball->ballLight.bind();
        mat.apply();
        //    ball->ballLight.setPosition(ball->getTranslation());
        //    ball->ballLight.bind();


        MatrixStack base(cur, Matrix4::makeScale(width, 1, height).applyOther(Matrix4::makeTranslate(width / 2, -.5, height / 2)));

        renderWithMatrix(base.convert,{
            cube();
        });


        for (auto& child : children) {
            child->draw(cur);
        }

        // ball->ballLight.unbind();
        //    ball->ballLight.unbind();
        old.count += cur.count;
    }

    static bool handleKeypress(unsigned char key) {
        switch (key) {
            case 'b': Globals::isBoundsOn = !Globals::isBoundsOn;
                break;
            case 'p': isPaused = !isPaused;
                break;
            default: return false;
        }

        return true;
    }

    virtual void update(int tick) override {
        if (!isPaused) {
            MatrixNode::update(tick);
            for (auto wall : walls) {
                wall->handleCollisions(*ball);
            }
        }
    }

private:

};

#endif	/* GAME_H */

