// author: gwall 
// ABOUT SYMBOLS
// a very common use case of symbols : 
// making this collection(object) iterable
const collection = {
    items: ["foo","bar","duck"],
    [Symbol.iterator]() {
        let index = 0;
        return {
            next: () =>{
                if (index < this.items.length){
                    return {value: this.items[index++],done:false};
                }
                return {value: undefined ,done:true};
            }
        };
    }
};

// testing 

for (const item of collection){
    console.log(item);
}

// other use case 

const password = Symbol("abcdef"); 
const user = {
    name: "zeusing",
    [password] : "youcantaccessme"
};
console.log(user.password); // shows undefined 
const keys = Object.keys(user); 
console.log(keys); // output : name only but expected name,password 
const values = Object.values(user); 
console.log(values); // output: zeusing only but expected zeusing,youcantaccessme 

const symb = Object.getOwnPropertySymbols(user); 
console.log(symb); // output :  [symbol(abcdef)] 
console.log(user[symb[0]]); // output: youcantaccessme  



