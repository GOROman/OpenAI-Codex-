const COLS = 6;
const ROWS = 12;
const SIZE = 40; // pixel size of one puyo

const canvas = document.getElementById('game');
const ctx = canvas.getContext('2d');

const COLORS = ['red', 'yellow', 'green', 'blue', 'purple'];

function randomColor() {
    return COLORS[Math.floor(Math.random() * COLORS.length)];
}

const board = Array.from({ length: ROWS }, () => Array(COLS).fill(null));

class Pair {
    constructor() {
        this.x = 2;
        this.y = -1; // top outside the board
        this.blocks = [
            { x: 0, y: 0, color: randomColor() },
            { x: 0, y: -1, color: randomColor() }
        ];
    }

    rotate() {
        const b = this.blocks[1];
        const tmp = { x: b.x, y: b.y };
        b.x = -tmp.y;
        b.y = tmp.x;
        if (collides(this)) {
            // revert if collision
            b.x = tmp.x;
            b.y = tmp.y;
        }
    }
}

let current = new Pair();
let dropCounter = 0;
let dropInterval = 500;
let lastTime = 0;
let gameOver = false;

function collides(pair) {
    for (const b of pair.blocks) {
        const x = pair.x + b.x;
        const y = pair.y + b.y;
        if (x < 0 || x >= COLS || y >= ROWS) return true;
        if (y >= 0 && board[y][x]) return true;
    }
    return false;
}

function merge(pair) {
    for (const b of pair.blocks) {
        const x = pair.x + b.x;
        const y = pair.y + b.y;
        if (y < 0) {
            gameOver = true;
            return;
        }
        board[y][x] = b.color;
    }
}

function clearGroups() {
    const visited = Array.from({ length: ROWS }, () => Array(COLS).fill(false));
    let cleared = false;

    function flood(x, y, color, group) {
        if (x < 0 || x >= COLS || y < 0 || y >= ROWS) return;
        if (visited[y][x] || board[y][x] !== color) return;
        visited[y][x] = true;
        group.push({ x, y });
        flood(x + 1, y, color, group);
        flood(x - 1, y, color, group);
        flood(x, y + 1, color, group);
        flood(x, y - 1, color, group);
    }

    for (let y = 0; y < ROWS; y++) {
        for (let x = 0; x < COLS; x++) {
            if (board[y][x] && !visited[y][x]) {
                const group = [];
                flood(x, y, board[y][x], group);
                if (group.length >= 4) {
                    cleared = true;
                    for (const p of group) {
                        board[p.y][p.x] = null;
                    }
                }
            }
        }
    }

    if (cleared) {
        for (let y = ROWS - 1; y >= 0; y--) {
            for (let x = 0; x < COLS; x++) {
                if (board[y][x] === null) {
                    for (let yy = y - 1; yy >= 0; yy--) {
                        if (board[yy][x]) {
                            board[y][x] = board[yy][x];
                            board[yy][x] = null;
                            break;
                        }
                    }
                }
            }
        }
    }
}

function playerMove(dir) {
    current.x += dir;
    if (collides(current)) {
        current.x -= dir;
    }
}

function playerDrop() {
    current.y++;
    if (collides(current)) {
        current.y--;
        merge(current);
        clearGroups();
        current = new Pair();
    }
    dropCounter = 0;
}

function update(time = 0) {
    if (gameOver) {
        ctx.fillStyle = 'black';
        ctx.fillRect(0, 0, canvas.width, canvas.height);
        ctx.fillStyle = 'white';
        ctx.font = '32px sans-serif';
        ctx.fillText('Game Over', 40, canvas.height / 2);
        return;
    }

    const delta = time - lastTime;
    lastTime = time;
    dropCounter += delta;
    if (dropCounter > dropInterval) {
        playerDrop();
    }
    draw();
    requestAnimationFrame(update);
}

document.addEventListener('keydown', event => {
    if (gameOver) return;
    switch (event.key) {
        case 'ArrowLeft':
            playerMove(-1);
            break;
        case 'ArrowRight':
            playerMove(1);
            break;
        case 'ArrowDown':
            playerDrop();
            break;
        case 'ArrowUp':
            current.rotate();
            break;
    }
});

function draw() {
    ctx.clearRect(0, 0, canvas.width, canvas.height);

    for (let y = 0; y < ROWS; y++) {
        for (let x = 0; x < COLS; x++) {
            const color = board[y][x];
            if (color) drawBlock(x, y, color);
        }
    }

    for (const b of current.blocks) {
        const x = current.x + b.x;
        const y = current.y + b.y;
        if (y >= 0) {
            drawBlock(x, y, b.color);
        }
    }
}

function drawBlock(x, y, color) {
    ctx.fillStyle = color;
    ctx.fillRect(x * SIZE, y * SIZE, SIZE - 1, SIZE - 1);
}

update();
