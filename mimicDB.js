'use strict'
const { randomUUID } = require("node:crypto");

const waiting = 150;

function delay(ms) {
    return (new Promise((resolve) => setTimeout(resolve, ms)));
}
/* let pretend that our db is map[key,value] */

const usersTable = new Map([
    ["1", { id: "1", name: "uncle", email: "uncle@x.com" }],
    ["2", { id: "2", name: "Bob", email: "bob@y.com" }],
]);



const db = {
    async getAllUsers() {
        await delay(waiting);
        return [...usersTable.values()];
    },
    async getUserById(id) {
        await delay(waiting);
        return usersTable.get(id) ?? null;
    },
    async createUser({ name, email }) {
        await delay(waiting);
        const id = randomUUID();
        const user = { id, name, email };
        usersTable.set(id, user);
        return user;
    },
    async deleteUser(id) {
        await delay(waiting);
        return usersTable.delete(id);
    },
    async updateUserInfo(id, payload) {
        await delay(waiting);
        const user = usersTable.get(id);
        if (!user) return null;
        const updatedUser = { id, ...user, ...payload };
        usersTable.set(id, updatedUser);
        return updatedUser;
    }
};


