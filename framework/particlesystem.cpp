#include <string>
#include <iostream>

#include "particlesystem.h"
#include "image.h"


void ParticleSystem::Init() {
    for (int i = 0; i < MAX_PARTICLES; ++i) {
        particles[i].position = Vector2(rand() % 1280, rand() % 720); // Random initial position
        particles[i].velocity = Vector2((rand() % 200 - 100) / 100.0f, (rand() % 200 - 100) / 100.0f); // Random initial velocity
        particles[i].color = Color::WHITE; // White color
        particles[i].acceleration = 0.1f; // Set your desired acceleration
        particles[i].ttl = (float)(rand() % 100) / 10.0f; // Set a random time to live
        particles[i].inactive = false;
    }
}

void ParticleSystem::Render(Image* framebuffer) {
    for (int i = 0; i < MAX_PARTICLES; ++i) {
        if (!particles[i].inactive) {
            // Draw the particle on the framebuffer
            framebuffer->SetPixelSafe(particles[i].position.x, particles[i].position.y, particles[i].color);
        }
    }
}

void ParticleSystem::Update(float dt) {
    for (int i = 0; i < MAX_PARTICLES; ++i) {
        if (!particles[i].inactive) {
            // Update particle position using the equation of motion (P0 = P + V ∗ t)
            particles[i].position.x += particles[i].velocity.x * dt;
            particles[i].position.y += particles[i].velocity.y * dt;

            // Update particle velocity based on acceleration (V0 = V + a ∗ t)
            particles[i].velocity.x += particles[i].acceleration * dt;
            particles[i].velocity.y += particles[i].acceleration * dt;

            // Decrease time to live
            particles[i].ttl -= dt;

            // Check if the particle's time to live has expired
            if (particles[i].ttl <= 0.0f) {
                particles[i].inactive = true;
            }
        }
    }
}
