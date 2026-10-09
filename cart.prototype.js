
/* 
 * this how a simple cart must be implemented 
 * and it can be used in ecommerce sites 
 * with some improvements it will work
 * but this is just a prototype not real implementation
 * */

const item = {
      id: "11136azEsadAZE",
      name: "item1",
      price: 100,
      quantity: 10,
      av:true,
      isExpired:false,
      dateAdded: new Date(),
      expDate: new Date()
};


class Cart{

    #cart_items = new Map(); 
    #max_nb_items = 100; 
    
    hasItem(id){
        return this.#cart_items.has(id);
    }    
    addItemToCart(item){
       const {id,...payload} = item; 
       if (this.#cart_items.has(id)){
               throw new Error("this item already exist");
       }
           if (this.#cart_items.size < this.#max_nb_items){    
                this.#cart_items.set(id,{...payload});
                return;
           }else{
                   throw new Error("this item already exist");
           }
       }
    
    // avoid falsy true     
   // 1 ---> sucess
   // -1 ---> fail 
    removeItemFromCart(id){
            if(id === undefined || id === null) throw new Error("id not found or null");
            if (this.#cart_items.delete(id)){
                    return 1;
            }
            return -1; 
    }    
    getTotalPrice(){
        let total = 0; 
            for (const [id,item] of this.#cart_items){
                    total += (item.price || 0) * item.quantity;
            }
            return total;
    }
    
    getQuantityItem(id){
            const item = this.#cart_items.get(id);
            if(!item){ 
                 throw new Error("item not found");
            }
            return item.quantity ?? 0;
    }      
        
   getMaxNbItems(){
           return this.#max_nb_items;
   }     
   getMapInstance(){
           return this.#cart_items;
   }
  }
