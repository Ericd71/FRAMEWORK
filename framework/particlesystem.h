#pragma once

#include <iostream>
#include <stdio.h>

#include <string.h>
#include "framework.h"
#include "image.h"

class ParticleSystem {
    static const int MAX_PARTICLES = 200;

    struct Particle {
        Vector2 position;
        Vector2 velocity; // Normalized speed and direction of the particle
        Color color;
        float acceleration;
        float ttl; // Time left until the particle expires
        bool inactive; // Particle is not used/expired, so it can be recreated
    };

    Particle particles[MAX_PARTICLES];

public:
    void Init();
    void Render(Image* framebuffer);
    void Update(float dt);
};
