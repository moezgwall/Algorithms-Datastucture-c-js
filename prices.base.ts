
type withDiscount = {
        type     : "discount";
        price    : number;
        discount : number;
}; 

type withNoDiscount = {
        type : "nodiscount";
        price: number;
}

type priceKind = withDiscount | withNoDiscount;

interface PriceDTO {
        regularPrice    : (p:priceKind) => number;
}
const SETTING_PRICE_OP_FAILED_CODE = -999;
class subPayment implements PriceDTO{
        constructor(){}

        regularPrice(p: priceKind) : number {
                switch(p.type){
                        case "discount":{
                                return (p.discount * p.price) / 100;
                        };
                        case "nodiscount":{
                                return (p.price);
                        };
                        default:{ 
                                const __failuretype : never = p;
                                return SETTING_PRICE_OP_FAILED_CODE;
                        }
                }
        }
}

