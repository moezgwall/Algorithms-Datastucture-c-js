// eval__expression::
// suppose we have an expression like that typeof(expr) === "string"
// expr := "1+3" it should be 4
// expr := "4*4" it should be 16
// problems:
// NO operator precedence
// NO SUPPORT FOR ()
// ill figure out how to implement it
// and update this

function evalexp(str) {
  let res = 0;
  let op = "+";
  let idx = 0;
  while (idx < str.length) {
    if (str[idx] === " ") {
      idx++;
      continue;
    }
    if (
      /\d/.test(str[idx]) ||
      (str[idx] === "-" && (idx === 0 || "+-*/".includes(str[idx - 1])))
    ) {
      let buffer = "";

      if (str[idx] === "-") {
        buffer += str[idx];
        idx++;
      }

      while (str[idx] && (/\d/.test(str[idx]) || str[idx] === ".")) {
        buffer += str[idx];
        idx++;
      }

      let numb = parseFloat(buffer);
      if (op === "+") res += numb;
      else if (op === "-") res -= numb;
      else if (op === "*") res *= numb;
      else if (op === "/") res /= numb;

      continue;
    }

    if ("+-*/".includes(str[idx])) {
      op = str[idx];
      idx++;
      continue;
    }

    idx++;
  }

  return res;
}

// regular expression
// /\s+\g
// const str =  str.replace(value,withValue);
// / \d / . test(ch) => test if ch matches a regular expression
// str.includes(something ) -> (true or false)
// we check if str includes that something

console.log(evalexpr("4 * 4 "));
console.log(evalexpr("4 + 200 "));
console.log(evalexpr("1000-350 "));
console.log(evalexpr("20* 0.5 "));
console.log(evalexpr("3000 * 3 + 1"));
console.log(evalexpr("1000 * 1000 * 1000 * 1000 * 1000 * 1000 * 1000"));
