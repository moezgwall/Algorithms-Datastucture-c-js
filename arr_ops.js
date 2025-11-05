

// remove duplicates from an array 

const arr = ["git", "clone", "git", "cmder", "clone"];
const noduplicates = [...new Set(arr)];

// output : ["git", "clone", "cmder"]

// array of users 
// users are objects

const users = [
    { id_: 1, username: "zozin" },
    { id_: 122, username: "kafka" },
    { id_: 10, username: "Marx" },
];

const orders = [
    { userID: 1, product: "cars" },
    { userID: 1, product: "dildos" },
    { userID: 10, product: "phones" },
];

const allUserOrders = users.map(user => ({ ...user, orders: orders.filter(order => order?.userID === user?.id_) }));


// compute the total amount for each user
const transactions = [
    { userID: 1, amount: 10 },
    { userID: 10, amount: 1500 },
    { userID: 10, amount: 5 },
    { userID: 1, amount: 358 },
    { userID: 1, amount: 12 },
    { userID: 3, amount: 105 },
];

const totals = transactions.reduce((acc, user) => { acc[user?.userID] = (acc[user?.userID] || 0) + user?.amount; return acc; }, {});

// get all the userID with amount > 0
const hasAmount = transactions.filter(u => u?.amount > 0).map(u => u.userID);
// no duplicates 
const uniqueHasAmout = [...new Set(hasAmount)];

// each userID with his total 
const usersTotals = users.map(u => ({
    ...u,
    total: totals[u.id_] || 0

}));



