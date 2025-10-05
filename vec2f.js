class vec2f {
  constructor(x = 0, y = 0) {
    this.x = x;
    this.y = y;
  }

  clone() {
    return new vec2f(this.x, this.y);
  }
  add(v) {
    return new vec2f(this.x + v.x, this.y + v.y);
  }
  sub(v) {
    return new vec2f(this.x - v.x, this.y - v.y);
  }
  multby(scalar) {
    return new vec2f(this.x * scalar, this.y * scalar);
  }
  divby(scalar) {
    return new vec2f(this.x / scalar, this.y / scalar);
  }
  len() {
    return Math.sqrt(this.x * this.x + this.y * this.y);
  }

  normalize() {
    const len = this.len();
    if (len === 0) return new vec2f(0, 0);
    return this.divby(len);
  }

  dot(v) {
    return this.x * v.x + this.y * v.y;
  }

  toString() {
    return `(${this.x.toFixed(2)}, ${this.y.toFixed(2)})`;
  }

  addSelf(v) {
    this.x += v.x;
    this.y += v.y;
    return this;
  }

  subtractSelf(v) {
    this.x -= v.x;
    this.y -= v.y;
    return this;
  }

  multiplySelf(scalar) {
    this.x *= scalar;
    this.y *= scalar;
    return this;
  }

  divideSelf(scalar) {
    this.x /= scalar;
    this.y /= scalar;
    return this;
  }

  normalizeSelf() {
    const len = this.len();
    if (len !== 0) {
      this.x /= len;
      this.y /= len;
    } else {
      this.x = 0;
      this.y = 0;
    }
    return this;
  }

  set(x, y) {
    this.x = x;
    this.y = y;
    return this;
  }

  equals(v) {
    return this.x === v.x && this.y === v.y;
  }

  static zero() {
    return new vec2f(0, 0);
  }
  static one() {
    return new vec2f(1, 1);
  }
  static up() {
    return new vec2f(0, -1);
  }
  static down() {
    return new vec2f(0, 1);
  }
  static left() {
    return new vec2f(-1, 0);
  }
  static right() {
    return new vec2f(1, 0);
  }
}
