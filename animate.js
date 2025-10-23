class fireball {
  constructor(x, y) {
    this.x = x;
    this.y = y;
    this.radius = 5;
    this.alpha = 1;
    this.color = `hsl(${Math.random() * 60}, 100%, 50%)`;
    const speed = Math.random() * 2 + 1;
    const angle = Math.random() * Math.PI * 2;
    this.vx = Math.cos(angle) * speed;
    this.vy = Math.sin(angle) * speed;
  }

  draw(ctx) {
    ctx.beginPath();
    ctx.fillStyle = `rgba(255, 100, 0, ${this.alpha})`;
    ctx.arc(this.x, this.y, this.radius, 0, Math.PI * 2);
    ctx.fill();
  }
  update() {
    this.radius += 1;
    this.alpha -= 0.02;
    this.x += this.vx;
    this.y += this.vy;
  }
}

const fireballs = [];
const canvas = document.getElementById("canvas");
const ctx = canvas.getContext("2d");
canvas.width = 800;
canvas.height = 600;

// populate the canvas

canvas.addEventListener("click", (e) => {
  e.preventDefault();
  const rect = canvas.getBoundingClientRect();
  const x = e.clientX - rect.left;
  const y = e.clientY - rect.top;

  for (let i = 0; i < 20; i++) {
    fireballs.push(new Fireball(x, y));
  }
});

function animate() {
  ctx.clearRect(0, 0, canvas.width, canvas.height);
  for (let i = fireballs.length - 1; i >= 0; i--) {
    const f = fireballs[i];
    f.update();
    f.draw(ctx);
    if (f.alpha <= 0) fireballs.splice(i, 1);
  }

  requestAnimationFrame(animate);
}

animate();
