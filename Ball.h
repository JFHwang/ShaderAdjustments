/* 
 * File:   Ball.h
 * Author: Evan
 *
 * Created on November 27, 2015, 7:29 PM
 */

#ifndef BALL_H
#define	BALL_H

#include "SmartGeode.h"
#include "ParticleSystem.h"
#include "ParticleSource.h"
#include "Shader.h"

class Ball : public SmartGeode, public ParticleSource {
public:

    static constexpr float SPEED = 7.0f;

    Vector3 speed; // In units/second
    ParticleSystem system;
    Light ballLight;

    Ball(Vector3 pos) : SmartGeode(pos, 1, 1), speed(Vector3(frand(-1, 0), 0, -1).normalize()), system(3000, this), ballLight(7, Light::POINT_LIGHT) {
        speed = speed.scale(SPEED);
        survivalRate = 96;
        ballLight.constantAttenuation = 0;
        ballLight.quadraticAttenuation = .9;
        ballLight.linearAttenuation = .1;
        mat.emissionColor = Color::white();
        mat.diffuseColor = Color::white();
        mat.ambientColor = Color::white();
        mat.shininess = 0;
    }

    Ball(const Ball& orig) : SmartGeode(orig), system(orig.system), ballLight(7, Light::POINT_LIGHT) {

    }

    virtual ~Ball() {


    }

    Vector3 speedGenerator(Vector3 position) const override {
        Vector3 var = Vector3(frand(-1, 1), frand(-1, 1), frand(-1, 1)).normalize().cross(speed.normalize());

        return (var.scale(.35)).scale(1.0f / 60);
    }

    virtual Color colorGenerator() const {
        Vector3 rand(frand(.3, .8), frand(.3, .7), frand(0, .1));
        Material m;
        rand = rand.normalize();
        return Color(rand.get(0), rand.get(1), rand.get(2), frand(.8, 1));
    }

    void update(int tick) override {
        transform.applyOther(Matrix4::makeTranslate(speed.scale(1.0f / 60)));
        system.update(tick);
    }

    virtual void render() override {
        GLUquadricObj* pQuadric = gluNewQuadric();
        gluSphere(pQuadric, .5, 50, 50);
        gluQuadricOrientation(pQuadric, GLU_INSIDE);

        gluSphere(pQuadric, .5, 500, 500);
       // glutSolidSphere(.5, 50, 50);
    }

    virtual void draw(MatrixStack& cum) {
        ++cum.count;
        MatrixStack stack = cum.push(transform);

        renderWithMatrix(stack.convert,{

            ballLight.bind();
            mat.apply();
            render();
            // ballLight.unbind();
        });
        system.draw(cum);
    }

    virtual Vector3 randOffset() const override {
        return ParticleSource::randOffset() + getTranslation();
    }

private:

};

#endif	/* BALL_H */

