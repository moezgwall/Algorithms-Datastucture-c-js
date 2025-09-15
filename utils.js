// array and objects 

const { type } = require("os");

// map()
const users = [
    {name: 'tsoding' , email:'email@gamil.com', age:16},
    {name: 'zozin' , email:'zozin@gamil.com', age:20}
];
// get all the users emails
const emails = users.map(user => user.email);
// get all the users names
const names = users.map(user => user.name);

//filter()
// get user with name tsoding
const byName = users.filter(user=> user.name === 'tsoding');

// forEach
users.forEach(user => {
    console.log(user.name);
});

// find()
const fuser = users.find( user => user.name ==='tsoding');
// sort()
users.sort((a,b)=> a.age - b.age);

// concat()
const arrv1 = [1,3,4,56];
const arrv2 = [2];
const mergeArray = arrv1.concat(arrv2);
// slice()
const partArray = arrv1.slice(1,3); 
// reverse()
const reversedArr = arrv1.reverse();
// splice(nbitem,index)
users.splice(1,1);

let str = "AABBCCC";
str.toLowerCase(); // aabbccc
let bool = str.startsWith('a');
let str1 = "ab cc";
let trimedStr = str1.trim();
// split()
let listName = "alex,mario,angela";
let arr = listName.split(',');

// math functions
Math.floor(55.6); // 55
Math.ceil(2.8); // 3
Math.random();

// typeof instanceof
typeof "hello";
users[0] instanceof Object;
