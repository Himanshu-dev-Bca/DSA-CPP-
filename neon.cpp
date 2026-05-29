#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <thread>
#include <cstdlib>

using namespace std;

// Screen size
const int WIDTH = 80;
const int HEIGHT = 30;

// ANSI colors for neon effect
string colors[] = {
    "\033[38;5;45m",   // cyan
    "\033[38;5;51m",
    "\033[38;5;87m",
    "\033[38;5;123m",
    "\033[38;5;159m"
};

string reset = "\033[0m";

// Particle struct
struct Particle {
    float x, y;
    float vx, vy;
    int life;
};

// Clear screen
void clearScreen() {
    cout << "\033[2J\033[1;1H";
}

// Draw frame buffer
void draw(vector<string>& buffer) {
    clearScreen();
    for (auto &row : buffer) {
        cout << row << "\n";
    }
}

// Neon wave generator
void drawWave(vector<string>& buffer, float time) {
    for (int x = 0; x < WIDTH; x++) {
        float y = HEIGHT / 2 + sin(x * 0.2 + time) * 8;
        int iy = (int)y;

        if (iy >= 0 && iy < HEIGHT) {
            int colorIndex = (int)(fabs(sin(time + x * 0.1)) * 4);
            buffer[iy][x] = '*';
        }
    }
}

// Update particles
void updateParticles(vector<Particle>& particles) {
    for (auto &p : particles) {
        p.x += p.vx;
        p.y += p.vy;
        p.life--;

        // gravity effect
        p.vy += 0.05;
    }

    // remove dead
    particles.erase(
        remove_if(particles.begin(), particles.end(),
            [](Particle& p) { return p.life <= 0; }),
        particles.end()
    );
}

// Draw particles
void drawParticles(vector<string>& buffer, vector<Particle>& particles) {
    for (auto &p : particles) {
        int x = (int)p.x;
        int y = (int)p.y;

        if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
            buffer[y][x] = '.';
        }
    }
}

// Spawn particles randomly
void spawnParticles(vector<Particle>& particles) {
    if (rand() % 5 == 0) {
        Particle p;
        p.x = rand() % WIDTH;
        p.y = rand() % HEIGHT;
        p.vx = ((rand() % 100) / 100.0f - 0.5f);
        p.vy = -((rand() % 100) / 100.0f);
        p.life = 20 + rand() % 30;
        particles.push_back(p);
    }
}

// Apply neon glow (fake blur)
void applyGlow(vector<string>& buffer) {
    vector<string> copy = buffer;

    for (int y = 1; y < HEIGHT - 1; y++) {
        for (int x = 1; x < WIDTH - 1; x++) {
            if (copy[y][x] == '*') {
                buffer[y][x] = '*';
                if (buffer[y+1][x] == ' ') buffer[y+1][x] = '.';
                if (buffer[y-1][x] == ' ') buffer[y-1][x] = '.';
                if (buffer[y][x+1] == ' ') buffer[y][x+1] = '.';
                if (buffer[y][x-1] == ' ') buffer[y][x-1] = '.';
            }
        }
    }
}

// Render with color
void renderColored(vector<string>& buffer, float time) {
    clearScreen();

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            char c = buffer[y][x];

            if (c == '*') {
                int colorIndex = (int)(fabs(sin(time + x * 0.1)) * 4);
                cout << colors[colorIndex] << "*" << reset;
            } else if (c == '.') {
                cout << "\033[38;5;39m.\033[0m";
            } else {
                cout << " ";
            }
        }
        cout << "\n";
    }
}

// Main loop
int main() {
    srand(time(0));

    vector<Particle> particles;
    float time = 0;

    while (true) {
        vector<string> buffer(HEIGHT, string(WIDTH, ' '));

        drawWave(buffer, time);
        spawnParticles(particles);
        updateParticles(particles);
        drawParticles(buffer, particles);
        applyGlow(buffer);

        renderColored(buffer, time);

        time += 0.1;

        this_thread::sleep_for(chrono::milliseconds(50));
    }

    return 0;
}
