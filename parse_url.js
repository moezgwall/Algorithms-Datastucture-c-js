const fullurl =
  "http://localhost:6969/path/to/page?username=zozin&age=30#section2";

// creating a url object
const url = new URL(fullurl);
// url object attributes
console.log("Full URL:", url.href);
console.log("Protocol:", url.protocol); // "https:"
console.log("Host:", url.host); // "localhost:6969"
console.log("Hostname:", url.hostname); // "localhost"
console.log("Port:", url.port); // "6969"
console.log("Pathname:", url.pathname); // "/path/to/page"
console.log("Search:", url.search); // "?username=zozin&age=30"
console.log("Hash:", url.hash); // "#section2"

// we are interest in the querey
// params
// url.search
// params {key , val}
const params = new URLSearchParams(url.search);
// params.get(key) -> value
// params.has(key)
// params.set(key,val)
// params.append(key,val) override the key val
// params.delete(key)
// params.forEach()

for (const [key, value] of params) {
  console.log(`${key} = ${value}`);
}
