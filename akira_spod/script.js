const message = document.getElementById('message');
const startBtn = document.getElementById('startBtn');
const spans = document.querySelectorAll('#inputs span');

let step = -1;
const pressed = {};

function updateHighlight() {
    spans.forEach((s, idx) => {
        if (idx === step) {
            s.classList.add('active');
        } else {
            s.classList.remove('active');
        }
    });
}

function start() {
    step = 0;
    message.textContent = 'Step 1: → と P を同時に押せ!';
    updateHighlight();
    startBtn.disabled = true;
}

startBtn.addEventListener('click', start);

document.addEventListener('keydown', e => {
    pressed[e.key] = true;
    checkInput();
});

document.addEventListener('keyup', e => {
    pressed[e.key] = false;
});

function checkInput() {
    switch (step) {
        case 0:
            if (pressed['ArrowRight'] && (pressed['p'] || pressed['P'])) {
                step = 1;
                message.textContent = 'いいぞ! Step 2: P を押せ!';
                updateHighlight();
            }
            break;
        case 1:
            if (pressed['p'] || pressed['P']) {
                step = 2;
                message.textContent = 'ラスト! Step 3: → + P + G を同時に押せ!';
                updateHighlight();
            }
            break;
        case 2:
            if (pressed['ArrowRight'] && (pressed['p'] || pressed['P']) && (pressed['g'] || pressed['G'])) {
                step = 3;
                message.textContent = '完璧! 崩撃雲身双虎掌 成功!';
                updateHighlight();
                startBtn.disabled = false;
            }
            break;
        default:
            break;
    }
}
