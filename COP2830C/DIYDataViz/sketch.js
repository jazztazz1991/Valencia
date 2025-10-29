// Data: Top MMO Games by estimated player count (in millions)
const gameData = {
    'Subscription': {
        shape: 'crown',
        games: [
            { label: 'WoW', count: 8 },
            { label: 'FFXIV', count: 10 }
        ]
    },
    'Buy-to-Play': {
        shape: 'coin',
        games: [
            { label: 'ESO', count: 5 },
            { label: 'New World', count: 3 }
        ]
    },
    'Free-to-Play': {
        shape: 'person',
        games: [
            { label: 'Lost Ark', count: 7 },
            { label: 'Albion', count: 4 },
            { label: 'OSRS', count: 5 },
            { label: 'RS3', count: 2 }
        ]
    }
};

let gameBubbles = [];
let gameColors = {};

function setup() {
    let canvas = createCanvas(600, 400);
    canvas.parent('canvas-container');

    // Generate a unique color for each game
    let allGames = new Set();
    for (let type in gameData) {
        for (let game of gameData[type].games) {
            allGames.add(game.label);
        }
    }

    colorMode(HSB, 360, 100, 100, 100);
    let hue = 0;
    let hueIncrement = 360 / allGames.size;
    for (let game of allGames) {
        gameColors[game] = color(hue, 85, 95, 80);
        hue += hueIncrement;
    }
    colorMode(RGB); // Switch back to RGB

    // Create game objects
    for (let type in gameData) {
        let category = gameData[type];
        for (let game of category.games) {
            let color = gameColors[game.label];
            gameBubbles.push(new Game(game.label, game.count, color, category.shape));
        }
    }
}

function draw() {
    background(255);

    // Update and display all game bubbles
    for (let i = 0; i < gameBubbles.length; i++) {
        gameBubbles[i].move();
        gameBubbles[i].display();
        for (let j = i + 1; j < gameBubbles.length; j++) {
            gameBubbles[i].intersects(gameBubbles[j]);
        }
    }
    
    // Legend for Game Titles
    let legendX = 20;
    let legendY = 20;
    let index = 0;
    for (let game in gameColors) {
        fill(gameColors[game]);
        noStroke();
        rect(legendX, legendY + index * 20, 15, 15);
        fill(0);
        textAlign(LEFT, CENTER);
        textSize(12);
        text(game, legendX + 20, legendY + index * 20 + 7);
        index++;
    }

    // Legend for Shapes
    let shapeLegendX = width - 120;
    let shapeLegendY = 20;
    let shapeLegendSize = 30;
    
    fill(0);
    noStroke();
    textAlign(LEFT, CENTER);
    textSize(12);

    // Subscription Shape
    text('Subscription', shapeLegendX + shapeLegendSize - 5, shapeLegendY + shapeLegendSize / 2);
    push();
    translate(shapeLegendX, shapeLegendY + shapeLegendSize / 2);
    drawGameShape('crown', shapeLegendSize, color(220));
    pop();

    // Buy-to-Play Shape
    text('Buy-to-Play', shapeLegendX + shapeLegendSize - 5, shapeLegendY + shapeLegendSize * 1.5 + 10);
    push();
    translate(shapeLegendX, shapeLegendY + shapeLegendSize * 1.5 + 10);
    drawGameShape('coin', shapeLegendSize, color(220));
    pop();

    // Free-to-Play Shape
    text('Free-to-Play', shapeLegendX + shapeLegendSize - 5, shapeLegendY + shapeLegendSize * 2.5 + 20);
    push();
    translate(shapeLegendX, shapeLegendY + shapeLegendSize * 2.5 + 20);
    drawGameShape('person', shapeLegendSize, color(220));
    pop();

    // Label for size meaning
    fill(0);
    noStroke();
    textAlign(CENTER, BOTTOM);
    textSize(12);
    text("Size represents estimated player count (in millions).", width / 2, height - 5);
}

function drawGameShape(shape, size, clr) {
    fill(clr);
    stroke(0);
    strokeWeight(1);
    
    if (shape === 'crown') {
        triangle(-size/2, 0, size/2, 0, 0, -size/2);
        rect(-size/2, 0, size, size/4);
    } else if (shape === 'coin') {
        ellipse(0, 0, size, size);
        textAlign(CENTER, CENTER);
        fill(0);
        noStroke();
        textSize(size * 0.6);
        text('$', 0, 0);
    } else if (shape === 'person') {
        ellipse(0, -size/4, size/3, size/3);
        rect(-size/2, 0, size, size/2);
    }
}

function mousePressed() {
    for (let game of gameBubbles) {
        game.clicked(mouseX, mouseY);
    }
}

// Game class
class Game {
    constructor(label, count, color, shape) {
        this.label = label;
        this.count = count;
        this.color = color;
        this.shape = shape;
        this.size = sqrt(count) * 25;
        this.x = random(this.size / 2, width - this.size / 2);
        this.y = random(this.size / 2, height - this.size / 2);
        this.vx = random(-1, 1);
        this.vy = random(-1, 1);
        this.revealed = false;
    }

    move() {
        this.x += this.vx;
        this.y += this.vy;

        if (this.x + this.size / 2 > width || this.x - this.size / 2 < 0) {
            this.vx *= -1;
        }
        if (this.y + this.size / 2 > height || this.y - this.size / 2 < 0) {
            this.vy *= -1;
        }
    }

    display() {
        push();
        translate(this.x, this.y);
        drawGameShape(this.shape, this.size, this.color);
        pop();

        fill(0);
        noStroke();
        textAlign(CENTER, CENTER);
        textSize(this.size / 4 > 9 ? this.size / 4 : 9);
        text(this.label, this.x, this.y);

        if (this.revealed) {
            fill(0, 0, 0, 220);
            textSize(16);
            text(this.count + "M", this.x, this.y + this.size / 2 + 10);
        }
    }

    intersects(other) {
        let d = dist(this.x, this.y, other.x, other.y);
        if (d < (this.size + other.size) / 2) {
            let angle = atan2(other.y - this.y, other.x - this.x);
            let overlap = ((this.size + other.size) / 2) - d;
            this.x -= cos(angle) * overlap / 2;
            this.y -= sin(angle) * overlap / 2;
            other.x += cos(angle) * overlap / 2;
            other.y += sin(angle) * overlap / 2;

            let tempVx = this.vx;
            let tempVy = this.vy;
            this.vx = other.vx;
            this.vy = other.vy;
            other.vx = tempVx;
            other.vy = tempVy;
        }
    }

    clicked(px, py) {
        let d = dist(px, py, this.x, this.y);
        if (d < this.size / 2) {
            this.revealed = !this.revealed;
        }
    }
}